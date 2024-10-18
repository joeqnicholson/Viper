#include "KCCMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Mathf.h"

UKCCMovementComponent::UKCCMovementComponent()
{
    bGrounded = false;
    CapsuleComponent = nullptr;
}

void UKCCMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Ensure CapsuleComponent is initialized
    if (!CapsuleComponent)
    {
        InitializeCapsuleComponent();
    }

    // Validate that the component is allowed to move
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || !CapsuleComponent)
    {
        return;
    }

    if(ForceNotGroundedTimer >= 0)
    {
        ForceNotGroundedTimer -= DeltaTime;
    }

    // Get (and then clear) the movement vector that we set in AKCC::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector() * DeltaTime;

    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        // Perform a downward capsule sweep to check for ground
        FVector Start = UpdatedComponent->GetComponentLocation();
        float GroundCheckDistance = FMath::Lerp(GroundCheckDistanceSteep, GroundCheckDistanceFlat, GroundNormalLastFrame.Z);
        if(!bGrounded) { GroundCheckDistance = GroundCheckDistanceFlat; }
        FVector End = Start - FVector(0, 0, GroundCheckDistance); // Adjust trace distance based on capsule half-height + buffer
        FHitResult GroundHit;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(PawnOwner); 

        bool bGroundHit = GetWorld()->SweepSingleByChannel(
            GroundHit, Start, End, FQuat::Identity, ECC_Visibility,
            FCollisionShape::MakeCapsule(CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetScaledCapsuleHalfHeight()),
            QueryParams
        );

        GroundNormalLastFrame = GroundNormal;
        float AngleLastFrame = Mathf::Angle(GroundNormal, FVector::UpVector);
        GroundNormal = GroundHit.ImpactNormal;
        float Angle = Mathf::Angle(GroundNormal, FVector::UpVector);
        float AngleDifference = FMath::Abs(Angle - MaxSlopeAngle);
        bGrounded = bGroundHit && Angle < MaxSlopeAngle && AngleDifference < MaxAngleDifference && ForceNotGroundedTimer <= 0;

        if (bGrounded && GroundHit.IsValidBlockingHit())
        {
            // Ensure the capsule remains just above the ground by compensating for the half-height
            float DesiredHeightAboveGround = 2.0f; // Adjust for small height above ground
            FVector AdjustedPosition = UpdatedComponent->GetComponentLocation();
            AdjustedPosition.Z = GroundHit.ImpactPoint.Z + CapsuleComponent->GetScaledCapsuleHalfHeight() + DesiredHeightAboveGround;
            UpdatedComponent->SetWorldLocation(AdjustedPosition);

            // Project movement onto the ground plane
            FVector SlopeAdjustedMovement = FVector::VectorPlaneProject(DesiredMovementThisFrame, GroundNormal);
            FHitResult SlideHit;
            SafeMoveUpdatedComponent(SlopeAdjustedMovement, UpdatedComponent->GetComponentRotation(), true, SlideHit);

            // If we bump into something, try to slide along it
            if (SlideHit.IsValidBlockingHit())
            {
                SlideAlongSurface(SlopeAdjustedMovement, 1.f - SlideHit.Time, SlideHit.Normal, SlideHit);
            }

            // Perform step handling only if grounded
            if(bGrounded)
            {
                HandleStepping(DesiredMovementThisFrame);
            }

        }
        else
        {
            // No valid ground hit, so we move as usual without slope adjustment
            FHitResult Hit;
            SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

            // If we bump into something, try to slide along it
            if (Hit.IsValidBlockingHit())
            {
                SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
            }
        }
        
    }
}

void UKCCMovementComponent::InitializeCapsuleComponent()
{
    if (AActor* Owner = GetOwner())
    {
        CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
    }

    if (!CapsuleComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("KCCMovementComponent: No CapsuleComponent found on %s"), *GetOwner()->GetName());
    }
}

void UKCCMovementComponent::HandleStepping(FVector& MovementVector)
{

    FVector Start = UpdatedComponent->GetComponentLocation() + FVector(MovementVector.X, MovementVector.Y, MaxStepHeight);
    FVector End = UpdatedComponent->GetComponentLocation() + FVector(MovementVector.X, MovementVector.Y, -MaxStepHeight * 1.50f);   

    FHitResult StepHit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(PawnOwner);

    bool bStepHit = GetWorld()->SweepSingleByChannel(
        StepHit, Start, End, FQuat::Identity, ECC_Visibility,
        FCollisionShape::MakeCapsule(CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetScaledCapsuleHalfHeight()),
        QueryParams
    );

    if (bStepHit && StepHit.IsValidBlockingHit())
    {
        // Ensure the capsule remains just above the ground by compensating for the half-height
        float DesiredHeightAboveGround = 2.0f; // Adjust for small height above ground
        FVector AdjustedPosition = UpdatedComponent->GetComponentLocation();
        AdjustedPosition.Z = StepHit.ImpactPoint.Z + CapsuleComponent->GetScaledCapsuleHalfHeight() + DesiredHeightAboveGround;
        UpdatedComponent->SetWorldLocation(AdjustedPosition);
    }
}




bool UKCCMovementComponent::IsGrounded() const
{
    return bGrounded && ForceNotGroundedTimer <= 0;
}

void UKCCMovementComponent::ForceUnground(float Time = .3f)
{
    ForceNotGroundedTimer = Time;
}
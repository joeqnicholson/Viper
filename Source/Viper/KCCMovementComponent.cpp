#include "KCCMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void UKCCMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure that everything is still valid, and that we are allowed to move.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // Get (and then clear) the movement vector that we set in AKCC::Tick
    FVector DesiredMovementThisFrame = ConsumeInputVector() * DeltaTime;
    
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        // Perform a downward trace to find the floor
        FVector Start = UpdatedComponent->GetComponentLocation();
        FVector End = Start - FVector(0, 0, 300.0f); // Adjust this value as necessary

        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(PawnOwner);
        
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
        bGrounded = bHit;

        if (bHit && HitResult.IsValidBlockingHit())
        {
            // Get the normal of the surface we hit
            FVector SurfaceNormal = HitResult.ImpactNormal;

            // Project the desired movement vector onto the plane defined by the surface normal
            FVector SlopeAdjustedMovement = FVector::VectorPlaneProject(DesiredMovementThisFrame, SurfaceNormal);

            // Attempt to move along the slope
            FHitResult SlideHit;
            SafeMoveUpdatedComponent(SlopeAdjustedMovement, UpdatedComponent->GetComponentRotation(), true, SlideHit);

            // If we bump into something, try to slide along it
            if (SlideHit.IsValidBlockingHit())
            {
                SlideAlongSurface(SlopeAdjustedMovement, 1.f - SlideHit.Time, SlideHit.Normal, SlideHit);
            }
        }
        else
        {
            // No valid hit, move as usual without slope adjustment
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
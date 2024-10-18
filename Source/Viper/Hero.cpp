// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "Mathf.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeroAirborneState.h"
#include "HeroGroundedState.h"
#include "KCCMovementComponent.h"
#include "Engine/Engine.h"
#include "HeroController.h"


AHero::AHero()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
    Camera = FindComponentByClass<UCameraComponent>();
    HeroController = Cast<AHeroController>(GetController());
    InitializeStateMachine();
}

void AHero::InitializeStateMachine()
{
    HeroStateMachine = NewObject<UStateMachine>(this);
    GroundedState = NewObject<UHeroGroundedState>(this);
    GroundedState->Initialize(this);
    AirborneState = NewObject<UHeroAirborneState>(this);
    AirborneState->Initialize(this);

    // Debug messages to confirm initialization
    if (HeroStateMachine)
    {
        UE_LOG(LogTemp, Log, TEXT("State Machine initialized successfully."));
    }
    
    if (GroundedState)
    {

        UE_LOG(LogTemp, Log, TEXT("Grounded State initialized with Hero: %s"), *GroundedState->GetName());
    }
    
    if (AirborneState)
    {
        UE_LOG(LogTemp, Log, TEXT("Airborne State initialized with Hero: %s"), *AirborneState->GetName());
    }

    // Set the initial state based on the current grounded state

    if (IsGrounded())
    {
        HeroStateMachine->SetState(GroundedState);
        if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GroundedSet")); }
    }
    else
    {
        HeroStateMachine->SetState(AirborneState);
        if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("AirborneSet")); }
    }
}


// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
    Super::SetupPlayerInputComponent(InInputComponent);
	UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent called on AHero"));
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    deltaTime = DeltaTime;
    if (HeroStateMachine && HeroStateMachine->GetCurrentState())
    {
        FString ClassName = HeroStateMachine->GetCurrentState()->GetName();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Operating: %s"), *ClassName));
        HeroStateMachine->Update(DeltaTime);
    }
    else
    {
        if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("StateMachineNotUpdating")); }
    }

    // Movement logic

    Move(CurrentVelocity);
    Rotate(CurrentRotation);

}

void AHero::GroundedMovement(float DeltaTime)
{

    if (HeroController->GetMoveInput().Length() > 0.2f)
    {
        speed = FMath::Lerp(speed, MaxRun, Acceleration * DeltaTime);
    }
    else
    {
        speed = FMath::Lerp(speed, 0.0f, Deceleration * DeltaTime);
    }

    FVector forwardDirection = GetActorForwardVector();
    CurrentVelocity = forwardDirection * speed;

}

void AHero::GroundedRotation(float DeltaTime)
{

    turnSpeed = FMath::Lerp(TurnSpeedWhileSlow, TurnSpeedWhileFast, MaxRun / speed);

    if (HeroController->GetMoveInput().Length() > 0.5f)
    {
        rotationInput = Mathf::LocalInputRotation(HeroController->GetMoveInput(), Camera);
    }

    CurrentRotation = FMath::RInterpTo(CurrentRotation, rotationInput, DeltaTime, turnSpeed);

}

void AHero::AirborneMovement(float DeltaTime)
{
    FVector DesiredMovement = Mathf::LocalInput(HeroController->GetMoveInput(), Camera) * MaxRun;
    CurrentVelocity = Mathf::MoveTowards(CurrentVelocity, DesiredMovement, AirAcceleration * DeltaTime);
    CurrentVelocity.Z = verticalMoveSpeed;
}

void AHero::AirborneRotation(float DeltaTime)
{
}

void AHero::OnGroundHit()
{
    verticalMoveSpeed = 0;
}

void AHero::Jump()
{
    currentJumpSpeed = FMath::Lerp(NormalJumpSpeedMin, NormalJumpSpeedMax, speed / MaxRun);
    gravity = NormalJumpSpeedGravity;
    GetKCCMovementComponent()->ForceUnground(.1f);
    verticalMoveSpeed = currentJumpSpeed * Mathf::OneDivided(deltaTime);
    HeroStateMachine->SetState(AirborneState);
}


void AHero::HandleGravity(float DeltaTime)
{
    verticalMoveSpeed -= gravity * Mathf::OneDivided(DeltaTime);
}

UStateMachine* AHero::GetStateMachine() const
{
    return HeroStateMachine;
}


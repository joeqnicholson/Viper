// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"
#include "Mathf.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeroAirborneState.h"
#include "HeroGroundedState.h"


AHero::AHero()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
    Camera = FindComponentByClass<UCameraComponent>();
}

void AHero::InitializeStateMachine()
{
    // Create the state machine
    HeroStateMachine = new StateMachine();

    // Create the grounded and airborne states, passing `this` so they can access `AHero`
    GroundedState = new HeroGroundedState(this);
    AirborneState = new HeroAirborneState(this);

    // Set the initial state based on the current grounded state
    if (IsGrounded())
    {
        HeroStateMachine->SetState(GroundedState);
    }
    else
    {
        HeroStateMachine->SetState(AirborneState);
    }
}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
    Super::SetupPlayerInputComponent(InInputComponent);
	UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent called on AHero"));
    InInputComponent->BindAxis("MoveY", this, &AHero::ReceiveInputY);
    InInputComponent->BindAxis("MoveX", this, &AHero::ReceiveInputX);
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (HeroStateMachine && HeroStateMachine->GetCurrentState())
    {
        HeroStateMachine->GetCurrentState()->Update(DeltaTime);
    }
}


void AHero::GroundedMovement(float DeltaTime)
{

    if (MoveInput.Length() > 0.2f)
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

    if (MoveInput.Length() > 0.5f)
    {
        rotationInput = Mathf::LocalInput(MoveInput, Camera);
    }

    CurrentRotation = FMath::RInterpTo(CurrentRotation, rotationInput, DeltaTime, turnSpeed);

}

void AHero::AirborneMovement(float DeltaTime)
{
}

void AHero::AirborneRotation(float DeltaTime)
{
}

void AHero::HandleGravity(float DeltaTime)
{
}


void AHero::ReceiveInputY(float YValue)
{
    MoveInput.Y = YValue;
}

void AHero::ReceiveInputX(float XValue)
{
    MoveInput.X = XValue;
}

StateMachine* AHero::GetStateMachine() const
{
    return HeroStateMachine;
}


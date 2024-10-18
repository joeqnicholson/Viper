// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "KCC.h"
#include "KCCMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AKCC::AKCC()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Our root component will be a sphere that reacts to physics
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    CapsuleComponent->InitCapsuleSize(34.0f, 88.0f); // Adjust the size as needed
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	RootComponent = CapsuleComponent;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Create an instance of our movement component, and tell it to update our root component.
    MovementComponent = CreateDefaultSubobject<UKCCMovementComponent>(TEXT("Good Movement Component"));
    MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AKCC::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AKCC::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}

UKCCMovementComponent* AKCC::GetKCCMovementComponent() const
{
    return MovementComponent;
}

void AKCC::Move(FVector CurrentVelocity)
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->AddInputVector(CurrentVelocity);
    }
}

void AKCC::Rotate(FRotator CurrentRotation)
{
    SetActorRotation(CurrentRotation);
}

bool AKCC::IsGrounded() const
{
    // Ensure MovementComponent is valid, then return its bGrounded value
    return MovementComponent ? MovementComponent->IsGrounded() : false;
}
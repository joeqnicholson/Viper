// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KCC.generated.h"

UCLASS()
class VIPER_API AKCC : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AKCC();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    bool IsGrounded() const;

    UPROPERTY()
    class UKCCMovementComponent* MovementComponent;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

    virtual UPawnMovementComponent* GetMovementComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Move(FVector CurrentVelocity);
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Rotate(FRotator CurrentRotation);

};
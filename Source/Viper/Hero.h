#pragma once

#include "CoreMinimal.h"
#include "KCC.h"
#include "Mathf.h"
#include "Camera/CameraComponent.h"
#include "StateMachine.h"
#include "Hero.generated.h"

class UState;
class HeroAirborneState;
class HeroGroundedState;
class AHeroController;

UCLASS()
class VIPER_API AHero : public AKCC
{
    GENERATED_BODY()

public:
    // Constructor
    AHero();

	void GroundedMovement(float DeltaTime);
	void GroundedRotation(float DeltaTime);
    void HandleGravity(float DeltaTime);
    void AirborneMovement(float DeltaTime);
    void AirborneRotation(float DeltaTime);
	void HandleInput();
    void OnGroundHit();
    void Jump();

    // Gravity and movement-related properties exposed to the editor
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float MaxRun;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float TurnSpeedWhileSlow;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float TurnSpeedWhileFast;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Acceleration;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float Deceleration;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float GravityUp;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float GravityDown;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float AirAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float gravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float turnSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float verticalMoveSpeed;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float currentJumpSpeed;

    UStateMachine* GetStateMachine() const;
	FVector CurrentVelocity;
	FRotator CurrentRotation;
	FRotator rotationInput;
	UCameraComponent* Camera;

    float deltaTime = 0;
    const float NormalJumpSpeedMin = 17.0f;
    const float NormalJumpSpeedMax = 19.5f;
    const float NormalJumpSpeedGravity = 1.5f;
    const float NormalVarJumpTimer = 0.167f;

    UState* GetAirborneState() const { return AirborneState; }
    UState* GetGroundedState() const { return GroundedState; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
	
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

    // State machine and states
    UPROPERTY();
    UStateMachine* HeroStateMachine;
    UPROPERTY();
    UState* AirborneState;
    UPROPERTY();
    UState* GroundedState;
    UPROPERTY();
    AHeroController* HeroController;
    
    void InitializeStateMachine();

};

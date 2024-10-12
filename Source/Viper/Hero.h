#pragma once

#include "CoreMinimal.h"
#include "KCC.h"
#include "Mathf.h"
#include "Camera/CameraComponent.h"
#include "StateMachine.h"
#include "Hero.generated.h"

class IState;
class HeroAirborneState;
class HeroGroundedState;

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
	void ReceiveInputY(float YValue);
	void ReceiveInputX(float XValue);

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
    float JumpHeight;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float GravityUp;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float GravityDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FVector MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float gravity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
    float turnSpeed;


    StateMachine* GetStateMachine() const;
	FVector CurrentVelocity;
	FRotator CurrentRotation;

	FRotator rotationInput;
	UCameraComponent* Camera;

    IState* GetAirborneState() const { return AirborneState; }
    IState* GetGroundedState() const { return GroundedState; }

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
    StateMachine* HeroStateMachine;
    IState* AirborneState;
    IState* GroundedState;
    
    void InitializeStateMachine();

};

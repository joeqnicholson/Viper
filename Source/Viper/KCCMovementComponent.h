#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "KCCMovementComponent.generated.h"

class UCapsuleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VIPER_API UKCCMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

public:
    // Constructor
    UKCCMovementComponent();

    // Override the TickComponent function to implement custom movement logic
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Checks if the character is grounded (public accessor)

    bool IsGrounded() const;
    float MaxSlopeAngle = 50.0f; // Maximum slope angle in degrees
    float MaxAngleDifference = 60.0f; // Maximum allowed difference between normals in degrees
    float MaxStepHeight = 60.0f; // // Maximum step height the character can step onto
    float GroundCheckDistanceFlat = 10.0f; // Extra distance under the capsule that is check for ground
    float GroundCheckDistanceSteep = 70.0f; // Extra distance under the capsule that is check for ground
    FVector GroundNormal = FVector::ZeroVector; // Track the normal of the ground last frame
    FVector GroundNormalLastFrame = FVector::ZeroVector; // Track the normal of the current ground
    float ForceNotGroundedTimer;
    void ForceUnground(float Time);

protected:
    // Boolean to track if the character is grounded
    bool bGrounded;

    // Reference to the capsule component for dimensions
    UPROPERTY()
    UCapsuleComponent* CapsuleComponent;

private:
    // Initialize the capsule component reference
    void InitializeCapsuleComponent();

    // Handles stepping up and down small obstacles
    void HandleStepping(FVector& MovementVector);
};

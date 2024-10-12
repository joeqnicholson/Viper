#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "KCCMovementComponent.generated.h"

UCLASS()
class VIPER_API UKCCMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

public:
    // Overrides the TickComponent function to include custom movement and slope handling
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Checks if the pawn is grounded
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    bool bGrounded;

    // Distance for ground check
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float GroundCheckDistance = 100.0f; // Default distance for ground check
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachine.generated.h"

// Forward declaration of the base state interface
class UState;

UCLASS()
class VIPER_API UStateMachine : public UObject
{
    GENERATED_BODY()

public:
    UStateMachine();

    void SetState(UState* NewState);
    void Update(float DeltaTime);
    UState* GetCurrentState() const;
    float StateTimer;
    float* GetStateTime();

private:
    TWeakObjectPtr<UState> CurrentState; // Use TWeakObjectPtr for safe referencing
};

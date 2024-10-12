#pragma once

#include "CoreMinimal.h"

// Forward declaration of the base state interface
class IState;

class VIPER_API StateMachine
{
public:
    StateMachine();
    ~StateMachine();

    // Sets a new state and handles transition
    void SetState(IState* NewState);

    // Updates the current state
    void Update(float DeltaTime);

    IState* GetCurrentState() const;

private:
    IState* CurrentState;
};

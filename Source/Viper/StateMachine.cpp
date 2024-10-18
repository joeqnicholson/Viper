#include "StateMachine.h"
#include "UState.h"

UStateMachine::UStateMachine()
    : CurrentState(nullptr) // Initialize CurrentState to nullptr
{
}

void UStateMachine::SetState(UState* NewState)
{
    StateTimer = 0;

    FString message = FString::Printf(TEXT("SetState"));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, message);


    if (CurrentState.IsValid())
    {
        CurrentState->Exit();
    }

    CurrentState = NewState;

    if (CurrentState.IsValid())
    {
        CurrentState->Enter();
    }
}

void UStateMachine::Update(float DeltaTime)
{
    if (CurrentState.IsValid())
    {
        StateTimer += DeltaTime;
        CurrentState->Update(DeltaTime);
    }
}

float* UStateMachine::GetStateTime()
{
    return &StateTimer;
}

UState* UStateMachine::GetCurrentState() const
{
    return CurrentState.Get(); // Use Get() to retrieve the raw pointer
}

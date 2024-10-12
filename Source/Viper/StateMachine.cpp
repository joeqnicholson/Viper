#include "StateMachine.h"
#include "IState.h"

StateMachine::StateMachine()
    : CurrentState(nullptr)
{
}

StateMachine::~StateMachine()
{
    if (CurrentState)
    {
        CurrentState->Exit();
    }
}

void StateMachine::SetState(IState* NewState)
{
    if (CurrentState)
    {
        CurrentState->Exit();
    }

    CurrentState = NewState;

    if (CurrentState)
    {
        CurrentState->Enter();
    }
}

void StateMachine::Update(float DeltaTime)
{
    if (CurrentState)
    {
        CurrentState->Update(DeltaTime);
    }
}

IState* StateMachine::GetCurrentState() const
{
    return CurrentState;
}
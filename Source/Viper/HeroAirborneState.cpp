#include "HeroAirborneState.h"
#include "Hero.h"

HeroAirborneState::HeroAirborneState(AHero* InHero)
    : H(InHero)
{
}

void HeroAirborneState::Enter()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero has entered the Airborne State."));
        // Example: Initialize airborne-specific variables or reset grounded variables
    }
}

void HeroAirborneState::Exit()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero is exiting the Airborne State."));
        // Cleanup or reset anything specific to the airborne state if needed
    }
}

void HeroAirborneState::Update(float DeltaTime)
{
    if (H)
    {

        // Call centralized methods in Hero for airborne mechanics
        H->HandleGravity(DeltaTime);
        H->AirborneMovement(DeltaTime);

        // Check if the Hero has landed and transition back to the GroundedState
        if (H->IsGrounded())
        {
            H->GetStateMachine()->SetState(H->GetGroundedState());
        }

    }
}

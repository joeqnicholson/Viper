#include "HeroGroundedState.h"
#include "Hero.h"

HeroGroundedState::HeroGroundedState(AHero* InHero)
    : H(InHero)
{
}

void HeroGroundedState::Enter()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero has entered the Grounded State."));
        // Example: Reset jump variables, or initialize grounded-specific variables
    }
}

void HeroGroundedState::Exit()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero is exiting the Grounded State."));
        // Cleanup or reset anything specific to the grounded state if needed
    }
}

void HeroGroundedState::Update(float DeltaTime)
{
    if (H)
    {
        // Call centralized methods in Hero for core mechanics
        H->HandleGravity(DeltaTime);
        H->GroundedMovement(DeltaTime);
        // Transition to AirborneState if the character is no longer on the ground
        if (!H->IsGrounded())
        {
            H->GetStateMachine()->SetState(H->GetAirborneState());
        }
    }
}

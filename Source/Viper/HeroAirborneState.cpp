#include "HeroAirborneState.h"
#include "Hero.h"
#include "Engine/Engine.h"


UHeroAirborneState::UHeroAirborneState()
    : H(nullptr) // Initialize H to nullptr
{
    Name = TEXT("Airborne");
}

void UHeroAirborneState::Initialize(AHero* Hero)
{
    H = Hero; // Initialize H with the passed pointer
    // Debug message to confirm initialization
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("UHeroAirborneState initialized with Hero: %s"), *H->GetName());
    }
}

void UHeroAirborneState::Enter()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero has entered the Airborne State."));
        // Example: Initialize airborne-specific variables or reset grounded variables
    }
}

void UHeroAirborneState::Exit()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero is exiting the Airborne State."));
        // Cleanup or reset anything specific to the airborne state if needed
    }
}

void UHeroAirborneState::Update(float DeltaTime)
{

    if (H)
    {
        // Call centralized methods in Hero for airborne mechanics
        H->HandleGravity(DeltaTime);
        H->AirborneMovement(DeltaTime);

        if (GEngine)
        {
            float stateTime = *H->GetStateMachine()->GetStateTime();
            FString message = FString::Printf(TEXT("Updating Airborne State. State Time: %f"), stateTime);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, message);
        }

        // Check if the Hero has landed and transition back to the GroundedState
        if (H->IsGrounded() && *H->GetStateMachine()->GetStateTime() > 0.05f)
        {
            H->GetStateMachine()->SetState(H->GetGroundedState());
        }

    }
}

#include "HeroGroundedState.h"
#include "Hero.h"
#include "Engine/Engine.h"


UHeroGroundedState::UHeroGroundedState()
    : H(nullptr) // Initialize H to nullptr
{
}

void UHeroGroundedState::Initialize(AHero* Hero)
{
    H = Hero; // Initialize H with the passed pointer
    // Debug message to confirm initialization
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("UHeroAirborneState initialized with Hero: %s"), *H->GetName());
    }
}

void UHeroGroundedState::Enter()
{
    if (H)
    {
        H->OnGroundHit();
        UE_LOG(LogTemp, Log, TEXT("Hero has entered the Grounded State."));
        // Example: Reset jump variables, or initialize grounded-specific variables
    }
}

void UHeroGroundedState::Exit()
{
    if (H)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero is exiting the Grounded State."));
        // Cleanup or reset anything specific to the grounded state if needed
    }
}

void UHeroGroundedState::Update(float DeltaTime)
{
    if (H)
    {

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Updating Grounded State."));
        }
        
        H->GroundedMovement(DeltaTime);
        H->GroundedRotation(DeltaTime);
        // Transition to AirborneState if the character is no longer on the ground
        if (!H->IsGrounded())
        {
            H->GetStateMachine()->SetState(H->GetAirborneState());
        }
    }
}

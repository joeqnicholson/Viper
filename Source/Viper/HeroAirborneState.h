#pragma once

#include "CoreMinimal.h"
#include "UState.h"
#include "HeroAirborneState.generated.h"

// Forward declaration of the Hero class
class AHero;

UCLASS()
class VIPER_API UHeroAirborneState : public UState
{
    GENERATED_BODY()

public:
    // Constructor that takes a pointer to the Hero character
    UHeroAirborneState();
    void Initialize(AHero* Hero) override;

    // Implement the UState interface methods
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;

private:
    AHero* H;  // Pointer to the Hero character
};

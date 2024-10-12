#pragma once

#include "CoreMinimal.h"
#include "IState.h"
#include "Hero.h"

// Forward declaration of the Hero class
class AHero;

class VIPER_API HeroAirborneState : public IState
{
public:
    // Constructor that takes a pointer to the Hero character
    HeroAirborneState(AHero* InHero);

    // Implement the IState interface methods
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float DeltaTime) override;

private:
    AHero* H;  // Shortened variable name for Hero
};

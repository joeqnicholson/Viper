#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UState.generated.h"

class AHero;

UCLASS(Abstract)
class VIPER_API UState : public UObject
{
    GENERATED_BODY()

public:

    virtual void Initialize(AHero* Hero) {}
    // Called when entering the state
    virtual void Enter() {}

    // Called when exiting the state
    virtual void Exit() {}

    // Called to update the state
    virtual void Update(float DeltaTime) {}

    FString Name = "Default State";

    FString GetName() const { return Name; }
private:
};

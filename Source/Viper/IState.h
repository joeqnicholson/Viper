#pragma once

#include "CoreMinimal.h"

// Declare the IState interface
class VIPER_API IState
{
public:
    virtual ~IState() = default;  // Virtual destructor for base class

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(float DeltaTime) = 0;
};

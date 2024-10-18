#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HeroController.generated.h"

UCLASS()
class VIPER_API AHeroController : public APlayerController
{
    GENERATED_BODY()

public:
    AHeroController();

    // Setup the input bindings
    void InitializeInput(UInputComponent* PlayerInputComponent);

    // Checks if the jump action is being held
    bool IsJumpHeld() const;

    // Functions to handle jump input
    void OnJumpPressed();
    void OnJumpReleased();
	void ReceiveInputY(float YValue);
	void ReceiveInputX(float XValue);
	FVector GetMoveInput() const;

private:
    // Tracks whether the jump action is being held
    bool bJumpHeld;
	FVector moveInput;
};

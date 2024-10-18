#include "HeroController.h"

AHeroController::AHeroController()
{
    // Set default values
    bJumpHeld = false;
}

void AHeroController::InitializeInput(UInputComponent* PlayerInputComponent)
{
    // Bind the "Jump" action to our functions
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHeroController::OnJumpPressed);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHeroController::OnJumpReleased);
    PlayerInputComponent->BindAxis("MoveY", this, &AHeroController::ReceiveInputY);
    PlayerInputComponent->BindAxis("MoveX", this, &AHeroController::ReceiveInputX);
}

void AHeroController::ReceiveInputY(float YValue)
{
    moveInput.Y = YValue;
}

void AHeroController::ReceiveInputX(float XValue)
{
    moveInput.X = XValue;
}

void AHeroController::OnJumpPressed()
{
    // Set the state to true when the jump button is pressed
    bJumpHeld = true;
    UE_LOG(LogTemp, Warning, TEXT("Jump button pressed!"));
}

void AHeroController::OnJumpReleased()
{
    // Set the state to false when the jump button is released
    bJumpHeld = false;
    UE_LOG(LogTemp, Warning, TEXT("Jump button released!"));
}

bool AHeroController::IsJumpHeld() const
{
    return bJumpHeld;
}

FVector AHeroController::GetMoveInput() const
{
    return moveInput;
}

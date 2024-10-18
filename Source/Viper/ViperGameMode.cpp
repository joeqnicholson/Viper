#include "ViperGameMode.h"
#include "ViperCharacter.h"
#include "HeroController.h"

AViperGameMode::AViperGameMode()
{
    // Set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Hero"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // Directly assign the C++ HeroController class
    PlayerControllerClass = AHeroController::StaticClass();
}

#include "GameFramework/NBSPlayerController.h"
#include "Components/NinjaInputManagerComponent.h"

ANBSPlayerController::ANBSPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName InputManagerName = FName("InputManager");
    InputManager = CreateDefaultSubobject<UNinjaInputManagerComponent>(InputManagerName);
}

#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaInputManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName InputManagerName = TEXT("InputManager");
	InputManager = CreateDefaultSubobject<UNinjaInputManagerComponent>(InputManagerName);
}

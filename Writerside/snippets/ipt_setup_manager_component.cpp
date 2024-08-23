#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaInputManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName EquipmentComponentName = TEXT("InputManager");
	InputManager = CreateDefaultSubobject<UNinjaInputManagerComponent>(EquipmentComponentName);
}

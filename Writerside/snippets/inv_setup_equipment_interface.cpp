#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaEquipmentManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName EquipmentComponentName = TEXT("EquipmentManager");
	EquipmentManagerComponent = CreateOptionalDefaultSubobject<UNinjaEquipmentManagerComponent>(EquipmentComponentName);
}

UNinjaEquipmentManagerComponent* APluginLabsCharacter::GetEquipmentManager_Implementation() const
{
	return EquipmentManagerComponent;
}
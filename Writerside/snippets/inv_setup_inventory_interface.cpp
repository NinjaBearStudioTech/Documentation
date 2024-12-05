#include "GameFramework/PluginLabsPlayerState.h"
#include "Components/NinjaInventoryManagerComponent.h"

APluginLabsPlayerState::APluginLabsPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName InventoryComponentName = TEXT("InventoryManager");
	InventoryManagerComponent = CreateOptionalDefaultSubobject<UNinjaInventoryManagerComponent>(InventoryComponentName);
}

UNinjaInventoryManagerComponent* APluginLabsPlayerState::GetInventoryManager_Implementation() const
{
	return InventoryManagerComponent;
}
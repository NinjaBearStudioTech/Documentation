#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaFactionComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName FactionComponentName = TEXT("FactionManager");
	FactionManager = CreateOptionalDefaultSubobject<UNinjaFactionComponent>(FactionComponentName);
}

UNinjaFactionComponent* APluginLabsCharacter::GetFactionComponent_Implementation() const
{
	return FactionManager;
}
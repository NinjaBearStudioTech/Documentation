#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaCombatActorPoolComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static const FName ActorPoolName = TEXT("ActorPool");
	ActorPool = CreateDefaultSubobject<UNinjaCombatActorPoolComponent>(ActorPoolName);
}

UNinjaCombatActorPoolComponent* APluginLabsCharacter::GetActorPool_Implementation() const
{
	return ActorPool;
}

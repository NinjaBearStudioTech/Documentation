// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/PluginLabsWeaponActor.h"

#include "NinjaCombatTags.h"
#include "Net/UnrealNetwork.h"

APluginLabsWeaponActor::APluginLabsWeaponActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bReplicates = true;
    WeaponTags = FGameplayTagContainer::EmptyContainer;
}

void APluginLabsWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, WeaponTags);
}


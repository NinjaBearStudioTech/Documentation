#include "GameFramework/PluginLabsCharacter.h"

#include "Components/NinjaCombatManagerComponent.h"
#include "Components/NinjaCombatWeaponManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static const FName CombatManagerName = TEXT("CombatManager");
	CombatManager = CreateDefaultSubobject<UNinjaCombatManagerComponent>(CombatManagerName);

    // Create this as an optional sub-object, so we may change later on for the Inventory integration.
	static const FName WeaponManagerName = TEXT("WeaponManager");
	WeaponManager = CreateOptionalDefaultSubobject<UNinjaCombatWeaponManagerComponent>(WeaponManagerName);
}

USkeletalMeshComponent* APluginLabsCharacter::GetCombatMesh_Implementation() const
{
	return GetMesh();
}

UNinjaCombatManagerComponent* APluginLabsCharacter::GetCombatManager_Implementation() const
{
	return CombatManager;
}

UActorComponent* APluginLabsCharacter::GetWeaponManagerComponent_Implementation() const
{
	return WeaponManager;
}
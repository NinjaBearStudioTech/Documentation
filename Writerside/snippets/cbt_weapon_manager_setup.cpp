#include "GameFramework/PluginLabsCharacter.h"

#include "Components/NinjaCombatManagerComponent.h"
#include "Components/NinjaCombatWeaponManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static const FName CombatManagerName = TEXT("CombatManager");
	CombatManager = CreateDefaultSubobject<UNinjaCombatManagerComponent>(CombatManagerName);

	static const FName WeaponManagerName = TEXT("WeaponManager");
	WeaponManager = CreateDefaultSubobject<UNinjaCombatWeaponManagerComponent>(WeaponManagerName);
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
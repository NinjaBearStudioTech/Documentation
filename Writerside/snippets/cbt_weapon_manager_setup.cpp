#include "GameFramework/PluginLabsCharacter.h"
#include "Components/NinjaCombatWeaponManagerComponent.h"

APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    static const FName LeaderMeshName = TEXT("LeaderMesh");
    LeaderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(LeaderMeshName);
    // ...

	static const FName WeaponManagerName = TEXT("WeaponManager");
	WeaponManager = CreateDefaultSubobject<UNinjaCombatWeaponManagerComponent>(WeaponManagerName);
}

USkeletalMeshComponent* APluginLabsCharacter::GetCombatMesh_Implementation() const
{
	return LeaderMesh;
}

UActorComponent* APluginLabsCharacter::GetWeaponManagerComponent_Implementation() const
{
	return WeaponManager;
}
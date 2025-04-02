#include "Components/NinjaCombatWeaponManagerComponent.h"

FName ANBSCharacter::WeaponManagerName = "WeaponManager";

ANBSCharacter::ANBSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // ...
    WeaponManager = CreateOptionalDefaultSubobject<UNinjaCombatWeaponManagerComponent>(WeaponManagerName);
}

UActorComponent* ANBSCharacter::GetWeaponManagerComponent_Implementation() const
{
    return WeaponManager;
}
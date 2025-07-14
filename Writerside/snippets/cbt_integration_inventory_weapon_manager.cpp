// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/SurvivalPlayerCharacter.h"

ASurvivalPlayerCharacter::ASurvivalPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    EquipmentWeaponManager = CreateDefaultSubobject<NinjaCombatEquipmentAdapterComponent>("EquipmentWeaponManager");
}

ASurvivalPlayerCharacter::GetWeaponManager_Implementation()
{
    return EquipmentWeaponManager;
}
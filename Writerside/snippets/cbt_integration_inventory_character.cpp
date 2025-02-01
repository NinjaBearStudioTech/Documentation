#include "GameFramework/CombatCharacter.h"
#include "Components/IntegratedWeaponEquipmentComponent.h"

ACombatCharacter::ACombatCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static const FName WeaponManagerName = TEXT("WeaponManager");
	WeaponManager = CreateDefaultSubobject<UIntegratedWeaponEquipmentComponent>(WeaponManagerName);
};

UActorComponent* ACombatCharacter::GetWeaponManagerComponent() const
{
    return WeaponManager;
}
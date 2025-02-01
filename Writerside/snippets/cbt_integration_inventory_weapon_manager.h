// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Components/CombatWeaponManagerInterface.h"
#include "IntegratedWeaponEquipmentComponent.generated.h"

/**
 * Integration between Combat (Weapon Manager) and Inventory (Equipment Manager).
 */
UCLASS(Abstract)
class PLUGINLABS_API UIntegratedWeaponEquipmentComponent : public UActorComponent, public ICombatWeaponManagerInterface
{

	GENERATED_BODY()

public:

	// -- Begin Weapon Repository implementation
	virtual AActor* GetWeapon_Implementation(const FGameplayTagQuery& WeaponQuery) const override;
	// -- End Weapon Repository implementation

};

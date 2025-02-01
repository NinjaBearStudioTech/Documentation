// Ninja Bear Studio Inc., all rights reserved.
#include "Components/IntegratedWeaponEquipmentComponent.h"

#include "NinjaCombatLog.h"
#include "Interfaces/CombatWeaponInterface.h"
#include "NinjaEquipmentFunctionLibrary.h"
#include "Components/NinjaEquipmentManagerComponent.h"
#include "GameFramework/NinjaEquipment.h"

AActor* UIntegratedWeaponEquipmentComponent::GetWeapon_Implementation(const FGameplayTagQuery& WeaponQuery) const
{
	AActor* WeaponActor = nullptr;

	const UNinjaEquipmentManagerComponent* EquipmentManager = UNinjaEquipmentFunctionLibrary::GetEquipmentManager(GetOwner());
	if (!IsValid(EquipmentManager))
	{
		COMBAT_LOG(Warning, "No equipment manager assigned to the owner.");
		return WeaponActor;
	}

	const UNinjaEquipment* Equipment = EquipmentManager->GetFirstEquipmentByQuery(WeaponQuery);
	if (!IsValid(Equipment))
	{
		COMBAT_LOG_ARGS(Verbose, "No equipment found for query: %s.", *WeaponQuery.GetDescription());
		return WeaponActor;
	}

	WeaponActor = Equipment->GetEffectCauserActor();
	if (!IsValid(WeaponActor) || !WeaponActor->Implements<UCombatWeaponInterface>())
	{
		COMBAT_LOG_ARGS(Warning, "Equipment %s does not have an Effect Causer Actor.", *GetNameSafe(Equipment));
		return WeaponActor;
	}

	return WeaponActor;
}

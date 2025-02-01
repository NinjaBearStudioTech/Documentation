// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/IntegratedEquipmentWeaponActor.h"

#include "Components/NinjaEquipmentManagerComponent.h"
#include "Components/NinjaEquipmentReceiverComponent.h"
#include "GameFramework/NinjaEquipment.h"
#include "GameFramework/NinjaInventoryItem.h"
#include "GameFramework/ItemFragments/ItemFragment_Level.h"

AIntegratedEquipmentWeaponActor::AIntegratedEquipmentWeaponActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static const FName EquipmentReceiverName = TEXT("EquipmentReceiver");
	EquipmentReceiver = CreateDefaultSubobject<UNinjaEquipmentReceiverComponent>(EquipmentReceiverName);
}

AActor* AIntegratedEquipmentWeaponActor::GetWeaponOwner_Implementation() const
{
	if (IsValid(EquipmentReceiver) && EquipmentReceiver->Implements<UEquipmentActorInterface>())
	{
		const UNinjaEquipment* Equipment = IEquipmentActorInterface::Execute_GetEquipment(EquipmentReceiver);
		if (IsValid(Equipment))
		{
			return Equipment->GetEquipmentManager()->GetOwner();
		}
	}

	// No integration or no receiver/equipment. Use the default weapon method.
	// It will most likely attempt to find the actor to which this one is attached to.
	//
	return Super::GetWeaponOwner_Implementation();
}

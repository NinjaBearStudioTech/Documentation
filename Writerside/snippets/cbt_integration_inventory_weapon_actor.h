// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaCombatWeaponActor.h"
#include "IntegratedEquipmentWeaponActor.generated.h"

class UNinjaEquipmentReceiverComponent;

/**
 * A weapon actor that is prepared to be used with Equipment instances.
 */
UCLASS(Abstract, Blueprintable)
class PLUGINLABS_API AIntegratedEquipmentWeaponActor : public ANinjaCombatWeaponActor
{

	GENERATED_BODY()

public:

	AIntegratedEquipmentWeaponActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Weapon implementation
	virtual AActor* GetWeaponOwner_Implementation() const override;
	// -- End Weapon implementation

private:

	UPROPERTY()
	TObjectPtr<UNinjaEquipmentReceiverComponent> EquipmentReceiver;

};

// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatSystemInterface.h"
#include "IntegratedEquipmentWeaponActor.generated.h"

class UIntegratedWeaponEquipmentComponent;

/**
 * Base character class.
 */
UCLASS(Abstract)
class PLUGINLABS_API ACombatCharacter : public ACharacter, public ICombatSystemInterface
{

	GENERATED_BODY()

public:

	ACombatCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    // -- Begin Combat System implementation
    virtual UActorComponent* GetWeaponManagerComponent() const override;
    // -- Begin Combat System implementation

private:

	UPROPERTY()
	TObjectPtr<UIntegratedWeaponEquipmentComponent> WeaponManager;

};

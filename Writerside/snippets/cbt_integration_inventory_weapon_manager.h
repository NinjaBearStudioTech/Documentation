// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatSystemInterface.h"
#include "ASurvivalCharacter.generated.h"

/**
 * Integration between Combat (Weapon Manager) and Inventory (Equipment Manager).
 */
UCLASS(Abstract)
class SURVIVALGAME_API ASurvivalPlayerCharacter : public ACharacter, public ICombatWeaponManagerInterface
{

	GENERATED_BODY()

public:

    ASurvivalPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Weapon Repository implementation
	virtual UActorComponent* GetWeaponManager_Implementation() const override;
	// -- End Weapon Repository implementation

private:

    /** Weapon Manager that adapts the combat system to the equipment manager. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess=true))
    TObjectPtr<NinjaCombatEquipmentAdapterComponent> EquipmentWeaponManager;

};

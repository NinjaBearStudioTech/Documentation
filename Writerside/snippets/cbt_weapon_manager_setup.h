#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatSystemInterface.h"
#include "PluginLabsCharacter.generated.h"

class UNinjaCombatManagerComponent;
class UNinjaCombatWeaponManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ANinjaGASPlayerCharacter, public ICombatSystemInterface
{

	GENERATED_BODY()

public:

	APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Combat System Implementation.
	virtual USkeletalMeshComponent* GetCombatMesh_Implementation() const override;
	virtual UNinjaCombatManagerComponent* GetCombatManager_Implementation() const override;
	virtual UActorComponent* GetWeaponManagerComponent_Implementation() const override;
	// -- End Combat System Implementation.

private:

	/** Main Manager for the Combat System. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaCombatManagerComponent> CombatManager;

	/** Weapon Manager component that will manage weapons for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaCombatWeaponManagerComponent> WeaponManager;

};

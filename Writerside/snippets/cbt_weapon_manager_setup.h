#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatSystemInterface.h"
#include "PluginLabsCharacter.generated.h"

class UNinjaCombatWeaponManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ACharacter, public ICombatSystemInterface
{

	GENERATED_BODY()

public:

	APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Combat System Implementation.
	virtual USkeletalMeshComponent* GetCombatMesh_Implementation() const override;
	virtual UActorComponent* GetWeaponManagerComponent_Implementation() const override;
	// -- End Combat System Implementation.


private:

	/** Main character mesh following the hidden mannequin for animations. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> LeaderMesh;

	/** Weapon Manager component that will manage weapons for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaCombatWeaponManagerComponent> WeaponManager;

};

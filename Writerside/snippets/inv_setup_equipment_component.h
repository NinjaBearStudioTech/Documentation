#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PluginLabsPlayerCharacter.generated.h"

class UNinjaEquipmentManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ACharacter
{

    GENERATED_BODY()

public:

    APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

	/** Hard reference to the Equipment Manager Component used by the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaEquipmentManagerComponent> EquipmentManagerComponent;

};
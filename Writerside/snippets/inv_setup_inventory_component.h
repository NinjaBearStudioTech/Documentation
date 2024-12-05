#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PluginLabsPlayerState.generated.h"

class UNinjaInventoryManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsPlayerState : public APlayerState
{

    GENERATED_BODY()

public:

    APluginLabsPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

	/** Hard reference to the Inventory Manager Component used by the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaInventoryManagerComponent> InventoryManagerComponent;

};
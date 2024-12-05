#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/InventoryManagerProviderInterface.h"
#include "APluginLabsPlayerState.generated.h"

class UNinjaInventoryManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsPlayerState : public APlayerState, public IInventoryManagerProviderInterface
{

    GENERATED_BODY()

public:

    APluginLabsPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    // -- Begin Inventory Provider implementation
    virtual UNinjaInventoryManagerComponent* GetInventoryManager_Implementation() const override;
    // -- End Inventory Provider implementation

private:

	/** Hard reference to the Inventory Manager Component used by the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaInventoryManagerComponent> InventoryManagerComponent;

};
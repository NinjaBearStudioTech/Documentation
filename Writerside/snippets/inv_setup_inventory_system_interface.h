// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/InventorySystemInterface.h"
#include "NBSPlayerState.generated.h"

class UNinjaInventoryManagerComponent;

UCLASS()
class NBSTECH_API ANBSPlayerState : public APlayerState, public IInventorySystemInterface
{
	
    GENERATED_BODY()

public:

    ANBSPlayerState(const FObjectInitializer& ObjectInitializer);

    // -- Begin InventorySystem implementation
    virtual UNinjaInventoryManagerComponent* GetInventoryManager_Implementation() const override;
    // -- End InventorySystem implementation
	
private:

    /** Inventory Manager component. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaInventoryManagerComponent> InventoryManager;
	
};

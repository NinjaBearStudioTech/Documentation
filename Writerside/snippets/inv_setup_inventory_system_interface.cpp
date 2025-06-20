// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/NBSPlayerState.h"

#include "Components/NinjaInventoryManagerComponent.h"

ANBSPlayerState::ANBSPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    InventoryManager = CreateDefaultSubobject<UNinjaInventoryManagerComponent>(TEXT("InventoryManager"));
}

UNinjaInventoryManagerComponent* ANBSPlayerState::GetInventoryManager_Implementation() const
{
    return InventoryManager;
}

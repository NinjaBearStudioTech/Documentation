#include "Components/NinjaInventoryManagerComponent.h"

ANBSPlayerState::ANBSPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    InventoryManager = CreateDefaultSubobject<UNinjaInventoryManagerComponent>(TEXT("InventoryManager"));
}

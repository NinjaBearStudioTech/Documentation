UFUNCTION()
void HandleContainerEvent(UInventoryContainer* Container, FGameplayTag EventTag, FInstancedStruct Payload);

UFUNCTION()
void HandleItemEvent(UInventoryItem* Item, FGameplayTag EventTag, FInstancedStruct Payload);
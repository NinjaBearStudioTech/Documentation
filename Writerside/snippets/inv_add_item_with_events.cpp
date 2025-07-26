void UInventoryExamples::AddItem(const UNinjaInventoryItemDataAsset* ItemData, int32 StackSize)
{
    TArray<FInventoryDefaultItemMemory> DefaultMemories;

    FInventoryDefaultItemMemory StackMemory = UNinjaInventoryFunctionLibrary::CreateStackMemory(StackSize);
    Memories.Add(StackMemory);

	FInventoryDefaultItem DefaultItem = UNinjaInventoryFunctionLibrary::CreateDefaultItem(ItemData, DefaultMemories);

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
    InventoryManager->OnItemEvent.AddDynamic(this, &ThisClass::OnItemEvent);
    
    FInventoryItemInitializationCallback Callback;
    Callback.BindDynamic(this, &ThisClass::OnItemLifecycleChanged);
	FGuid ItemId = InventoryManager->AddItemWithCallback(DefaultItem, Callback);
}

// UFUNCTION
void UInventoryExamples::OnItemLifecycleChanged(const UNinjaInventoryItem* Item, EInventoryItemLifecycle Lifecycle)
{
    // Item changed the initialization state.
}

// UFUNCTION
void UInventoryExamples::OnItemEvent(const UNinjaInventoryItem* Item, FGameplayTag EventTag, FInstancedStruct Payload)
{
    if (EventTag == Tag_Inventory_Event_Item_AddedToInventory)
    {
        // Item was added to the inventory.
    }
}


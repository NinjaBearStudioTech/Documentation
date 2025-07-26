void UInventoryExamples::AddItem(const UNinjaInventoryItemDataAsset* ItemData, int32 StackSize)
{
    TArray<FInventoryDefaultItemMemory> DefaultMemories;

    FInventoryDefaultItemMemory StackMemory = UNinjaInventoryFunctionLibrary::CreateStackMemory(StackSize);
    Memories.Add(StackMemory);

	FInventoryDefaultItem DefaultItem = UNinjaInventoryFunctionLibrary::CreateDefaultItem(ItemData, DefaultMemories);

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
	FGuid ItemId = InventoryManager->AddItem(DefaultItem);

	if (ItemId.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Item added!"));
	}
}

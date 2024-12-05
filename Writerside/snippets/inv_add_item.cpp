void UInventoryExamples::AddItem(const UNinjaInventoryItemDataAsset* ItemData, const TArray<FInventoryDefaultItemMemory>& DefaultMemories)
{
	FInventoryItemContext ItemContext, ResultContext;
	ItemContext = UNinjaInventoryFunctionLibrary::CreateItemContext(ItemData, DefaultMemories);

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
	InventoryManager->AddItem(ItemContext, ResultContext);

	if (ResultContext.IsSuccessful())
	{
		UE_LOG(LogTemp, Log, TEXT("Item added!"));
	}
}
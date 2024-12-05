void UInventoryExamples::AddHealthPotion()
{
	TArray<FInventoryDefaultItemMemory> Memories;

	const int32 StackSize = 5;
	const FInventoryDefaultItemMemory StackMemory = UNinjaInventoryGameplayFunctionLibrary::CreateStackMemory(StackSize);
	Memories.Add(StackMemory);

	FInventoryItemContext ItemContext, ResultContext;
	ItemContext = UNinjaInventoryFunctionLibrary::CreateItemContext(PotionItemData, Memories);

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
	InventoryManager->AddItem(ItemContext, ResultContext);

	if (ResultContext.IsSuccessful())
	{
		UE_LOG(LogTemp, Log, TEXT("Potion added!"));
	}
}
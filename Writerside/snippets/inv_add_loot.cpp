void UInventoryExamples::AddLoot(TArray<UNinjaInventoryLoot*> Loot)
{
	FInventoryItemContext ResultContext;

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
	InventoryManager->AddLoot(Loot);

	if (ResultContext.IsSuccessful())
	{
		UE_LOG(LogTemp, Log, TEXT("Loot added!"));
	}
}
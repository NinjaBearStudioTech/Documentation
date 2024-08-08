void UInventoryExamples::AddPickup(AActor* ItemPickup)
{
	FInventoryItemContext ResultContext;

	UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
	InventoryManager->AddPickup(ItemPickup, ResultContext);

	if (ResultContext.IsSuccessful())
	{
		UE_LOG(LogTemp, Log, TEXT("Pickup added!"));
	}
}
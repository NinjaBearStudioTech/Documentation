void UInventoryExamples::RemoveItem(UNinjaInventoryItem* Item, int32 Quantity)
{
    UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
    InventoryManager->RemoveItem(Item, Quantity);
}
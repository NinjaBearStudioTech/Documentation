void UInventoryExamples::RemoveContainer(UNinjaInventoryContainer* Container)
{
    UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
    InventoryManager->RemoveContainer(Container);
}
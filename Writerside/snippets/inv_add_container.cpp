void UInventoryExamples::AddContainer(const UNinjaInventoryContainerDataAsset* ContainerData, UNinjaInventoryItem* SourceItem)
{
    FInventoryContainerContext ContainerContext, ResultContext;
    ContainerContext.SetContainerData(ContainerData);
    ContainerContext.SetOwningItem(Item);

    UNinjaInventoryManagerComponent* InventoryManager = GetInventoryManager();
    InventoryManager->AddContainer(ContainerContext, ResultContext);

    if (ResultContext.IsSuccessful())
    {
        UE_LOG(LogTemp, Log, TEXT("Container added!"));
    }
}
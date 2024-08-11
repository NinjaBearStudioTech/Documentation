void UInventoryExamples::CreateDefaultMemories(const UNinjaInventoryItemDataAsset* ItemData)
{
    // First, create memories using the Gameplay Function Library, where we can find high level functions (i.e. fragments).
    TArray<FInventoryDefaultItemMemory> Memories;

    const int32 StackSize = 10;
    FInventoryDefaultItemMemory StackMemory = UNinjaInventoryGameplayFunctionLibrary::CreateStackMemory(StackSize);
    Memories.Add(StackMemory);

    const UNinjaInventoryContainerDataAsset* PrimaryContainer = GetBackpackContainerData();
    const int32 Position = 5
    FInventoryDefaultItemMemory ContainerMemory = UNinjaInventoryGameplayFunctionLibrary::CreateContainerMemory(PrimaryContainer, Position);
    Memories.Add(ContainerMemory);

    const float Durability = 10.f;
    FInventoryDefaultItemMemory DurabilityMemory = UNinjaInventoryGameplayFunctionLibrary::CreateDurabilityMemory(Durability);
    Memories.Add(DurabilityMemory);

    const float Level = 20.f;
    FInventoryDefaultItemMemory LevelMemory = UNinjaInventoryGameplayFunctionLibrary::CreateLevelMemory(Level);
    Memories.Add(LevelMemory);

    // Using the core Inventory Function Library, where we can find functions for Items and Containers.
    FInventoryItemContext ItemContext = UNinjaInventoryFunctionLibrary::CreateItemContext(ItemData, Memories);
}
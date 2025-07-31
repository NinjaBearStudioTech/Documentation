void UEventHandler::HandleItemEvent(UInventoryItem* Item, FGameplayTag EventTag, FInstancedStruct Payload)
{
    if (EventTag == Tag_Inventory_Event_Item_AddedToInventory)
    {
        const FInventoryItemEventPayload* ItemPayload = Payload.GetPtr<FInventoryItemEventPayload>();
        if (ItemPayload)
        {
            // Handle the event...
        }
    }
}

InventoryManager->OnContainerEvent.AddDynamic(this, &UEventHandler::HandleContainerEvent);
InventoryManager->OnItemEvent.AddDynamic(this, &UEventHandler::HandleItemEvent); 
# Container ViewModel
<primary-label ref="inventory"/>

The **Container ViewModel** wraps a `NinjaInventoryContainer` backend instance and exposes its contents and metadata to 
the user interface.

## Configuration

This ViewModel is created by the `InventoryResolver`. It requires a valid **Container Instance**, which can be assigned 
manually (e.g., during a widget's `OnConstruct` or Blueprint Initialize event), or automatically using the `NinjaInventoryContainerWidget`.

These approaches are covered in the [**ViewModel overview page**](inv_ui_mvvm.md).

## Container Items

The main purpose of this ViewModel is to provide all items currently stored in the container it represents.

Each item is automatically converted into an [`Inventory Item ViewModel`](inv_mvvm_item.md), regardless of whether it is 
a full `Item Instance` or a detached `Item View`.

Optionally, the ViewModel can also provide **empty item entries** to represent unoccupied positions. For example, a backpack 
grid may show all 25 slots (even if some are empty), while a loot list may only display actual items. This is controlled 
by the `bFillEmptyEntries` setting.

## Notifies

A widget can listen to the following fields to drive UI updates:

| Field              | Type     | Description                                                                                                                                     |
|--------------------|----------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetContainer`     | Function | Returns the container currently bound to the ViewModel. May return `null` if no container is assigned.                                          |
| `GetContainerName` | Function | Returns the name of the container, as defined in its **Data Asset**, or an empty text if no container is assigned.                              |
| `GetItems`         | Function | Returns the list of items in the container, as [Item ViewModels](inv_mvvm_item.md). May include empty entries depending on `bFillEmptyEntries`. |

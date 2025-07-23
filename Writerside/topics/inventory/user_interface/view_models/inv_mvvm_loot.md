# Loot ViewModel
<primary-label ref="inventory"/>

The **Loot ViewModel** is responsible for exposing loot entries received by an `Inventory Manager` to the user interface.

It receives these entries in the form of **Default Items**, and converts them into **UI-ready ViewModels**, making them 
compatible with the rest of the inventory UI system.

Once converted, loot can be presented using standard UI widgets (e.g., lists, wrap boxes) powered by **ViewModel Extensions**, 
just like [container-based](inv_mvvm_container.md) displays.

## Configuration

This ViewModel is usually created via the `Inventory Resolver`, and is commonly attached to a **Loot Panel Widget** 
designed to display temporary or received items.

It receives a reference to an `Inventory Manager` that is currently holding pending loot and uses that reference to 
build its internal list of items as **Item ViewModels**.

## Loot Presentation

Loot entries are represented as [`Item ViewModels`](inv_mvvm_item.md), each wrapping a detached **Item View**. These 
ViewModels can be used to display loot details, preview icons, tooltips, and more - following the same structure as any 
other item-driven widget.

> **Loot Entries**
>
> Loot entries use **detached views** (not item instances), which means they are read-only until transferred to the
> player's inventory.
>
> Generated loot will always include the **Source Inventory** from which it was generated. It may also include the
> **Source Item** used to create the loot entry. You can obtain additional information from these.
{style="note"}

## Loot Transfer

The Loot ViewModel also supports **transferring loot** from the loot source into the owning player's `Inventory Manager`. 
This can be triggered using the following functions:

| Function                       | Description                                                                                                                            |
|--------------------------------|----------------------------------------------------------------------------------------------------------------------------------------|
| `TransferLootFromViewModels`   | Accepts an array of `Item ViewModels`, each containing a valid `Item View`, and attempts to transfer them into the player's inventory. |
| `TransferLootFromDefaultItems` | Accepts an array of raw **Default Items**, typically used for direct scripting or logic-based transfers.                               |

These functions can be used to implement "Take All", "Transfer Selected", or even filtered looting behavior.

## Notifies

The following fields can be observed for UI updates:

| Field      | Type     | Description                                                                |
|------------|----------|----------------------------------------------------------------------------|
| `GetItems` | Function | Returns the current loot entries as [`Item ViewModels`](inv_mvvm_item.md). |


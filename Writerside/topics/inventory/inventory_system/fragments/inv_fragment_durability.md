# Durability Fragment
<primary-label ref="inventory"/>

The **Durability** Fragment determines whether an item can wear down and break over time, based on its usage. 

It tracks current durability per item instance and optionally allows items to be repaired or broken, influencing gameplay 
tags like **Broken** or **Indestructible**.

## Fragment Tags
This fragment adds the following tags, representing the **Broken state** and **Indestructible trait**.

| Tag                                   | When Applied                                 |
|---------------------------------------|----------------------------------------------|
| `inventory.item.trait.broken`         | When item durability reaches `0`.            |
| `inventory.item.trait.indestructible` | When `bCanBreak` is `false` on the fragment. |

## Properties
This fragment has the following properties.

| Property     | Description                                                            |
|--------------|------------------------------------------------------------------------|
| `CanBreak`   | Whether the item can lose durability and break.                        |
| `Durability` | Maximum durability of the item. Only relevant if `CanBreak` is `true`. |

## Operations
This fragment exposes the following operations.

| Function                         | Description                                                           |
|----------------------------------|-----------------------------------------------------------------------|
| `CanBreak`                       | Returns `true` if the item is allowed to break.                       |
| `IsBroken`                       | Returns `true` if the given item instance is currently broken.        |
| `IsBrokenFromDefaultMemory`      | Returns whether the specified default item data is in a broken state. |
| `IsIndestructible`               | Returns `true` if this fragment marks the item as indestructible.     |
| `GetMaximumDurability`           | Returns the maximum durability value defined in this fragment.        |
| `GetDurability`                  | Returns the current durability of the given item instance.            |
| `GetDurabilityFromDefaultMemory` | Provides the current durability for a default item data structure.    |
| `SetDurability`                  | Sets the durability value of the item.                                |
| `AddWear`                        | Decreases durability by a given wear amount.                          |
| `Repair`                         | Restores the item's durability to full.                               |

## Memory
This fragment uses `InventoryItemFragmentDurabilityMemory`, to store the current **durability**.

## Event Payload
This fragment emits the following events, using `InventoryItemDurabilityPayload` as the payload structure.

| Event                                    | Description                              |
|------------------------------------------|------------------------------------------|
| `Inventory.Event.Item.DurabilityChanged` | Triggered when durability value changes. |

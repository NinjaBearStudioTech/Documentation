# Loot
<primary-label ref="inventory"/>

The **Loot** fragment allows items within an inventory to be considered for **loot selection**. 

It can be used in conjunction with loot selectors that scan a source inventory - such as defeated enemies or lootable 
containers - to determine which items should be offered to the requesting player.

This fragment is used in conjunction with the **[](inv_inventory_loot.md)**

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Lootable` tag to an item, which introduces the **Lootable** trait.

## Properties
This fragment has the following property.

| Property              | Description                                                                 |
|-----------------------|-----------------------------------------------------------------------------|
| `LootTags`            | Tags applied to the item to mark loot traits (e.g., rarity, category).      |
| `RequiredContextTags` | Context tags that must be present on the requester to make this item valid. |
| `LootWeight`          | Optional scalar for relative loot selection weight. Default is 1.0.         |

## Operations
This fragment does not expose runtime operations.

## Memory
This fragment does **not** use memory replication or persistent memory types.

## Event Payload
This fragment does **not** emit or consume any specific inventory events.
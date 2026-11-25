# Ninja Inventory
<primary-label ref="inventory"/>

![Ninja Inventory](inv_feature.png "Ninja Inventory")

Give a character a bag, let them pick up supplies, and decide what happens when they run out of room. Ninja Inventory supports fixed slots, spatial backpacks, equipment, and storage shared by several players.

## What It Does

An **item definition** describes what a kind of item can do. Fragments give it features such as stacking, consuming, or equipping. The **Inventory Manager** keeps track of the actual items. A **container layout** decides where each one fits.

## Main Features

| What should the player do? | Where to start |
| --- | --- |
| Carry one item or stack in each of six slots | [Build a standard slot-based inventory](inv_guide_simple_grid.md) |
| Pack items of different sizes into a backpack | [Build a spatial grid inventory](inv_guide_spatial_grid.md) |
| Collect, use, or drop supplies | [Create a stackable pickup](inv_guide_inventory_items.md) and [use, store, or drop items](inv_gameplay_abilities.md) |
| Wear gear or switch what is in hand | [Equip an item and change its appearance](inv_guide_equipment.md) |
| Take supplies from a chest and keep them between sessions | [Open a shared loot container](inv_inventory_loot.md) and [save inventory progress](inv_save_and_load.md) |

## How a Pickup Reaches the Bag

When a character picks up arrows, the manager checks whether it can add them. They can join an existing stack or take another position in the bag. The inventory UI reads the resulting item and quantity. Start with [Set Up Ninja Inventory](inv_setup.md), then [give a character a starting item](inv_first_steps.md).

## Integrations

[Combat and Inventory](integration_combat_inventory.md) connects equipped items to weapons. [Interaction and Inventory](integration_interaction_inventory.md) connects a Collect action to an inventory transfer and covers partial pickups.

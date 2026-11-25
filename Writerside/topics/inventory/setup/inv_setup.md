# Set Up Ninja Inventory
<primary-label ref="inventory"/>

## Prerequisites

Start with a playable pawn or a Player State that can own the player's inventory. Fixed-size containers can use inventory data alone. Features such as attribute-driven capacity, consumable Gameplay Effects, and item abilities also need a working Unreal Ability System Component.

## Setup Checklist

| Step | When you need it | Where to go |
| --- | --- | --- |
| Enable Ninja Inventory and its engine dependencies. Add `NinjaInventory` to modules that reference its C++ classes. | Every project (module dependencies apply to C++) | [Install plugins](installing_plugins.md) |
| Register item and container definitions with Unreal's Asset Manager. | Every project | [Asset Manager settings and configuration entries](asset_manager.md) |
| Add an Inventory Manager, a starting container, and one item. | To check that the owner initializes | [First Steps](inv_first_steps.md) |
| Add `NinjaInventoryAttributeSet` to the owner's ability system and initialize the attributes you use. | Attribute-driven slots, weight limits, or wealth | [Initial attribute values](#initialization-data) |

In **Project Settings → Asset Manager → Primary Asset Types to Scan**, register `InventoryContainerData` with base class `NinjaInventoryContainerDataAsset` and `InventoryItemData` with base class `NinjaInventoryItemDataAsset`. Add the folders where you will create the assets, for example `/Game/Data/Containers` and `/Game/Data/Items`. Use non-Blueprint primary assets and **Always Cook** so the same definitions are available in a packaged build.

## Choose Your Setup Guide

- [Build a Standard Slot-Based Inventory](inv_guide_simple_grid.md) sets up a six-slot bag, its item widgets, and the full-bag test.
- [Build a Spatial Grid Inventory](inv_guide_spatial_grid.md) sets up a backpack with item footprints, rotation, and separate cell and item widgets.

Both guides use the same Inventory Manager. Either can be your first layout.

## Initialization Data

For a bag that grows with the character, set its slot count type to **Gameplay Attribute** and select **BackpackSlots**. Add the inventory attribute set to the owner's ability system and initialize it with a Data Table using the **AttributeMetaData** row type. This sample starts the character with 12 backpack slots, a weight limit of 100, and zero wealth. Adjust the values to suit your game. If you use Ninja G.A.S., follow [Give a Backpack Its Capacity](gas_guide_attributes.md#give-a-backpack-its-capacity) to assign the table to an ability bundle.

<code-block lang="json" src="inv_attributes.json" collapsible="true" collapsed-title="Starting inventory attributes"/>

# Inventory Items
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Inventory Items</b></p>
    <br/>
    <ul>
        <li>Items are created from Data Assets and turned into runtime instances.</li>
        <li>Item behavior is modular and defined using <b>fragments</b>.</li>
        <li>Fragments support stacking, equipping, consumables, events, and more.</li>
    </ul>
</tldr>

Inventory Items represent any object that can be stored, equipped, consumed, or manipulated through the Inventory System.

They are instantiated at runtime as `NinjaInventoryItem` objects and can represent things like weapons, potions, materials, 
or keys. Items can be defined by the following concepts:

- **Data-Driven**: Each item is created from a `UNinjaInventoryItemDataAsset`, defining its fragments and tags.
- **Fragment-Based**: Item behavior is defined by modular fragments, acting like components.
- **Instanced Runtime Object**: At runtime, items become `UNinjaInventoryItem` objects with their own state, memory, and container reference.

## Item Data Asset
Items are defined by a **Primary Data Asset**, and as such, must be added to the **Asset Manager** configuration as 
described in the [Asset Manager setup](inv_asset_manager.md#item-data-assets).

The Item Data Asset contains essential properties that define the identity and behavior of the item.

| Property            | Description                                                                                                                                                     |
|---------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `DisplayName`       | Internal name for the item (used for debugging/logging). UI name should come from a fragment.                                                                   |
| `GameplayTags`      | Tags that categorize the item for filtering, searching, and querying. Items should have at least one identifying tag, even if they simply represent a category. |
| `DynamicTags`       | A cache of all tags added by fragments. These are merged with the Gameplay Tags, and are used to further identify the item.                                     |
| `ItemInstanceClass` | Default class used for the runtime instance of this item. Usually left as the default.                                                                          |
| `Fragments`         | List of item fragments that define how the item behaves (e.g., stackable, equipable, consumable, etc.).                                                         |

You can create an Item Data Asset by right-clicking in the **Content Browser**, navigating to **Ninja Bear Studio > Ninja 
Inventory**, and selecting **Item Definition**.

<img src="inv_overview_item_data.png" alt="Item Data Asset" width="800" border-effect="line"/>

Items usually have **traits** which are useful when querying for certain items stored in the inventory. You can define
traits directly as **item tags**, or via **fragments**. Some fragments are already configured to add gameplay tags for 
the traits they represent.

## Item Fragments
Items are composed via **aggregation** of **fragments**—small pieces of logic and data that define item behavior.

Each fragment is tied to the Data Asset and **shared** across all instances of that item.

> **Fragments are Shared**  
> 
> A fragment is not directly related to a specific item instance. Instead, it is tied to the Item Data Asset and used by 
> all runtime instances created from it.
{style="note"}

Fragments control all core inventory functionality, such as:

- **Stacking and Quantity**: Manage how items stack and split.
- **Container Placement**: Determine valid containers, layouts, and positioning.
- **Consumables**: Allow items to apply effects and be consumed.
- **Equipment**: Define physical representation and equipment logic.

Fragments are automatically initialized when an item is created and can perform cleanup when the item is removed.

> **Fragment Creation**  
> 
> Simple fragments can be created in Blueprints. More advanced fragments (with memory or events) should be implemented in C++.
{style="note"}

Each fragment may also broadcast **events** via the **Inventory Manager**, which can be used to trigger logic such as UI 
updates, animations, or gameplay effects.

Refer to each fragment's documentation for specific behavior, memory structure, and event payloads.

## Item Instances
At runtime, an item becomes a `NinjaInventoryItem` instance. These are instanced objects that:

- Store runtime state (container, position, equipment state, etc.).
- Reference the original Data Asset and all resolved fragments.
- Include a unique **GUID** used for save/load and networking.
- Support **replicated memory** for multiplayer scenarios.

You can customize item behavior further by subclassing `NinjaInventoryItem` and assigning the new class in the Item Data 
Asset’s `ItemInstanceClass` property.

When added to an inventory, items have a **registration process**, that can inform where in the initialization an item
currently is. Possible values are:

- **Accepted**: The item was accepted and will be processed by the inventory.
- **Fragments Initialized**: Fragments will initialize and prepare their initial memories.
- **Fragments Activated**: Fragments have been initialized and executed any activation logic.
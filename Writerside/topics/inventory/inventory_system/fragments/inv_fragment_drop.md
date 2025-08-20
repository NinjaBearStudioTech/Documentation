# Drop Fragment
<primary-label ref="inventory"/>

The **Drop** fragment allows an item to be placed into the world as a Pickup Actor, using an **environment query** to 
determine a suitable drop location. 

When dropped, the item is removed from the inventory, and a corresponding **Pickup Actor** is spawned and initialized 
with the item data, including its relevant **Fragment** memories.

This is useful for world interactions, loot drops, or manual player drops.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Droppable` tag to an item, which introduces the **Droppable** trait.

## Properties
This fragment has the following properties.

| Property           | Description                                                                                   |
|--------------------|-----------------------------------------------------------------------------------------------|
| `PickupActorClass` | Actor class to spawn when the item is dropped. Must implement the `InventoryPickupInterface`. |
| `PlacementQuery`   | Environment Query used to determine where the Pickup Actor will be placed.                    |
| `QueryConfig`      | Parameters passed to the EQS query. Must match any named params in the query.                 | 
| `RunMode`          | EQS run mode, defining how results are prioritized (e.g., `RandomBest25Pct`).                 | 

The **Query Configuration** property dynamically matches any parameters exposed by the assigned **Placement Query** asset.
This is useful when multiple items share the same EQS asset but require different settings, such as grid size or spacing, 
to reflect their physical footprint in the world.

For example, here's an Environment Query that exposes **Grid Size** as a parameter:

<img src="inv_fragment_drop_eqs.png" alt="Item Placement EQS" width="800" border-effect="line"/>

If this asset is assigned to the Drop Fragment, the exposed parameters will appear automatically in the **Query Configuration** field:

<img src="inv_fragment_drop_eqs_parameters.png" alt="Drop EQS Parameters" width="800" border-effect="line"/>

## Operations
This fragment exposes the following operation.

| Function         | Description                                                                                                       |
|------------------|-------------------------------------------------------------------------------------------------------------------|
| `Drop`           | Spawns the Pickup Actor and removes the item from the inventory. Uses the Environment Query to define a location. |
| `DropAtLocation` | Spawns the Pickup Actor at a pre-defined location.                                                                |

## Memory
This fragment does not use its own memory but selectively includes other fragment memories when creating the Pickup Actor. 
For example, it excludes container placement memory since pickup placement will be re-evaluated when the item is picked up.

> **Selecting Fragment Memories**
>
> Memories stored for an item are transferred to the Pickup Actor, so things like "stack size" are carried.
>
> However, some memories are irrelevant, such as the container position, so it is filtered-out. You can fine-tune which
> memories should be added/removed by overriding `ShouldAddMemoryToPickup`.
{style="note"}

## Event Payload
This fragment emits the following event, using `InventoryItemDropPayload` as the payload structure.

| Event                                       | Description                                                                      |
|---------------------------------------------|----------------------------------------------------------------------------------|
| `Inventory.Event.Item.DroppedFromInventory` | Triggered when the item is successfully dropped and the Pickup Actor is spawned. |

## Pickup Actor
The Pickup Actor must implement the `InventoryPickupInterface`, which defines the following methods:

| Method                     | Description                                                      |
|----------------------------|------------------------------------------------------------------|
| `GetPickupItemDefinitions` | Returns the item definitions that this Pickup provides.          |
| `SetPickupDefinitions`     | Sets the item definitions for the Pickup, used when spawning it. |

A single Pickup Actor can provide **one or more items**. The Inventory System ensures that each pickup always results in 
**at least one item**.

The Inventory plugin includes a base implementation: `NinjaInventoryPickupActor`, which can be used directly or extended.
Valid actors can be added to the inventory via `AddItemsFromPickupActor`.
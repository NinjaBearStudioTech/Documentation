# Equipment
<primary-label ref="inventory"/>

The **Equipment** Fragment defines how an inventory item behaves when used as equipment. It integrates directly with the 
Equipment Manager, supports configurable equipment states, and defines **soft references** to assets for streamlined 
loading via the **Asset Manager**.

Each item with this fragment can have one or more **equipment states**, such as _equipped_ or _stored_. These states 
define how the item appears or behaves in the world.

> **Equipment Presence**
> 
> Not all **equipment states** defined in the tag set must have a **definition**. Only states with **in-world presence** 
> should be defined.
{style="note"}

Please make sure to check the additional documentation pages for [**Equipment**](inv_equipment_instances.md) and the 
[**Equipment Manager**](inv_equipment_management.md).

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Equipment` tag to an item, which introduces the **Equipment** trait.

## Properties
This fragment has the following properties.

| Name                    | Description                                                                        |
|-------------------------|------------------------------------------------------------------------------------|
| `DefaultEquipmentClass` | Class used for runtime equipment instances (default is `NinjaInventoryEquipment`). |
| `EquipmentStates`       | List of valid equipment states for this item, each with its own configuration.     |

## Operations
This fragment exposes the following operation.

| Function                             | Description                                                                                 |
|--------------------------------------|---------------------------------------------------------------------------------------------|
| `SetEquipmentState`                  | Updates the equipment state of the item (e.g., equip, store).                               |
| `GetEquipmentState`                  | Returns the current equipment state tag stored in memory.                                   |
| `GetCurrentEquipmentStateDefinition` | Returns the `FInventoryEquipmentState` definition for the current state.                    |
| `GetEquipmentStateDefinition`        | Returns the `FInventoryEquipmentState` for a given state tag.                               |
| `GetAssetSoftPaths`                  | Returns all referenced soft object paths (meshes, animations, etc.) from state definitions. |
| `GetEquipmentManager`                | Finds the `NinjaEquipmentManagerComponent` related to the item's owner.                     |
| `GetDefaultEquipmentClass`           | Returns the default class used to instantiate the equipment runtime object.                 |

## Memory
This fragment uses `FInventoryItemFragmentEquipmentMemory` to store the current **equipment state**.

This memory is created during the item initialization, **but only if the item is placed in a container with an Equipment layout**.
No memory is created if placed in a non-equipment container.

## Event Payload
This fragment emits the following event, using `InventoryItemEquipmentEventPayload` as the payload structure.

| Event                                        | Description                                     |
|----------------------------------------------|-------------------------------------------------|
| `Inventory.Event.Item.EquipmentStateChanged` | Triggered when the equipment state was changed. |
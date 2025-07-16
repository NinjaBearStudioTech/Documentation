# Weight
<primary-label ref="inventory"/>

The **Weight** fragment defines how heavy an item is and contributes to **encumbrance tracking** for the owning inventory. 
It integrates with **[stack size](inv_fragment_stack.md)** to calculate total weight and optionally blocks inventory actions 
when encumbrance limits are exceeded.

This fragment interacts with Gameplay Attributes using a lightweight approach based on **attribute aggregators**, avoiding 
the need for persistent Gameplay Effects.

> **Encumbrance Tracking**
>
> When items are added, removed, or modified, this fragment recalculates total encumbrance and updates the associated attribute. 
> This value can be used by movement systems, stamina drain logic, or other encumbrance-sensitive systems.
{style="note"}

## Fragment Tags
This fragment does not contribute any tags by default. 

## Properties
This fragment has the following properties.

| Property                     | Description                                                                                          |
|------------------------------|------------------------------------------------------------------------------------------------------|
| `WeightPerItem`              | The weight of a single item unit.                                                                    |
| `EncumbranceAttribute`       | The Gameplay Attribute representing the current encumbrance.                                         |
| `WeightLimitAttribute`       | The Gameplay Attribute representing the maximum encumbrance allowed.                                 |
| `ExemptContainerFilterQuery` | A query used to exclude specific containers (e.g., vendor or loot) from contributing to encumbrance. |

## Operations
This fragment exposes the following operations.

| Function                      | Description                                                                   |
|-------------------------------|-------------------------------------------------------------------------------|
| `GetItemWeight`               | Calculates the total weight of the item, considering the stack size.          |
| `CalculateEncumbrance`        | Sums the weight of all valid items in the inventory and returns the total.    |
| `RefreshEncumbranceAttribute` | Updates the current encumbrance attribute on the owning actor.                |

## Memory
This fragment does not define a memory struct but relies on the **[Stack fragment](inv_fragment_stack.md)** to calculate 
the total item weight.

Encumbrance is recomputed dynamically by summing valid item weights across all containers, filtered by `ExemptContainerFilterQuery`.

> **Encumbrance Precision**
>
> This fragment avoids the need to track individual contributions via GE handles or custom memory structs. Instead, it 
> ensures consistent and accurate encumbrance using recalculation on-demand or via fragment events.
{style="note"}

## Event Payload
This fragment does not define its own event or payload. 
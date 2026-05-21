# Dynamic Attributes Fragment
<primary-label ref="inventory"/>

The **Dynamic Attributes** fragment allows you to define custom attributes for an item.

Each attribute can be assigned a **fixed value** or a **random range** that is resolved when the item is created.

> **Item Attributes and Gameplay Attributes**
> 
> These are not Gameplay Attributes (GAS). Instead, they are custom item-level attributes that can also be exported to 
> Gameplay Effects as Set By Caller magnitudes if desired.

## Application
This fragment implements `IInventoryItemMagnitudeInterface`, which is used by an Item Instance to set magnitudes to any 
gameplay effect applied either from the [**Gameplay Effect Fragment**](inv_fragment_gameplay_effect.md) or by an active 
[**Equipment State**](inv_equipment_instances.md).

## Fragment Tags
This fragment does not introduce any specific gameplay tags by default.

## Properties
This can define multiple attributes, each with the following properties.

| Property               | Description                                                                                |
|------------------------|--------------------------------------------------------------------------------------------|
| `AttributeDataTag`     | Unique tag identifying the attribute.                                                      |
| `Name`                 | A localized name that can be used internally or with the user interface.                   |
| `Description`          | A localized description that can be used internally or with the user interface.            |
| `ValueMode`            | Determines how the value is determined for this attribute.                                 |
| `FixedValue`           | Value assigned when `ValueMode` is set to **Fixed**.                                       |
| `MinValue`             | Minimum possible value when `ValueMode` is set to **Range**.                               |
| `MaxValue`             | Maximum possible value when `ValueMode` is set to **Range**.                               |
| `AttributeCurve`       | A level/value curve used, when `ValueMode` is set to **Table**.                            |
| `bExportAsSetByCaller` | If true, this attribute will be exported to Gameplay Effects as a Set By Caller magnitude. |

## Value Modes
This fragment supports the following value modes:

| Value Mode | Description                                                                         |
|------------|-------------------------------------------------------------------------------------|
| `Fixed`    | The dynamic attribute starts with a fixed, pre-defined, value.                      |
| `Range`    | The dynamic attribute starts with a random value in a given range (Min/Max Values). |
| `Table`    | The dynamic attribute starts and updates its value from a level-based table.        |

> **Level-Based Table**
> 
> This is a **Curve Table** asset, where each line represents an attribute. Indexes are defined by the **Item Level**,
> provided by the [**Level Fragment**](inv_fragment_level.md).
{style="note"}

## Memory
The fragment supports default memories via the `FInventoryItemFragmentAttributeMemory` struct.

From the item instance’s perspective, dynamic attributes are stored in a **dedicated memory structure** separate from 
other fragment memories, allowing for optimized replication and runtime access.

## Operations
This fragment exposes the following operations:

| Function                            | Description                                                                   |
|-------------------------------------|-------------------------------------------------------------------------------|
| `HasAttribute`                      | Returns `true` if the item has an attribute matching the provided tag.        |
| `GetAttribute`                      | Retrieves the attribute value for the provided item.                          |
| `GetAllAttributes`                  | Retrieves all attributes and values for the given item.                       |
| `GetAllAttributesFromDefaultMemory` | Retrieves all default attributes and values from the item’s default memory.   |
| `AddToDefaultItem`                  | Applies all attributes (resolving random ranges if needed) to a default item. |
| `SetAttribute`                      | Sets the attribute value for the provided item.                               |
| `RemoveAttribute`                   | Removes the attribute from the provided item.                                 |

## Events
The fragment triggers the following events, all using the `FInventoryItemAttributesPayload` struct:

- `Inventory.Event.Item.DynamicAttribute`:
  - `.Created`: A new attribute is added to an item.
  - `.Updated`: An attribute value changes.
  - `.Removed`: When an attribute is removed from an item.

## Gameplay Effect Integration
When `bExportAsSetByCaller` is enabled in an attribute, its value can be injected into a Gameplay Effect Spec as Set By 
Caller magnitudes, allowing them to directly influence ability and effect calculations.

Eligible attributes are exposed via `IInventoryItemMagnitudeInterface`.
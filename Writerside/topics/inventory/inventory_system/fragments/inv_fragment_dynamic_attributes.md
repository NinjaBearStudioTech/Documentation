# Dynamic Attributes Fragment
<primary-label ref="inventory"/>

The **Dynamic Attributes** fragment allows you to define custom attributes for an item.

Each attribute can be assigned a **fixed value** or a **random range** that is resolved when the item is created.

> **Item Attributes and Gameplay Attributes**
> 
> These are not Gameplay Attributes (GAS). Instead, they are custom item-level attributes that can also be exported to 
> Gameplay Effects as Set By Caller magnitudes if desired.

## Fragment Tags
This fragment does not introduce any specific gameplay tags by default.

## Properties
This can define multiple attributes, each with the following properties.

| Property               | Description                                                                                |
|------------------------|--------------------------------------------------------------------------------------------|
| `AttributeDataTag`     | Unique tag identifying the attribute.                                                      |
| `Name`                 | A localized name that can be used internally or with the user interface.                   |
| `Description`          | A localized description that can be used internally or with the user interface.            |
| `ValueMode`            | Determines if the attribute’s value is fixed or randomly resolved from a range.            |
| `FixedValue`           | Value assigned when `ValueMode` is set to **Fixed**.                                       |
| `MinValue`             | Minimum possible value when `ValueMode` is set to **Range**.                               |
| `MaxValue`             | Maximum possible value when `ValueMode` is set to **Range**.                               |
| `bExportAsSetByCaller` | If true, this attribute will be exported to Gameplay Effects as a Set By Caller magnitude. |

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
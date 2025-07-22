# Quality Fragment
<primary-label ref="inventory"/>

The **Quality** fragment defines the quality tier of an item, such as _Common_, _Rare_, or _Legendary_. It provides a 
quality tag, localized text, and a representative color.

This fragment relies on a **centralized Data Table**, configured in `Project Settings > Ninja Inventory`, under the 
"Quality Mapping Table" section. This table must use the `InventoryItemQualityMappingTableRow` structure and define all 
supported quality tags and their attributes.

## Fragment Tags
This fragment adds the corresponding `Inventory.Item.Quality.*` tag to the item, based on the fragment configuration.

## Properties
This fragment has the following property.

| Property       | Description                                                                                                                       |
|----------------|-----------------------------------------------------------------------------------------------------------------------------------|
| `QualityTag`   | Gameplay Tag that represents the item's quality (e.g., `Inventory.Item.Quality.Common`). Must exist in the Quality Mapping Table. |
| `QualityText`  | Localized name for the quality (e.g., "Epic"). Auto-filled from the table.                                                        |
| `QualityColor` | Visual color representing the quality. Auto-filled from the table.                                                                |

## Operations
This fragment exposes the following operations.

| Function          | Description                                        |
|-------------------|----------------------------------------------------|
| `GetQualityTag`   | Returns the Gameplay Tag representing the quality. |
| `GetQualityText`  | Returns the localized display name.                |
| `GetQualityColor` | Returns the color associated with the quality.     |

## Memory
This fragment does not use or contribute any memory state.

## Event Payload
The Quality fragment does not broadcast a dedicated event.
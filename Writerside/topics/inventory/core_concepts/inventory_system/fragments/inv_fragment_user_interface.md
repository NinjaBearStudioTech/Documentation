# User Interface Fragment
<primary-label ref="inventory"/>

The **User Interface** fragment defines how an item appears in UI elements such as tooltips, inventory slots, or detail 
panels. It includes localized text for the item’s name, category, and description, as well as an icon.

This fragment is optional, but recommended for all items that will be visible on **Widgets**.

## Fragment Tags
This fragment does not add any traits to the item.

## Properties
This fragment has the following properties.

| Property      | Description                                    |
|---------------|------------------------------------------------|
| `DisplayName` | Localized text used as the item's main name.   |
| `Category`    | Localized text used to describe the item type. |
| `Description` | Localized text used to describe the item.      |
| `Icon`        | Texture representing the item in the UI.       |

## Operations
This fragment exposes the following operations.

| Function         | Description                                         |
|------------------|-----------------------------------------------------|
| `GetDisplayName` | Returns the localized display name of the item.     |
| `GetCategory`    | Returns the localized category or type of the item. |
| `GetDescription` | Returns the localized description of the item.      |
| `GetIcon`        | Returns the texture used as the item’s UI icon.     |

## Memory
This fragment does not store any data in memory.

## Event Payload
This fragment does not define its own event or payload structure.
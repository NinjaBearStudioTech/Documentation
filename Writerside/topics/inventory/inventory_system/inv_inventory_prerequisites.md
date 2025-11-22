# Item Prerequisites
<primary-label ref="inventory"/>

**Item Prerequisites** are small objects that can be instantiated in certain parts of the system to determine if the 
item operation being executed can happen, such as **adding the item to the inventory** or **equipping an item**.

## Prerequisite Object

Prerequisites are defined by the `UNinjaInventoryItemPrerequisite` class, which can be extended to crate new prerequisites
in either Blueprints or C++.

Prerequisites may provide a **user interface description** that can be used to expose accurate messages, when these
pieces of logic are exposed to widgets.

## Default Prerequisites

The system provides the following prerequisites.

| Prerequisite     | Description                                                                                                                                                                                                           |
|------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `AttributeValue` | Checks that the current value for a pre-defined attribute is **greater or equal** than the reference value. Its description includes wildcards for the **attribute name**, **reference value** and **current value**. |
| `ItemQuery`      | Executes an item query to find items from the inventory. Can be inverted to test that no items were found. Does not provide a default description for user interfaces.                                                |

## Usage Scenarios

Currently, you will find these prerequisites being used in the following situations:

- **Adding Items to Inventory**: If the [**Prerequisites Fragment**](inv_fragment_prerequisites.md) is present in the item, it will be used to evaluate if the item can be added to the inventory.
- **Equipping an Item**: If the item has an [**Equipment Representation**](inv_fragment_equipment.md), it may include prerequisites that will determine if the item can be equipped or not. 


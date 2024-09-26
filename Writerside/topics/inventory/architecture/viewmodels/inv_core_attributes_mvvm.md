# Inventory Attributes
<primary-label ref="inventory"/>

Exposes **Gameplay Attributes** assigned to the **Inventory Owner**. 

This viewmodel is meant to be used at the **Inventory UI** level. It will bind to the owner's **Ability System Component**
and the appropriate attributes when the Inventory Manager **completes its initialization**.

| Field                   | Description                                       | Update Condition                                  |
|-------------------------|---------------------------------------------------|---------------------------------------------------|
| Wealth                  | Amount of funds available to the owner.           | Gameplay Attribute value changes.                 |
| Encumbrance             | Total weight of items in the inventory.           | Items are added or removed from the inventory.    |
| Equipment Level         | Absolute level from all items in equipment slots. | Items are added or removed from equipment slots.  |
| Average Equipment Level | Average equipment level.                          | Items are added or removed from equipment slots.  |
| Weight Limit            | Maximum weight supported by the inventory.        | Gameplay Attribute value changes.                 |


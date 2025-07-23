# Attributes ViewModel
<primary-label ref="inventory"/>

The **Attributes ViewModel** exposes inventory-related attributes from the owner's `Ability System Component`.

It enables UI widgets to respond to updates in **weight**, **equipment level**, and **currency** without manual polling 
or binding logic.

It is commonly used in HUDs, equipment panels, or stats widgets to visualize key gameplay values.

## Configuration

This ViewModel is automatically resolved by the `Inventory Resolver` and requires the owning actor to have a valid 
`Ability System Component`.

## Notifies

This ViewModel currently supports the following inventory-related attributes:

| Field            | Description                                                     |
|------------------|-----------------------------------------------------------------|
| `Wealth`         | Tracks the player's current amount of **currency**.             |
| `EquipmentLevel` | Reflects the average level of all currently **equipped items**. |
| `Encumbrance`    | Shows the current **carried weight**.                           |
| `WeightLimit`    | Shows the **maximum carry weight** the player can support.      |


# Level
<primary-label ref="inventory"/>

The **Level** Fragment defines the power level for an item, which can also be used to determine the Gameplay Effect
level for many effects applied from the item.

## Fragment Tags
This fragment adds the `Inventory.Item.Trait.Upgradeable` tag to an item, which introduces the **Upgradeable** trait.
This trait is conditional to the value set for `CanUpgrade`.

## Properties
This fragment has the following properties.

| Property     | Description                                   |
|--------------|-----------------------------------------------|
| `CanUpgrade` | Indicates if the item can be upgraded or not. |
| `Level`      | The level in which the item starts.           |
| `MaxLevel`   | The maximum level the item can reach.         |

## Operations
This fragment exposes the following operations.

| Function                    | Description                                                  |
|-----------------------------|--------------------------------------------------------------|
| `CanUpgrade`                | Informs if the item can be upgraded or not.                  |
| `IsMaximumLevel`            | Informs if the item is at the maximum level.                 |
| `GetLevel`                  | Gets the current level assigned to the item.                 |
| `GetLevelFromDefaultMemory` | Gets the current level assigned to the default memory data.  |
| `GetMaximumLevel`           | Gets the maximum level allowed to items using this fragment. |
| `SetLevel`                  | Sets the level of the specified inventory item.              |
| `Upgrade`                   | If possible, adds an extra level to the item.                |

## Memory
This fragment uses `InventoryItemFragmentLevelMemory`, to store the current **level**.

## Event Payload
This fragment emits the following events, using `InventoryItemLevelPayload` as the payload structure.

| Event                               | Description                            |
|-------------------------------------|----------------------------------------|
| `Inventory.Event.Item.LevelChanged` | Triggered when the item level changes. |

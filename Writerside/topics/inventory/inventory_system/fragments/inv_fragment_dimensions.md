# Dimensions
<primary-label ref="inventory"/>

The **Dimensions** Fragment defines the 2D spatial footprint for a container that uses a spatial layout.

It defines the base **width** and **height** and if the item can be **rotated**. On top of the default rotation flag,
an item cannot be rotated if its width equals its height, since rotation would be irrelevant.

## Fragment Tags
This fragment does not contribute any tags

## Properties
This fragment has the following properties.

| Property    | Description                                                                 |
|-------------|-----------------------------------------------------------------------------|
| `Width`     | The width for the item, when shown in a 2D representation.                  |
| `Height`    | The height for the item, when shown in a 2D representation.                 |
| `CanRotate` | Determines if the item can be rotated, when width is different than height. |

## Operations
This fragment exposes the following operations.

| Function            | Description                                                                                                               |
|---------------------|---------------------------------------------------------------------------------------------------------------------------|
| `GetBaseDimensions` | Provides the base fragment dimensions, disregarding rotation state.                                                       |
| `GetDimensions`     | Returns the item rotation, considering its rotation state. If rotation is not allowed, this is always the base dimension. |
| `CanRotate`         | Informs if the item can be rotated. It considers the `CanRotate` flag and also the item's dimensions.                     |
| `IsRotated`         | Informs if the item is currently rotated.                                                                                 |
| `SetRotated`        | Sets if the item is currently rotated or not.                                                                             |

## Memory
This fragment uses `FInventoryItemFragmentDimensionsMemory`, to store the current **durability**.

## Event Payload
This fragment emits the following events, using `FInventoryItemDimensionsPayload` as the payload structure.

| Event                                  | Description                               |
|----------------------------------------|-------------------------------------------|
| `Inventory.Event.Item.RotationChanged` | Triggered when the item rotation changes. |

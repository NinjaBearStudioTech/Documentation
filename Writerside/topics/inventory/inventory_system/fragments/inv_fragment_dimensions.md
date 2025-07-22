# Dimensions Fragment
<primary-label ref="inventory"/>

The **Dimensions** Fragment defines the **2D spatial footprint** for items placed within containers that use a [](inv_layout_spatial.md).

It specifies the base **width** and **height**, and whether the item can be **rotated**.  
Rotation is only considered valid when the item's width and height are not equal (i.e., non-square shapes).

## Fragment Tags
This fragment does not contribute any gameplay tags.

## Properties

| Property    | Description                                                                      |
|-------------|----------------------------------------------------------------------------------|
| `Width`     | The base width of the item in grid cells.                                        |
| `Height`    | The base height of the item in grid cells.                                       |
| `CanRotate` | Allows the item to be rotated. Rotation is only relevant when `Width != Height`. |

## Operations

| Function            | Description                                                                                                               |
|---------------------|---------------------------------------------------------------------------------------------------------------------------|
| `GetBaseDimensions` | Returns the original dimensions defined by the fragment, ignoring any current rotation.                                   |
| `GetDimensions`     | Returns the current item dimensions, accounting for its rotation state (if applicable).                                   |
| `CanRotate`         | Checks whether the item supports rotation, based on its shape and the `CanRotate` flag.                                   |
| `IsRotated`         | Returns whether the item is currently rotated.                                                                            |
| `SetRotated`        | Sets the item's rotation state. Requires authority and valid memory.                                                      |

## Memory
This fragment uses the `FInventoryItemFragmentDimensionsMemory` structure to track the **rotation state** of the item at runtime.

## Occupancy Masks
When enabled, this fragment can also define an **Occupancy Mask**, allowing for non-rectangular item shapes (e.g. crosses, circles, Tetris-style pieces).

- The mask is a `TArray<bool>` representing which cells in the item's dimensions are considered occupied.
- When rotated, the fragment automatically interprets the mask in rotated space.
- If no mask is defined, the item defaults to occupying all cells in its width * height rectangle.

> A future version will include UI tools to visually edit these masks in-editor.

## Event Payloads
This fragment emits events using the `FInventoryItemDimensionsPayload` structure.

| Event                                  | Description                                        |
|----------------------------------------|----------------------------------------------------|
| `Inventory.Event.Item.RotationChanged` | Emitted when the item's rotation state changes.    |

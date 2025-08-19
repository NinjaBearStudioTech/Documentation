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

| Function                         | Description                                                                                              |
|----------------------------------|----------------------------------------------------------------------------------------------------------|
| `GetBaseDimensions`              | Returns the original dimensions defined by the fragment, ignoring any current rotation.                  |
| `GetDimensions`                  | Returns the current item dimensions, accounting for its rotation state (if applicable).                  |
| `GetDimensionsFromDefaultMemory` | Returns the dimensions for a default item, accounting for its rotation state (if a memory is available). |
| `CanRotate`                      | Checks whether the item supports rotation, based on its shape and the `CanRotate` flag.                  |
| `CanRotateItemInPlace`           | Checks if the fragment supports rotation and if the item can be rotated in the occupied space.           |
| `IsRotated`                      | Returns whether the item is currently rotated.                                                           |
| `IsRotatedFromDefaultMemory`     | Returns whether the default item is currently rotated, based on a memory.                                |
| `SetRotated`                     | Sets the item's rotation state. Requires authority and valid memory.                                     |

## Memory
This fragment uses the `FInventoryItemFragmentDimensionsMemory` structure to track the **rotation state** of the item at runtime.

## Occupancy Masks
Occupancy Masks let items use non-rectangular footprints (crosses, L-pieces, circles, Tetris-like shapes) when placed 
inside [grid-based containers](inv_layout_spatial.md). The layout/placement logic treats only the true cells of the mask 
as occupied, enabling richer packing and equipment silhouettes.

- A mask is a **grid** (Width x Height) stored as a `TArray<bool>` (row-major).
- Setting a cell to `true` means the cell is occupied by the item; `false` means cell is empty and ignored for collisions.
- If no mask is defined, the item occupies its **full rectangle** (Width x Height, all `true`).
- Masks respect **rotation**: the framework evaluates collisions using the mask transformed into the item’s current orientation.
- A mask requires at least one occupied cell. The asset validation will fail for empty masks.  

<img src="inv_fragment_dimensions_occupancy_mask.png" alt="Occupancy Mask" width="800" border-effect="line"/>

## Event Payloads
This fragment emits events using the `FInventoryItemDimensionsPayload` structure.

| Event                                  | Description                                        |
|----------------------------------------|----------------------------------------------------|
| `Inventory.Event.Item.RotationChanged` | Emitted when the item's rotation state changes.    |

# Spatial Layout
<primary-label ref="inventory"/>
<secondary-label ref="experimental"/>

The **Spatial Layout** is a specialized container layout that supports **2D spatial positioning** of items, enabling 
grid-based organization.

> **Item Dimensions**
>
> This layout is designed to work alongside the [**Dimensions Fragment**](inv_fragment_dimensions.md), which defines an 
> item's 2D footprint within the grid.
{style="note"}

It is ideal for containers that can hold **items of varying sizes** (e.g., `1x1`, `2x2`, `2x3`, `2x4`, etc.), and it 
also supports **item rotation**, when enabled.

## Layout Properties

The following properties control the grid layout:

| Property        | Description                                                                                                                                    |
|-----------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| `Width`         | The **number of columns** in the grid. Used for placement logic and UI layout.                                                                 |
| `Height`        | The **number of rows** in the grid. Only used if `SlotCountType` is set to **Property**.                                                       |
| `SlotCountType` | Defines how the total number of usable slots is determined. Options include **Property** (fixed values) or **Gameplay Attribute** (dynamic).   |
| `SlotAttribute` | A reference to a `GameplayAttribute` used to determine slot count at runtime. Used only when `SlotCountType` is set to **Gameplay Attribute**. |

> **Height and Slot Attributes**
>
> When using a **Gameplay Attribute** to define the slot count, the `Height` property is ignored.  
> The grid will automatically calculate the number of rows using:  
> 
> `height = attribute_value / width`.
{style="note"}

## Position Type

This layout uses the `Grid` position type, where each item occupies a **2D coordinate** on the container (starting at `0,0`).  
The layout behaves like a **matrix**, with collision and fit checks performed across rows and columns.

## Slot Count Types

The layout supports two modes of determining total slots:

- **Fixed Property**: The `Width` and `Height` are set directly on the asset and remain constant.
- **Gameplay Attribute**: A runtime attribute defines the total number of slots. The layout uses `Width` and derives `Height` dynamically.

This enables both static containers (e.g. a small chest) and dynamic ones (e.g. a player’s bag scaling with level or strength).

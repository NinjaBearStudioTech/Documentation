# Spatial Layout
<primary-label ref="inventory"/>

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
| `GridWidth`     | The **number of columns** in the grid. Used for placement logic and UI layout.                                                                 |
| `GridHeight`    | The **number of rows** in the grid. Only used if `SlotCountType` is set to **Property**.                                                       |
| `FitAlgorithm`  | Algorithm used to test fit and item collisions.                                                                                                |
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

To better illustrate how items interact with the spatial grid, the following example shows two scenarios, in a `10x4`grid.

**Example 1**: An L-shaped item and a 1x1 item are placed on the grid, on positions `0,0` and `1,0` respectively. The 
L-shaped item cannot rotate because the 1x1 item blocks one of its required cells.

<img src="inv_layout_spatial.png" alt="Grid with L-shaped and 1x1 item, rotation blocked" width="600"/>

**Example 2**: After moving the 1x1 item to a different position, `2,0`, the L-shaped item can rotate freely. This 
demonstrates how the fit algorithm checks collisions against existing occupants and container bounds.

<img src="inv_layout_spatial_rotated.png" alt="Grid after moving 1x1 item, rotation allowed" width="600"/>

> **Item Dimensions**
> 
> Complex item shapes (such as L-forms) are defined by the [**Dimensions Fragment**](inv_fragment_dimensions.md).
> This fragment defines the item's **occupancy mask** and whether **rotation** is allowed.
{style="note"}

## Slot Count Types

The layout supports two modes of determining total slots:

- **Fixed Property**: The `Width` and `Height` are set directly on the asset and remain constant.
- **Gameplay Attribute**: A runtime attribute defines the total number of slots. The layout uses `Width` and derives `Height` dynamically.

This enables both static containers (e.g. a small chest) and dynamic ones (e.g. a player’s bag scaling with level or strength).

## Fit Algorithm

The spatial layout's fit algorithm decides whether an item can be placed at a candidate position given its size, rotation, 
and occupancy mask, while respecting container bounds and existing items. It's called by CanAcceptItemAtPosition and by 
search routines that try alternative slots when the first choice fails.

### PerCell
<secondary-label ref="beta"/>
This algorithm iterates each occupied cell of the item's mask, including rotation support, and tests that cell against 
the container grid.

Best for small–medium items or containers where shapes vary a lot (Tetris-like pieces, irregular masks). It’s simple, 
exact, and easy to reason about. Great default when you value clarity over raw throughput.

### BitSetRows
<secondary-label ref="experimental"/>
Treats each container row as a bitset and checks the item's occupied cells with fast bitwise operations (shift-and-AND) 
per row.

Ideal for large grids or heavy search (auto-fit, mass packing). Row-level bit operations drastically reduce inner-loop work, 
making it much faster when scanning many positions or handling wide items.

### Custom
Lets you plug in your own fit logic for special layouts or heuristics. Extend the layout and override the virtual 
`TestWithCustomAlgorithm` hook to implement your algorithm. 

> For performance reasons, this is a C++ only extension point; it's called in tight loops, so keep allocations to a 
> minimum and prefer cache-friendly data structures.
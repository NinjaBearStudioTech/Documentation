# Spatial Layout
<primary-label ref="inventory"/>
<secondary-label ref="experimental"/>

The **Spatial Layout** is a specialized container layout that supports **2D spatial representations** of items.

> **Item Dimensions**
>
> This layout is designed to work alongside the [**Dimensions Fragment**](inv_fragment_dimensions.md), which is used to 
> define and provide an item's 2D footprint, for a layout like this. 
{style="note"}

It is ideal for **grids** that can store items of different sizes (e.g., `1x1`, `2x2`, `2x3`, `2x4`, etc.), including
the possibility of **rotating** items.

## Layout Properties
This layout implementation defines the following properties:

| Property        | Description                                                                                                                                                    |
|-----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `Width`         | The **width** of the grid, used for position calculation and potentially, user interface.                                                                      |
| `Height`        | The **height** of the grid, used for position calculation and potentially, user interface.                                                                     |
| `SlotCountType` | Determines how the total slot count is calculated, which limits the amount of items that can be added. Options include **Property** or **Gameplay Attribute**. |
| `SlotAttribute` | Attribute reference used to determine slot count dynamically. Used only if `SlotCountType` is set to **GameplayAttribute**.                                    |

> **Height and Attribute**
> 
> If the **Slot Count** is configured as an **Attribute Set**, then the height is **ignored**. 
> 
> Instead, the **width** is used with the attribute value, and the height just becomes the result of the division `attribute / width`.
{style="note"}

## Position Type
This layout uses the `Grid` **position type**, where each item's position is represented by a **2D position**
(starting at 0,0). The layout behaves like a **matrix**, as expected for a grid-based container.

## Slot Count Types
The number of available slots can be determined in two different ways:

- **Fixed Property**: Constant value defined directly in the asset, for both width and height.
- **Gameplay Attribute**: A dynamic value pulled from an owning `AttributeSet`. In this case, height is **discarded**.

This allows for both static and player-scaled inventories.

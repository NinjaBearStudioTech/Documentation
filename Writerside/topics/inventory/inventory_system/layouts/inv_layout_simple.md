# Simple Layout
<primary-label ref="inventory"/>

The **Simple Layout** is a minimal and flexible layout designed for straightforward container types such as backpacks,
stash tabs, or vendor inventories. Each item occupies a **single slot**, and the layout does not support spatial
positioning (like grids or item dimensions).

It is ideal for **list-style containers**, where the only constraint is how many items the container can hold at once.
This layout focuses on:

- Defining a maximum **slot count**.
- Treating each item as a **single-slot entry**.
- Allowing compatibility with gameplay systems through **attribute-driven slot scaling**.

## Layout Properties
This layout implementation defines the following properties:

| Property        | Description                                                                                                                                                    |
|-----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `SlotCountType` | Determines how the total slot count is calculated, which limits the amount of items that can be added. Options include **Property** or **Gameplay Attribute**. |
| `Slots`         | Number of slots available, if `SlotCountType` is set to **Property**.                                                                                          |
| `SlotAttribute` | Attribute reference used to determine slot count dynamically. Used only if `SlotCountType` is set to **GameplayAttribute**.                                    |

## Position Type
This layout uses the `Index` **position type**, where each item's position is represented by a **simple integer index**
(starting at 0). The layout behaves like a **linear array**, ideal for list-based storage.

## Slot Count Types
The number of available slots can be determined in two different ways:

- **Fixed Property**: A constant value defined directly in the asset.
- **Gameplay Attribute**: A dynamic value pulled from an owning `AttributeSet`.

This allows for both static and player-scaled inventories.

## Example Use Cases
Use this layout when you need a lightweight, scalable container without the overhead of spatial layouts like grids.
Recommended for:

- Player backpacks with fixed or upgradeable size.
- Vendor inventories with a capped number of items.
- Loot chests or reward bags.

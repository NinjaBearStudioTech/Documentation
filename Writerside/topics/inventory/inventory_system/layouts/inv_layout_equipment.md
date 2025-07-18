# Equipment Layout
<primary-label ref="inventory"/>

The **Equipment Layout** is a specialized container layout for managing **gear items**—such as weapons, armor, or tools 
that require an equipment state and a defined attachment point.

It integrates directly with the **Ninja Equipment System** and allows items to be stored in specific **equipment slots**, 
with state transitions managed through gameplay tags.

> **Equipment Integration**
>
> This layout is designed to work alongside the [**Equipment Fragment**](inv_fragment_equipment.md) and requires an 
> [**Equipment Manager**](inv_equipment_management.md) component on the owning character.
{style="note"}

This layout provides:

- Integration with the **equipment system**, including states like *Equipped*, *Stored*, or *Sheathed*.
- A way to organize items by their **equipment state**, instead of physical position.
- Automation of **state transitions**, using the layout logic and item fragment behavior.

## Prerequisites
To use this layout correctly, the following must be present:

- An [**Equipment Manager**](inv_equipment_management.md) on the owning actor or pawn.
- An [**Equipment Fragment**](inv_fragment_equipment.md) on each item placed in this container.

## Layout Properties
This layout implementation defines the following properties:

| Property                  | Description                                                                                                                                                       |
|---------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `DefaultStateTag`         | Equipment state tag applied to items added to this container. Determines how the item is treated on initial add (e.g., `equipped`, `stored`).                     |
| `DefaultEquipSocketName`  | Default socket name for items in the **equipped** state. Used to attach actors to the skeletal mesh (e.g., `"RightHandSocket"`). Can be overridden per equipment. |
| `DefaultStoredSocketName` | Default socket name for items in the **stored** state. Common for sheathed or holstered positions. Can be overridden per equipment.                               |
| `LinkedContainerData`     | Optional reference to a **linked container**. Used when an item occupies more than one container. Example: a two-handed weapon using both weapon slots.           |
| `LinkedItemQuery`         | Gameplay tag query that determines if an item should also occupy the **linked container**. Evaluated only when `LinkedContainerData` is set.                      |

## Position Type
This layout uses the `Single` **position type**, since only one item can be added to an equipment slot.

## Example Use Cases
This layout is ideal for:

- Character equipment panels (e.g., Head, Chest, Weapon, Accessory slots).
- Quick-access bars for consumables or tools.
- Any system where items represent gear and should transition through equipped states.

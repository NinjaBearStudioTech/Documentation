# Base Widgets
<primary-label ref="inventory"/>

## Item Widget

The first part of the **widget hierarchy** is the **Item Widget**.

- Root widget that owns the Item View Model (data entry-point).
- Child view models (e.g., stack, rarity) bind to the entry-point.
- It's self-contained, when given an Item View Model, all Fragment View Models are automatically updated.

## Container Widget

Then the next part is the **Container Widget** (like grids, panels, loot lists).

- Hosts multiple Item Widgets.
- Uses a **Container View Model**, which outputs multiple **Item View Models**.
- If using a **ViewModel Extension**, bindings from the container to entries are automatic.

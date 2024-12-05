# Inventory Layout
<primary-label ref="inventory"/>

Provides information about the inventory's **Layout**.

Useful to expose the **Display Name** set in the Layout's **Data Asset**, which is something that you might need, if you
have layouts representing **actual items**, for example:

- A layout for the **Player Inventory**, with a title like **Inventory** or **Backpack**.
- A layout for **Treasure Chests**, with a title like **Treasure**.

Since the Display Name is a **localized value**, it might be useful to used it as the inventory window's title.

| Field                   | Description                              | Update Condition |
|-------------------------|------------------------------------------|------------------|
| DisplayName             | Localized name for the Inventory Layout. | None.            |


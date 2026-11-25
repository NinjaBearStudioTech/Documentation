# Items, Fragments, and Eligibility
<primary-label ref="inventory"/>

An **Item Definition** describes every item of one kind. A **fragment** gives that item a particular feature. Two bandage stacks can share a definition and icon while one contains five bandages and the other contains one. Each stack keeps its own count in **fragment memory**.

## Give an Item the Features It Needs

| Player-facing example | Fragments to add | What to configure |
| --- | --- | --- |
| [A stack of bandages](inv_guide_inventory_items.md) | Container Placement, Stack and Quantity, User Interface | Where it can go, how many fit in one stack, how many the player can own, and what the player sees. |
| [A tool in a spatial backpack](inv_guide_spatial_grid.md) | Dimensions, alongside placement and UI | Width, height, any gaps in its shape, and whether the player can rotate it. |
| [A usable or droppable item](inv_gameplay_abilities.md) | Consumable or Drop | The effect and cost of using one charge, or the pickup actor that appears when dropped. |
| [A piece of gear](inv_guide_equipment.md) | Equipment, alongside placement | Its appearance when equipped or stored and the conditions for entering a state. |

A **Weight Fragment** can make a stack contribute to the owner's encumbrance. Initialize the owner's inventory attributes before using weight in an eligibility rule. A stack limit of five and a maximum quantity of ten allow two full stacks if there is space for both.

For an item that holds other items, add a **Nested Container Fragment** and use `GetNestedContainer` to open its contents. For changing stats such as healing power, a **Dynamic Attributes Fragment** can supply tagged values to a Gameplay Effect through Set By Caller magnitudes. A custom fragment can provide these values through `IInventoryItemMagnitudeInterface.GetMagnitudesForSpec`.

## Explain Why an Action Is Unavailable

Use a **prerequisite** where a feature offers one. For example, on a gear item's Equipped state, add an attribute-value prerequisite for the required character stat. Supply a description such as “Requires 10 Strength” so the equipment screen can explain the requirement. The player can carry the item before they qualify to wield it.

To check an item before it enters the inventory, add a **Prerequisites Fragment** to the definition. An item-query prerequisite can look for a required item in the owner's inventory.

For a game-specific rule, subclass `NinjaInventoryItemPrerequisite`, implement `EvaluatePreRequisite` for the decision, and implement `GetDescription` for the player's message. Mark it relevant for the user interface if it should be displayed.

## Add Your Own Item Behavior

Subclass `NinjaInventoryItemFragment` for a feature such as a rechargeable scanner. Put the shared maximum on the fragment and the current charge in the individual item's memory. Use `InitializeItem` for a new scanner and `InitializeItemWithDefaultMemory` when the incoming item already contains a charge value. This lets a dropped or restored scanner keep its remaining charge. Add the events the fragment needs to `WatchedEventTags` and handle them in `HandleItemEvent`, and expose the charge to the [item widget](inv_ui_mvvm.md) where the player uses it.

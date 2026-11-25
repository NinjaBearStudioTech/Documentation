# Shared Inventories and Loot
<primary-label ref="inventory"/>

A town chest can hold one set of items for everyone. A personal locker can look like the same chest while showing each player a container in their own inventory. Decide who owns the contents before building the screen.

## Open a Shared Inventory

Give the chest a **Shared Inventory Manager** on a replicating actor. `NinjaInventorySharedStorageActor` includes both. On the server, check your game's access rule, then call `OpenSessionForActor` with the player. The chest can now recognize the player's inventory for operations on its contents. Call `CloseSessionForActor` when the player closes the chest or walks away. Use `IsActorAuthorized` to check an existing session.

If players can rearrange items inside the chest, show its actual containers and bind the widgets to the chest's inventory. A **loot panel** shows the items the chest has offered this player. Use it when the player should choose what to take from a selection.

## Choose What the Chest Offers

| Source of loot | Setup |
| --- | --- |
| Items already in a chest or on a defeated character | Use the inventory-items loot selector. Add a **Loot Fragment** to each item that can appear. |
| Items in selected containers | Use the lootable-containers selector to limit the search. |
| Rewards drawn from a table | Use the data-table selector. Set chances and a budget for the rewards you want. |

Call `GenerateLoot` on the source with the player's manager. The player receives an offer, can take entries with `TransferLoot`, and can clear the panel with `DismissLoot`. The source's **Loot Persistency Mode** controls whether a selection is generated again or remembered for that requester. **Remove Looted Items From Source** on the receiving manager controls whether claiming a real source item also removes it from the chest.

For a custom selector, override `GenerateLoot`. To keep the standard inventory-item rules and change which items are candidates, override `GetItems` on the inventory-items selector. The [shared loot container guide](inv_inventory_loot.md) walks through one chest with a guaranteed reward.

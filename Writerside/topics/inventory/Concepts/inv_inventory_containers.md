# Owners, Containers, and Layouts
<primary-label ref="inventory"/>

A player's bag, belt, and equipment slots can all belong to one **Inventory Manager**. The **owner** holds that manager. The **avatar** is the actor that uses the items or wears the gear. For a player whose possessions survive a pawn change, put the manager on the Player State and let the current pawn act as the avatar.

## Choose a Layout

| What you want to build | Layout | What takes up space |
| --- | --- | --- |
| A bag or hotbar with a known number of entries | [Simple Layout](inv_guide_simple_grid.md) | Each item or stack occupies one slot. An attribute can supply the slot count for upgradable bags. |
| A backpack the player can rearrange | [Spatial Layout](inv_guide_spatial_grid.md) | The item's Dimensions Fragment supplies its footprint. The whole shape must fit in the available cells. |
| A hand, holster, or armor slot | [Equipment Layout](inv_guide_equipment.md) | A compatible item takes the slot and enters the layout's default equipment state. |

## Decide Where a Pickup Goes

Put `Inventory.Container.Trait.Default` on the starting bag so the manager can find a default home for pickups. Use **Item Compatibility Query** on a container to decide what it accepts. For example, tag arrows with a project tag such as `Item.Ammo.Arrow` and require that tag on a quiver. Other items can still go into the backpack.

Use the item's **Container Placement Fragment** to give it a **Preferred Container Query**. An arrow can prefer containers tagged as quivers while the backpack remains available for general storage. When several candidate containers qualify, the lower **Priority** number goes first. The selected layout still needs room.

## Find the Right Inventory

Implement `GetInventoryManager` on the **Inventory System Interface** when another system needs to find the owner's manager. Use `GetContainersByQuery` on that manager to find containers by their gameplay tags. If a screen should show one particular bag, assign its container definition to the [container widget](inv_ui_mvvm.md). For a chest used by several players, give the [chest its own manager](inv_shared_inventories.md).

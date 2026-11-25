# Firearms and Ammunition
<primary-label ref="combat"/>

A firearm has ammunition ready to fire and can draw more from its owner's reserve. The **Firearm Definition** sets the fire mode, shot behavior, capacity, and reload rules. The **Firearm Component** tracks the current weapon. The character's **Shoot** and **Reload** abilities coordinate its animation and Gameplay Effects.

## Follow One Shot

The player's press tells the component they want to fire. The component requests the Shoot ability, which handles the shot and confirms firing. A hitscan checks the path immediately. A projectile travels as a game actor. The fire mode determines whether holding the button requests additional shots.

## Follow One Reload

The firearm queries the owner's ammo storage for a matching ammo type. The **Reload Ammo** montage notify marks when ammunition moves into the weapon. A magazine reload can fill the available space in one step. A single-round reload repeats this step in a montage loop.

Implement `ICombatAmmoStorageInterface` to supply ammunition from another system. `GetAvailableAmmo` reports what the query can use, and `TakeAmmo` removes the amount supplied. For a reserve-ammo counter, use `BindToAvailableAmmoChangedDelegate`. See [Configure a Firearm and Reload It](cbt_guide_firearms.md) for two playable setups and [Combat and Inventory](integration_combat_inventory.md) for inventory-backed ammo.

# Combat and Inventory: Fight with Equipped Weapons
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>

Equip a rifle from a backpack, fire it, then reload from an ammo stack. Inventory supplies the weapon actor in the player's hand and counts the reserve rounds. Combat uses that actor to fire and tracks the rounds loaded in its magazine. Start with a working [equipment slot](inv_guide_equipment.md) and a [firearm with shooting and reload abilities](cbt_guide_firearms.md).

## Weapon Manager

<procedure title="Let equipment supply the active weapon">
    <step><p>On the character, keep its <code>NinjaEquipmentManagerComponent</code> and use <code>NinjaCombatEquipmentAdapterComponent</code> as its only Combat Weapon Manager. Return the adapter from <b>Get Weapon Manager Component</b> (<code>GetWeaponManagerComponent</code>) on the <b>Combat System Interface</b>. Remove the rifle from Combat's default weapon classes if it was previously spawned there.</p></step>
    <step><p>Give the rifle's Item Definition a project tag such as <code>Item.Weapon.Primary</code>. In its <b>Equipment Fragment</b>, add the <code>Inventory.Equipment.State.Equipped</code> state. Choose <b>Actor</b> as the presence and assign a Blueprint based on <code>NinjaCombatEquipmentWeaponActor</code>. Put the rifle mesh and its Firearm Component on this actor.</p></step>
    <step><p>Let the hand slot accept the item's tag and set its equipped socket. In the combat ability's <b>Weapon Query</b>, require both the item tag and the equipped state. Move the rifle from the backpack into that slot. Combat searches the equipment's tags and returns the first matching weapon actor.</p></step>
</procedure>

## Weapon Actor

If your game already has a weapon actor, keep its **Combat Weapon Interface** and add a `NinjaEquipmentActorComponent` to access the equipment and its item. The supplied equipment weapon can use the item's level as its hit effect level. To drive damage from a rolled item stat, read the item's **Dynamic Attributes** fragment in the weapon's `GetAdditionalCombatMagnitudes` override and add the value under the damage tag your effect reads. In C++, extend `GetAdditionalCombatMagnitudes_Implementation` and preserve the parent's magnitudes. An **Offhand Position** fragment can also supply the support-hand position for a two-handed weapon.

## Ammo Storage

<procedure title="Reload from an inventory stack">
    <step><p>Add <code>NinjaCombatInventoryAmmoAdapterComponent</code> to the character as its only ammo storage component. Create an ammunition Item Definition tagged, for example, <code>Inventory.Item.Type.Ammo.Rifle</code>. Add a <b>Stack and Quantity</b> fragment, set a stack limit of at least ten, and enable <b>Can Be Observed</b>.</p></step>
    <step><p>On the adapter, set <b>All Ammo Types Query</b> to include your ammo items. On the rifle's Firearm Definition, set <b>Ammo Query</b> to the rifle ammo tag. The first query tells the adapter which stack changes to watch. The rifle's query determines which rounds it can actually take.</p></step>
    <step><p>Give the backpack ten reserve rounds. Use a full magazine of at least three, fire three shots, and trigger a magazine reload. At the reload notify the magazine should refill and seven rounds should remain in inventory.</p></step>
</procedure>

For an ammo counter, read `GetAvailableAmmo` with the rifle's query when the widget opens. Bind `BindToAvailableAmmoChangedDelegate` on the ammo storage interface for later changes. Unbind with `UnbindFromAvailableAmmoChangedDelegate` when the widget closes. Combat calls `TakeAmmo` during reload, so the widget only displays the result.

## Try It in Play

Replace the rifle in the hand slot with a second weapon bearing the same primary tag and a visibly different mesh. Fire again and check which actor supplies the shot. Move it back to the bag and verify the slot no longer supplies a weapon. Finally, try reloading the rifle with only an incompatible ammo stack. Its magazine and that stack should both keep their counts.

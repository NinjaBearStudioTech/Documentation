# Use, Store, and Drop Items
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Add menu actions to use one bandage, stow a lantern, and drop an item as a pickup. Start with a player who has a working Ability System Component, a [stackable bandage](inv_guide_inventory_items.md), and an [equipped lantern](inv_guide_equipment.md).

<procedure title="Prepare the actions">
    <step><p>Give the bandage a <b>Consumable Fragment</b>. Set its <b>Consumable Effect</b> to a Gameplay Effect the player can receive, such as restoring health. Choose the stack-charge use mode and set <b>Quantity Per Use</b> to one.</p></step>
    <step><p>To make the bandage droppable, add a <b>Drop Fragment</b>. For <b>Pickup Actor Class</b>, assign an actor Blueprint that implements <b>Inventory Pickup Interface</b> on the actor itself. If it uses a pickup component, forward the interface functions to that component, including <code>SetPickupDefinitions</code>. The spawned pickup then receives the dropped stack's actual contents.</p></step>
    <step><p>Grant the player abilities based on <code>InventoryAbility_Consume</code>, <code>InventoryAbility_Store</code>, and <code>InventoryAbility_Drop</code>. For a test without montages, enable <b>Should Trigger Action on Missing Animation</b> on the ability defaults. The Store example uses the lantern's existing Stored state.</p></step>
</procedure>

<procedure title="Send the selected item from the menu">
    <step><p>On <b>Use</b>, call <b>Send Gameplay Event to Actor</b> on the player avatar with <code>Inventory.Event.Consume</code>. Set <b>Optional Object</b> in the payload to the selected live inventory item. In an item widget, obtain it from the item view's <b>Get Source Item</b>. The Consume ability listens for this event by default.</p></step>
    <step><p>For <b>Store</b> and <b>Drop</b>, add a <b>Gameplay Event</b> trigger to each corresponding ability Blueprint. Use distinct project tags, for example <code>Game.Inventory.Command.Store</code> and <code>Game.Inventory.Command.Drop</code>. Send the matching event and selected item from each menu button. Leave fallback item queries empty if the command should affect only the selection.</p></step>
</procedure>

To time an action to an animation, configure the ability's **Trigger Policy** and montage. When using an animation event, send the ability's configured event tag at the frame where the item should change. To customize which items qualify or what an action does, override `IsEligibleItem` or `ExecuteItemAction` in your ability subclass. A menu can also check the Consumable Fragment's `CanConsume` before enabling **Use**.

## Try It in Play

Use a bandage while injured and check both health and stack count. Select the lantern and try the same Use command. The bandage count should stay the same. Stow the equipped lantern and check its belt socket. Drop the remaining bandages and collect the pickup again. Its quantity should match what you dropped.

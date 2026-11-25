# Interaction and Inventory: Collect an Item from an Interactable
<primary-label ref="integrations"/>
<secondary-label ref="interaction-sec"/>
<secondary-label ref="inventory-sec"/>

Use Ninja Interaction to decide **when** a world pickup is collected and Ninja Inventory to decide **how much fits**. Start with a [character with inventory](inv_first_steps.md) and an [immediate Collect slot](int_guide_without_focus.md). The same transfer works for a focused pickup confirmed with a button.

<procedure title="Transfer the item on successful interaction">
    <step><p>On the interaction actor, add a <b>Ninja Inventory Pickup Component</b>. Choose <b>Initial Items</b> as its <b>Item Source</b>. Add an item definition and quantity under <b>Pickup Items</b>. For the first test, use one item that already fits the player's container.</p></step>
    <step><p>Bind the Interaction Target Component's <b>On Interaction Finished</b>. Check for <code>Interaction.Type.Collect</code>. On the server, get the pawn from the event's source Interaction Manager and pass it to <b>Try Grant Items</b> (<code>TryGrantItems</code>) on the pickup component. Run the grant once here. If you use walk-over collection, the registration handler only requests the interaction.</p></step>
    <step><p>Use the pickup component's <b>Destroy Owner When Fully Consumed</b> setting, or bind <code>OnFullyConsumed</code> to disable the slot and play a collection effect. Leave <code>Interaction.Trait.Disposable</code> off if the player should be able to retry a failed or partial transfer. A successful interaction can finish even when inventory capacity prevents the transfer.</p></step>
</procedure>

The pickup component calls `AddItemsFromPickupActor` and uses `HandlePickupResults` to subtract the quantities actually accepted. For a custom pickup implementation, see [Give a Pickup Its Own Behavior](inv_guide_inventory_items.md#give-a-pickup-its-own-behavior).

## Try It in Play

Walk past a pickup with space available. Check that the quantity increases once and the depleted pickup disappears or becomes unavailable. Fill the inventory and repeat with a fresh pickup. Its contents should remain in the world. Free a slot, leave and re-enter pickup range, and try again. For a stack, also test with room for only part of it and check the remaining quantity.

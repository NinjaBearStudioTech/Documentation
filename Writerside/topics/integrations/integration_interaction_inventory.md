# Interaction and Inventory: Collect an Item from an Interactable
<primary-label ref="integrations"/>
<secondary-label ref="interaction-sec"/>
<secondary-label ref="inventory-sec"/>

Let a player walk over a bundle of five bandages. Ninja Interaction decides when collection starts. Ninja Inventory decides how many fit. The same transfer also works for a focused pickup that the player collects with a button.

<procedure title="Make the Collect slot grant bandages">
    <step><p>Start with a <a href="inv_first_steps.md">character with an inventory</a> and an actor with an <a href="int_guide_without_focus.md">immediate Collect slot</a>. The actor implements the <b>Interaction Target Interface</b> and has an Interaction Target Component. Add a <b>Ninja Inventory Pickup Component</b> to that actor. Set <b>Item Source</b> to <b>Initial Items</b> and add five stackable bandages under <b>Pickup Items</b>.</p></step>
    <step><p>Bind the Target Component's <code>OnInteractionFinished</code>. Check for <code>Interaction.Type.Collect</code>. On the authority branch, call <code>GetPawn</code> on the event's source Interaction Manager and pass that pawn to <code>TryGrantItems</code> on the pickup component. For walk-over collection, the overlap starts the interaction and the finish callback performs the transfer.</p></step>
    <step><p>Enable <b>Destroy Owner When Fully Consumed</b>, or bind <code>OnFullyConsumed</code> to disable the slot and play a collection effect. Leave <code>Interaction.Trait.Disposable</code> off so the player can return for the remainder. Finishing the interaction tells you the player reached the pickup. Inventory's result tells you what they received.</p></step>
</procedure>

## Show How Many the Player Collected

For a message such as **Collected 2 bandages**, use `ConsumedAmount` and `SourceIndex` from each pickup result. In a C++ pickup component, override `HandlePickupResults_Implementation` and call `Super::HandlePickupResults_Implementation(Results)` once so the component deducts the accepted quantities. In Blueprint, an actor implementing the **Inventory Pickup Interface** can forward `HandlePickupResults` to its pickup component and read the same results. Use `OnFullyConsumed` for the final disappearance. [Give a Pickup Its Own Behavior](inv_guide_inventory_items.md#give-a-pickup-its-own-behavior) explains how Inventory finds the pickup implementation.

## Try It in Play

Collect all five bandages with space available. The bag should gain five and the pickup should disappear or become unavailable. Try a fresh bundle with room for only two in an existing stack and no empty slots. Expect two in the bag and three left in the world. Try again with the bag full, then free space and re-enter range. The last collection should grant exactly three. If cancelling a focused interaction also grants items, check that only the finish event calls `TryGrantItems`.

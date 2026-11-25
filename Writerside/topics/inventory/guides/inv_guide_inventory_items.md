# Create a Stackable Item and Pickup
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Make a bandage pickup that gives three bandages at a time. Two pickups should give the player a stack of five and a second stack of one. Start with an empty [slot-based bag](inv_guide_simple_grid.md) or [spatial backpack](inv_guide_spatial_grid.md) with room for two stacks.

<procedure title="Define the stack">
    <step><p>Create or open <b>Item_Bandage</b>. Add a <b>Container Placement Fragment</b> and a <b>User Interface Fragment</b> with a name and icon. For a spatial bag, also add a one-by-one <b>Dimensions Fragment</b>.</p></step>
    <step><p>Add a <b>Stack and Quantity Fragment</b>. Set <b>Stack Limit</b> to five, <b>Maximum Quantity</b> to at least six, and enable <b>Allow Stack Merge</b>. The pickup's starting quantity is a separate setting.</p></step>
</procedure>

<procedure title="Place two pickups in the level">
    <step><p>Create a Blueprint based on <code>NinjaInventoryPickupActor</code> and give it a visible mesh. It already includes a pickup component and a sphere that collects on pawn overlap. Make sure the player's collision generates overlap events with the sphere.</p></step>
    <step><p>On the inherited pickup component, choose <b>Initial Items</b> for <b>Item Source</b>. Add <b>Item_Bandage</b> to <b>Pickup Items</b>. In that entry's <b>Initial Fragment Data</b>, select the stack fragment, add <b>Stack Memory</b>, and set <b>Stack Size</b> to three. Enable <b>Destroy Owner When Fully Consumed</b> if the empty pickup should disappear.</p></step>
    <step><p>Place two copies far enough apart to collect them separately. If your game uses a button to collect items, use an actor with a pickup component and call <code>TryGrantItems</code> on the server from the confirmed action. See <a href="integration_interaction_inventory.md">Interaction and Inventory</a> for the Collect setup.</p></step>
</procedure>

## Give a Pickup Its Own Behavior

For a custom pickup, implement `IInventoryPickupInterface`. Return its remaining entries from `GetPickupItemDefinitions` and accept replacement entries in `SetPickupDefinitions`. Give the actor to the player's manager with `AddItemsFromPickupActor`. In `HandlePickupResults`, subtract each entry's **Consumed Amount**. A full bag may accept nothing, and a nearly full stack may accept only part of the pickup. The built-in pickup component does this bookkeeping. Bind its `OnFullyConsumed` event for a depletion effect.

## Try It in Play

Walk over the first pickup and check for three bandages. Collect the second and check for stacks of five and one. To test a partial grant, repeat with only one free slot in the bag and no existing bandages. The first pickup fills three places in the stack. The second tops it up to five and keeps one bandage in the world. Free a slot, leave the sphere, and walk back to collect the last bandage.

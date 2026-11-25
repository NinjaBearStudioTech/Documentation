# Build a Standard Slot-Based Inventory
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

Build a bag that holds six entries. A key takes one slot. A stack of bandages also takes one slot. Start with the player and registered assets from [First Steps](inv_first_steps.md).

<procedure title="Give the player six slots">
    <step><p>Open <b>Container_Backpack</b>, or create a Container Definition with that name. Give it the tag <code>Inventory.Container.Trait.Default</code>. Choose <b>Simple Layout</b>, set <b>Slot Count Type</b> to <b>Property</b>, and set <b>Slots</b> to six. Leave the item compatibility query empty so the bag accepts the test items.</p></step>
    <step><p>On the player's Inventory Manager, set this bag as the only <b>Initial Containers</b> entry. Start with empty <b>Initial Items</b> and a fresh inventory for the capacity test.</p></step>
    <step><p>Create an item such as a brass key. Add a <b>Container Placement Fragment</b>, a <b>User Interface Fragment</b> with an icon, and a <b>Stack and Quantity Fragment</b>. Use a <b>Stack Limit</b> of one and a <b>Maximum Quantity</b> of at least seven. Place seven single-key <a href="inv_guide_inventory_items.md">pickups</a> in the level.</p></step>
</procedure>

<procedure title="Show all six slots in the player's menu">
    <step><p>Create a Widget Blueprint based on <code>NinjaInventoryItemWidget</code>. Give it a visible slot background and an image for the item. Add an <b>Inventory Item ViewModel</b> with <b>Manual</b> creation. Follow the <a href="inv_ui_mvvm.md#bindings-with-the-item-widget">item widget bindings</a> to pass the item, container, and position into the widget. Bind <b>Get Icon Brush</b> from the <b>User Interface ViewModel</b> to the image brush. Keep the slot background visible when the item is empty.</p></step>
    <step><p>Create a second widget based on <code>NinjaInventoryContainerWidget</code>. In its Inventory settings, set <b>Container Data Asset</b> to <b>Container_Backpack</b> and enable <b>Fill Empty Entries</b>. Add an <b>Inventory Container ViewModel</b> with creation type <b>Resolver</b> and select <b>Inventory Resolver</b>. The base widget finds the player's bag.</p></step>
    <step><p>Add a <b>Wrap Box</b> and choose <b>Add ViewModel Extension</b>. Set <b>Entry Widget Class</b> to your slot widget and <b>Entry ViewModel</b> to the Inventory Item ViewModel. Compile, then bind the container ViewModel's <b>Get Items</b> to the extension's <b>Set Items</b>. Add the bag widget to the owning player's menu.</p></step>
</procedure>

<img src="inv_ui_mvvm_container_bindings.png" alt="Container item list bound to Set Items on the panel extension" width="700" border-effect="line"/>

For a pickup prompt that should say **Bag full**, call `EvaluatePlacementForDefinition` on the player's manager with the pickup entry. Check **Can Store Any Amount** before offering to collect it. For a drag preview over one particular slot, call the container's `CanAcceptItemAtPosition` with the item and destination position.

If a bag upgrade should unlock more slots, change its layout to **Gameplay Attribute** and select an initialized slot attribute such as `BackpackSlots` on the owner's ability system. The same slot widget works with the new capacity.

## Try It in Play

Open the empty bag and count six backgrounds. Collect six keys. Each gets its own icon. Try the seventh pickup while all six slots are occupied. The bag should still show six keys and the pickup should remain available. [Drop a key](inv_gameplay_abilities.md) if you configured it for dropping, or remove one with the Inventory Manager. Collect the remaining pickup and check that the empty slot fills again.

# Adding Items from Pickups
<primary-label ref="inventory"/>

Items can be added to the inventory through actors placed in the world, typically representing loot, rewards, or
interactable pickups.

While the Inventory system provides a ready-to-use base actor class (`ANinjaInventoryPickupActor`), the only requirement
is that your actor implements the `IInventoryPickupInterface`.

The Inventory Manager provides a built-in function, <code>AddItemsFromPickupActor</code>, which can be used to extract
and grant items from any actor that implements this interface. This ensures custom pickup actors remain fully compatible
with the inventory system’s queuing, stacking, and placement logic.

This gives you full control over how pickups behave, while still benefiting from the Inventory system’s item lifecycle
and automation.

## Provided Pickup Actor

<procedure title="Adding Items from a Pickup Actor" collapsible="true" default-state="expanded">
    <step>Create a new Actor that inherits from <b>ANinjaInventoryPickupActor</b>.</step>
    <step>Customize the actor visually and functionally using meshes, effects, audio, or any other components relevant to your game.</step>
    <step>
        <p>In the actor's <code>PickupItems</code> array, define one or more default items that should be granted when the pickup is collected.</p>
        <note>
            The system will attempt to add the item(s) to the collector’s Inventory Manager on overlap.
            If the pickup is successfully granted, the actor will automatically destroy itself.
        </note>
    </step>
</procedure>

## Custom Pickup Actor
<secondary-label ref="advanced"/>

If you'd like to build a custom pickup actor (e.g., for complex interactions, scripted behavior, or special effects), you
can do so by implementing the <code>IInventoryPickupInterface</code>.

This allows you to define your own collection logic while still leveraging the Inventory system’s item creation, queuing,
and placement handling.

<procedure title="Implementing a Custom Pickup Actor" collapsible="true" default-state="expanded"> 
    <step> 
        <p>Create a new actor based on your desired class (e.g., derived from <code>AActor</code> or any custom base).</p>
    </step> 
    <step>
        <p>Implement the <b>IInventoryPickupInterface</b> on your actor class.</p>
    </step> 
    <step>
        <p>Add a property that stores an array of <code>FInventoryDefaultItem</code> entries. This defines the items that can be granted to the inventory.</p> 
    </step> 
    <step> 
        <p>Implement the required interface functions:</p> 
        <ul> 
            <li><code>GetPickupItemDefinitions</code>: returns the current array of item definitions.</li> 
            <li><code>SetPickupItemDefinitions</code>: allows updating the array programmatically.</li> 
        </ul>
    </step>
    <step>
        <p>Implement your pickup logic. When ready to grant the items, call <code>AddItemsFromPickupActor</code> on the target's <b>Inventory Manager</b>.</p>
        <note>
            This will ensure the item is processed through the queue and respects all stacking, placement, and validation rules.
        </note>
    </step>
</procedure>

# Adding Items
<primary-label ref="inventory"/>

Items can be added to the Inventory through different sources, such as a Default Item Data Structure, a Pickup, or Loot 
that has been selected. This page explores those methods in detail, along with advanced usage patterns.

## Add Default Item

<procedure title="Adding an Item to the Inventory" collapsible="true" default-state="expanded">
    <step>
        <p>From an appropriate event, access the <b>Inventory Manager</b> and call <code>AddItem</code>.</p>
        <note>If you are programming for <b>multiplayer</b>, then you must handle the <b>authoritative check</b> and invoke a <b>Server RPC</b> if necessary.</note>
    </step>
    <step>
        <p>Create a new <b>Default Item</b> by setting the <b>Item Data Asset</b> and adding desired <b>Fragment Memories</b> (e.g., Stack).</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_management_add_item.png" alt="Add a default item" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="inv_add_item.cpp"/>
            </tab>
        </tabs>
        <note>Ninja Inventory provides <b>Create Functions</b> for all supported <b>Fragment Memories</b> (Container Position, Durability, Level, Stack, etc.).</note>
    </step>
</procedure>

> **Asynchronous Item Queue**
>
> Although a GUID is assigned right away, items are not added to the inventory immediately.
>
> Items are processed in order, asynchronously (off the game thread), and eventually added to the inventory, or dropped if allocation fails.

### Adding Items and Event Tracking

<secondary-label ref="advanced"/>

In some cases, it might be useful to react to items being added to the inventory. In those cases you can use a **callback**
with the new item information, or the global **Item Event**.

Both the callback and the item event are triggered after the item has been processed by the queue and successfully added 
to the inventory.

| Event Type | Scope                 | Notes                               |
|------------|-----------------------|-------------------------------------|
| Callback   | Authoritative only    | Per-item, step-by-step registration |
| Item Event | Authoritative + Local | Broadcast-based, includes additions |

<procedure title="Adding Items with Events" collapsible="true" default-state="expanded">
    <step>Retrieve the <b>Inventory Manager</b> and bind to the <b>Item Event</b> delegate.</step>
    <step>Create your default item data structure and call <code>AddItemWithCallback</code>.</step>
    <step>
        <p>Connect your logic to both the <b>Item Event</b> and the <b>Callback</b>.</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_management_add_item_with_events.png" alt="Add a default item with events" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <code-block lang="c++" src="inv_add_item_with_events.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

### Item Processor

The logic responsible for processing new items is separated from the Inventory Manager, so developers can easily adjust
their own flows if needed, without having to extend large pieces of the main component.

Item processors are created by extending `UNinjaInventoryItemProcessor`.
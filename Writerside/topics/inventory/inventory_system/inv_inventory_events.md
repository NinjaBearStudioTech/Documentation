# Inventory Events
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Inventory Events</b></p>
    <br/>
    <ul>
        <li>Inventory events are centralized in the <b>Inventory Manager</b>, which exposes <code>OnItemEvent</code> and <code>OnContainerEvent</code> delegates.</li>
        <li>These events include a <b>tag</b> and an <b>instanced payload struct</b>, allowing flexible and decoupled reactions to item and container changes.</li>
    </ul>
</tldr>

All Inventory Events, whether related to **items** or **containers**, are **centralized in the Inventory Manager**.

This means you do not need to manually track events on individual fragments, containers, or item instances. Instead, you
can simply listen to the appropriate event delegate exposed by the manager.

The Inventory Manager provides two primary **multicast delegates** for reacting to inventory-related events:

| Event              | Signature                                                                             |
|--------------------|---------------------------------------------------------------------------------------|
| `OnContainerEvent` | `UInventoryContainer* Container`, `FGameplayTag EventTag`, `FInstancedStruct Payload` |
| `OnItemEvent`      | `UInventoryItem* Item`, `FGameplayTag EventTag`, `FInstancedStruct Payload`           |

Both delegates share a consistent structure:

- **Target Object**: Either the Container or Item involved in the event.
- **EventTag**: A Gameplay Tag that describes the event type.
- **Payload**: A `FInstancedStruct` that holds additional data related to the event (see [Event Payloads](#event-payloads)).

## Binding to Events

To listen for events, simply bind to the appropriate delegate in the Inventory Manager:

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <i>Image coming soon...</i>
        <!-- <img src="inv_setup_inventory_interface.png" alt="Binding to Inventory Events" width="800" thumbnail="true" border-effect="line"/> -->
    </tab>
    <tab title="C++" group-key="cpp">
        <p>Add a dynamic binding to each delegate:</p>
        <code-block lang="c++" src="inv_events_binding.cpp"/>
        <p>Make sure your handler functions match the delegate signatures:</p>
        <code-block lang="c++" src="inv_events_function_signatures.cpp"/>
    </tab>
</tabs>

## Event Payloads

Each event's payload contains data relevant to that specific action. You can safely extract this payload by checking the
event's tag and casting the `FInstancedStruct` to the appropriate Payload Struct type.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <i>Image coming soon...</i>
        <!-- <img src="inv_setup_inventory_interface.png" alt="Handling an Inventory Payload" width="800" thumbnail="true" border-effect="line"/> -->
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_events_handling.cpp"/>
    </tab>
</tabs>

## Event Reference

This section covers details for each event emitted by **Containers** and **Items**, including the correct **Payload Struct**
and **available attributes**.

> **Additional Inventory Events**
>
> The Inventory Manager will also broadcast events related to its [**initialization**](inv_inventory_management.md#inventory-events)
> and [**loot**](inv_inventory_loot.md#loot-events). Check these specific pages for additional information.

### Container Events

All container event payloads are `FInventoryContainerEventPayload` or specific subtypes.

<table>
    <tr>
        <td>Event And Payload</td>
        <td>Payload Attributes</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Container.AddedToInventory</code></li>
                <li><code>FInventoryContainerEventPayload</code></li>
            </ul>
        </td>
        <td>Container</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Container.RemovedFromInventory</code></li>
                <li><code>FInventoryContainerEventPayload</code></li>
            </ul>
        </td>
        <td>Container</td>
    </tr>
</table>

### Item Events

All item event payloads are `FInventoryItemEventPayload` or specific subtypes.

<table>
    <tr>
        <td>Event And Payload</td>
        <td>Payload Attributes</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.AddedToInventory</code></li>
                <li><code>FInventoryItemEventPayload</code></li>
            </ul>
        </td>
        <td>Item</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.ContainerChanged</code></li>
                <li><code>FInventoryItemContainerPlacementPayload</code></li>
            </ul>
        </td>
        <td>Item, Container, Previous Container, Position, Previous Position</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.DroppedFromInventory</code></li>
                <li><code>FInventoryItemDropPayload</code></li>
            </ul>
        </td>
        <td>Item, Pickup Actor</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.DurabilityChanged</code></li>
                <li><code>FInventoryItemDurabilityPayload</code></li>
            </ul>
        </td>
        <td>Item, Durability</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.EquipmentStateChanged</code></li>
                <li><code>FInventoryItemEquipmentEventPayload</code></li>
            </ul>
        </td>
        <td>Item, EquipmentStateTag</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.LevelChanged</code></li>
                <li><code>FInventoryItemLevelPayload</code></li>
            </ul>
        </td>
        <td>Item, Level</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.PositionChanged</code></li>
                <li><code>FInventoryItemContainerPlacementPayload</code></li>
            </ul>
        </td>
        <td>Item, Container, Previous Container, Position, Previous Position</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.RemovedFromInventory</code></li>
                <li><code>FInventoryItemEventPayload</code></li>
            </ul>
        </td>
        <td>Item</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.RotationChanged</code></li>
                <li><code>FInventoryItemDimensionsPayload</code></li>
            </ul>
        </td>
        <td>Item, bIsRotated</td>
    </tr>
    <tr>
        <td>
            <ul>
                <li><code>Inventory.Event.Item.StackChanged</code></li>
                <li><code>FInventoryItemStackAndQuantityPayload</code></li>
            </ul>
        </td>
        <td>Item, StackSize</td>
    </tr>
</table>



# Inventory Manager
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>This component is the <b>core</b> of the Inventory System.</li>
        <li>It manages <b>Containers</b> and <b>Items</b> assigned to an <b>Inventory Owner</b>.</li>
        <li>Provides multiple <b>query methods</b> for Containers and Items along with functions to perform <b>operations</b> on them.</li>
        <li>It may be added to <b>Pawns</b> or to the <b>Player State</b>.</li>
        <li>Classes with an Inventory Manager must also implement <code>InventoryManagerProviderInterface</code>.</li>
        <li>The Inventory Manager needs to access an <b>Ability System Component</b>.</li>
    </ul>
</tldr>

The **Inventory Manager** is the central component that manages **Containers** and **Items** available to a **Pawn** or
**Player State**. 

## Setup

The Inventory Manager can be added to **Pawns** or a **Player State**. Its only pre-requisite is that its owner is able
to provide an **Ability System Component**.

The owner of an Inventory Manager should also implement `InventoryManagerProviderInterface`. This interface has a few
methods, but the only one should always be implemented is `GetInventoryManager`.

If the Inventory Manager is added to a **Player State**, its Pawn should also implement that interface and either provide
the Inventory Manager **directly** from the state, or store and provide a **local copy**.

## Initialization

The Inventory Manager is self-contained, and it will initialize itself. It requires a valid **Pawn** (_Inventory Avatar_) 
and an **Ability System** to initialize. This is particularly relevant in the following scenarios:

- When the Inventory Manager is added to a **Player State**, it will retrieve the avatar from it.
- In **Network Scenarios**, the Inventory will wait for the Pawn and ASC to **replicate** so it can initialize.

> **Asynchronous Initialization**
> 
> Waiting for these elements happens **asynchronously** and won't lock your game thread.
> For more information, please check `NinjaInventoryAction_WaitForAbilitySystem`.

You can fine tune how the polling process happens by adjusting the following properties:

- `AbilitySystemPollInterval`: How often it will check for the Ability System's presence.
- `AbilitySystemMaxWait`: Maximum amount of time the inventory will wait for the ASC to replicate.

Issues during this process will be added to your **Inventory Log**.

Once fully initialized, the Inventory will notify any classes waiting for it, via the `OnInventoryInitialized`. You can
also query the initialization state by calling `IsInventoryInitialized`.

## Default Objects

The Inventory can receive a **Layout** and **Default Items** directly, via its properties. However, if you need to have 
more flexibility, allowing each _avatar_ to define their own Layout or Default Items, you can do so using the
`InventoryManagerProviderInterface`.

This interface has the following functions that can be used to customize the initialization:

- `GetInventoryLayout`: Provides the Layout that will be used when the Inventory Manager initializes.
- `GetDefaultItems`: Provides all default items granted when the Inventory Manager initializes.

> **Default Items**
> 
> If the Inventory Manager has **Default Items**, these will be consolidated with the ones obtained from the interface.
{style="note"}

## Query Methods

There are many **read-only** operations available to query **Containers** and **Items** added to the Inventory, which 
are presented as multiple `Getter` and `Count` functions.

> **Caching**
> 
> The Inventory Manager contains caching structures for Items and Containers, to avoid constantly iterating over arrays.
> 
> These transparent structures will perform many Item and Container lookups with an **O(1)** time-complexity. 

## Operations

The following **operations** can add or remove **Containers** and **Items**. Items in particular can be added from a few
different sources. The Inventory Manager is also a gateway for **Fragment Operations**. 

> **Network Authority**
> 
> For networked games, all **add** and **remove** operations must be performed in the **authoritative** version.
{style="note"}

### Managing Containers

Containers are **added** by the `AddContainer` function, like so:

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_add_container.png" alt="Add a container to the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_add_container.cpp"/>
    </tab>
</tabs>

Containers are **removed** by the `RemoveContainer` function. You can also remove a container by its unique **identifier**,
using the `RemoveContainerById` function.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_remove_container.png" alt="Remove a container from the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_remove_container.cpp"/>
    </tab>
</tabs>

> **Relocating Items**
> 
> The Inventory will attempt to **relocate** Items stored in the container being removed. You can check beforehand to
> make sure that items can be relocated, by calling `CanRelocateItemsInContainer`.

### Managing Items

Items can be **added** to the inventory in a few different ways:

- With an **Item Data** and optional default memories.
- From a **Pickup Actor**.
- From **Selected Loot**.

Whenever an item is added, a validation process will happen and, based on the fragments configured for the item, and the
current state of the Inventory, the item will be **accepted** or **rejected**.

> **Rejection Messages**
> 
> If an item is **rejected**, check your logs. You will find details on what fragment has rejected the item. This entry 
> will be displayed under `LogNinjaInventory` with a `Verbose` level. 
> 
> Make sure to enable that visibility in your `DefaultEngine.ini`, with the following lines:
> 
> ```
> [Core.Log]
> LogNinjaInventory=Verbose
> ```

#### Add Item Data

First, by the `AddItem` function, which allows you to set **optional** default memories to the item.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_add_item.png" alt="Adds an item to the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_add_item.cpp"/>
    </tab>
</tabs>

If you want to create **default memories**, similar to what you can do when adding default items to the inventory, then
you can use the provided functions:

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_create_default_memories.png" alt="Crates default memories for new items" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_create_default_memories.cpp"/>
    </tab>
</tabs>

#### Add Pickup Actors

Another way to add an item directly from a **pickup**, via the `AddPickup` function. The `PickupActor` parameter must be
a valid actor that implements `InventoryPickupInterface`.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_add_pickup.png" alt="Adds a pickup to the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_add_pickup.cpp"/>
    </tab>
</tabs>

#### Add Selected Loot
<secondary-label ref="wip"/>

You can also add items that were selected by a **Loot Manager**, via the `AddLoot` function.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_add_loot.png" alt="Adds selected loot to the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_add_loot.cpp"/>
    </tab>
</tabs>

#### Remove Items

Items are **removed** by the `RemoveItem` function. You can also remove an item by its unique **identifier**,
using the `RemoveItemById` function.


Additionally, you can set an amount of items to remove from the item's **stack**. A value of **zero** will always 
remove the **entire stack**.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="inv_remove_item.png" alt="Removes an item from the inventory" thumbnail="true"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="inv_remove_item.cpp"/>
    </tab>
</tabs>

## Replication

Inventory Items only replicate from the **authoritative component** to the **local client**. You won't be able to query
items and containers in **simulated proxies**.

## Delegates

The Inventory Manager will **broadcast** its events using the following delegates listed in the table below.

They will broadcast on both the **authoritative** and **local client** versions.

| Delegate              | Event                                          |
|-----------------------|------------------------------------------------|
| Inventory Initialized | The inventory has been initialized.            |
| Container Added       | A container was added to the inventory.        |
| Container Removed     | A container was removed from the inventory.    |
| Item Added            | An item was added to the inventory.            |
| Item Storage Changed  | An item's storage has changed.                 |
| Item Removed          | An item has been removed from the inventory.   |
| Loot Received         | Loot has been made available to the inventory. |
| Loot Dismissed        | Loot has been dismissed for the inventory.     |

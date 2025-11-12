# Inventory Management
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Inventory Management</b></p>
    <br/>
    <ul>
        <li>The <b>Inventory Manager</b> manages <b>containers</b> and <b>items</b> dynamically with high flexibility.</li>
        <li>Optionally integrates with <b>GAS</b>, but doing so incorrectly can cause issues.</li>
        <li>Exposes events, accessors, and safeguards like <b>stranded item handlers</b>.</li>
    </ul>
</tldr>

The `NinjaInventoryManagerComponent` is the core of the Ninja Inventory System. It manages **containers**, **items**, 
**ownership**, and **data flow** between inventory instances and other systems like Gameplay Abilities and Save/Load.

This page provides an overview of the key systems and methods available to developers.

## Initialization
The Inventory Manager must be **initialized** before it can be used. Initialization is usually performed automatically 
during the component's `InitializeComponent` function, which is invoked as part of the standard **Actor Lifecycle**.

The manager **can** function without a Gameplay Ability System, which may be appropriate in scenarios that don't require 
complex inventory interactions—such as **chests**, **vendors**, or other non-playable containers.

To know more about the Inventory Setup, please check the corresponding [setup page](inv_inventory_system.md).

## Inventory Events
The Inventory Manager exposes several events that can be used so other systems can react to changes at runtime:

| Event Name                           | Description                                                  |
|--------------------------------------|--------------------------------------------------------------|
| `OnInventoryInitializationSucceeded` | Broadcast when the inventory is successfully initialized.    |
| `OnInventoryInitializationFailed`    | Broadcast when the inventory fails to initialize.            |
| `OnContainerEvent`                   | Broadcasts a change in a container managed by the inventory. |
| `OnItemEvent`                        | Broadcasts a change in an item managed by the inventory.     |

The Inventory Manager centralizes **all events** related to its managed instances. This means all **containers**,
**items** and their **fragments** will only broadcast events through the Inventory Manager, making it a central **Event Hub**.

Container and Item events will contain a generic **payload**, a `FInstancedStruct`, and varies depending on the source 
(container, item, or fragment). This allows downstream systems to deserialize and react accordingly.

## Inventory Avatar
The **Inventory Avatar** is the actor most closely associated with the inventory when representing it in the **game world**. 
This is usually:

- The **Pawn** owning the inventory.
- The Pawn associated with the **Player State** owning the inventory.
- Or the **Ability System Component Avatar**, if bound through a `UAbilitySystemComponent`.

This distinction matters for gameplay logic that relies on the owner of items or containers, especially when applying 
effects or evaluating interactions.

## Container Management
Containers are dynamic structures that hold items and define available inventory space or rules. They can be added and 
removed at runtime. To know more about containers, please check the corresponding [Container page](inv_inventory_containers.md).

Containers can be managed using the following transactional functions:

| Function                   | Description                                                                                                                                                          |
|----------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `AddContainer`             | Adds a container from a `ContainerData` asset. Returns a GUID for the new instance.                                                                                  |
| `AddContainerWithCallback` | Adds a container and invokes a callback with direct access to the new Container Instance. Returns a GUID for the instance. Must be called on authority.              |
| `AddNestedContainer`       | Adds a nested container related to an inventory item. Useful to represents items that are container themselves, like _pots_ or _boxes_. Must be called on authority. |
| `RemoveContainer`          | Removes a container from the inventory.                                                                                                                              |
| `RemoveContainerById`      | Removes a container using its unique identifier as a target criteria.                                                                                                |

> **Server Authority**
>
> All functions listed above require **server authority**, and will trigger a server RPC when invoked from a locally
> controlled autonomous client (unless marked otherwise).
{style="note"}

Containers can be queried using the following read-only functions:

| Function               | Description                                                                    |
|------------------------|--------------------------------------------------------------------------------|
| `CountContainers`      | Returns the number of containers currently assigned to this inventory.         |
| `GetContainer`         | Finds and returns a container by its unique GUID.                              |
| `GetDefaultContainers` | Retrieves containers that are flagged as default for this inventory instance.  |
| `GetContainersByData`  | Returns all container instances created from a specific `ContainerData` asset. |
| `GetContainersByQuery` | Retrieves all containers matching a `GameplayTagQuery`.                        |
| `GetContainersByItem`  | Retrieves all containers owned by an Inventory Item (nested containers).       |

## Item Management
Even though items are ultimately stored in their assigned containers, the Inventory Manager is completely aware of them,
and it's also the entry-point for item maintenance. To know more about items, please check the corresponding [Item page](inv_inventory_items.md).

Items can be managed using the following transactional functions:

| Function                          | Description                                                                                                                   |
|-----------------------------------|-------------------------------------------------------------------------------------------------------------------------------|
| `AddItem`                         | Adds a new item using the given `ItemInfo` struct. Returns a GUID for the new item instance.                                  |
| `AddItemWithCallback`             | Adds a new `ItemInfo` and receives a callback executed during main **initialization events**. Authority only (no server RPC). |
| `AddItemsFromPickupActor`         | Adds items from a Pickup Actor that implements `InventoryPickupInterface`. Returns item GUIDs.                                |
| `TransferItem`                    | Transfers an item from one inventory to another, returning the new item GUID. Requires an **authorization session**.          |
| `TransferItemWithMemoryOverrides` | Transfers an item, overriding or adding new memories to it. Requires an **authorization session**.                            |
| `TransferDefaultItem`             | Transfers a default item structure, which must include a source item and inventory. Requires an **authorization session**.    |
| `RemoveItem`                      | Removes an item from the inventory. Optionally drops it if set to do so and the item has a valid drop fragment.               |
| `RemoveItemById`                  | Removes an item using its unique identifier as a target criteria.                                                             |

> **Server Authority**
> 
> All functions listed above require **server authority**, and will trigger a server RPC when invoked from a locally 
> controlled autonomous client (unless marked otherwise).
{style="note"}

When you add an item to the Inventory Manager, the system will automatically determine container placement, stacking, 
and other behaviors based on your configuration.

You can influence this process using:

- **Preferred Container Query** on the Container Placement Fragment, used to suggest preferred containers for a given item.
- **Item Eligibility Query** on containers, to filter valid items, plus the container's **priority**.
- **Default Placement Memories** (e.g., Container Position), which the system will try to honor if possible (i.e. no items already occupying the position).

>**Let the Inventory Handle It**
> 
>**Avoid manually assigning items to containers**. Let the processor and configuration handle it for more robust and 
>predictable results. 
>
> That said, **direct container assignment is still possible**. Use it only if you're confident that it won't interfere 
> with the inventory's logic or lifecycle.
{style="note"}

Items can be queried using the following read-only functions:

| Function              | Description                                                                                          |
|-----------------------|------------------------------------------------------------------------------------------------------|
| `CountItems`          | Returns the number of item instances in the inventory (does not account for stack sizes or volumes). |
| `GetAllItems`         | Retrieves all items stored in the Inventory.                                                         |
| `GetItemsByData`      | Retrieves all items that match a specific `ItemDataAsset`.                                           |
| `GetItemsByQuery`     | Retrieves all items that match a `GameplayTagQuery`.                                                 |
| `GetFirstItemByQuery` | Returns the first item that matches a given `GameplayTagQuery`.                                      |

## Authorization Sessions

The Inventory Manager provides functions used to authorize an external inventory to perform certain operations, the 
most common example being the **item transfer**. 

Before executing operations between **two distinct Inventory Managers** you need to initiate a _handshake_ resulting in
an **authorization session**. This is only necessary in the authoritative inventory. Also, keep in mind that a session
allows an operation to happen from **either direction**.

| Function                | Description                                        |
|-------------------------|----------------------------------------------------|
| `IsInventoryAuthorized` | Checks if an Inventory Manager is authorized.      |
| `OpenSession`           | Opens an authorization session for an inventory.   |
| `CloseSession`          | Closes the authorization session for an inventory. |

When managing your own inventory, operations like "move", "swap" and so on won't require this session, even in multiplayer,
since an Inventory Manager is **always authorized** to interact with itself.

## Item Processor

The logic responsible for processing new items is separated from the Inventory Manager, so developers can easily adjust
their own flows if needed, without having to extend large pieces of the main component.

Item processors are created by extending `UNinjaInventoryItemProcessor`.

The processor will use your configuration (e.g., queries, default memories) to determine valid placement and stacking. 
For most cases, you won’t need to override this unless you're building a custom flow (e.g., forced container injection or 
loot-specific routing).

## Stranded Items
A **stranded item** is an item that no longer has a valid container. This can happen if:

- A container is **removed** while still holding items.
- An item **fails to be placed** during loading or initialization.

Stranded items are automatically handled by a chain of registered **Stranded Item Handlers**, added to the Inventory
Manager by the `StrandedItemHandlerClasses` property. If no handler resolves the item, it will be **destroyed** and a 
**warning** will be logged.

By default, the Inventory system provides the following handlers:

| Handler                         | Description                                                          |
|---------------------------------|----------------------------------------------------------------------| 
| `StrandedItemHandler_Container` | Attempts to place the item into another valid container.             |
| `UStrandedItemHandler_Drop`     | Spawns the item as a Pickup Actor (if a supporting fragment exists). |

> **Stranded Item Chain**
> 
> This fallback is not ideal. Always configure your handler chain to handle expected gameplay scenarios, such as item 
> reassignment, dropping or any custom handler relevant to your scenario.
{style="warning"}

You can create new Stranded Item Handlers by subclassing `NinjaInventoryStrandedItemHandler`. This class is quite simple
and only expects one function to be implemented: `HandleStrandedItem`. 

If this function is able to handle the stranded item, then it should return `true`, which will interrupt the handler 
chain and move on to the next item, if any.

## Default Values
You can assign default **containers** and **items** directly to the Inventory Manager using the exposed properties in 
the component's **Details Panel**.

Both data types go through the standard validation pipeline. Items can also include default **fragment memories**,
which will be evaluated during item processing.

<img src="inv_overview_manager_defaults.png" alt="Default Containers and Items" width="800" border-effect="line"/>

> **Default Items and Saved Slots**
>
> If the Inventory Manager is set to automatically load a **saved slot**, the default containers and items will be ignored.  
> You can verify where the inventory data is coming from using the [**Inventory Gameplay Debugger**](inv_gameplay_debugger.md).
>
> For more details, refer to the [**Save and Load** documentation](inv_save_and_load.md).
{style="note"}

## Deferred Initialization
When the Inventory component is added to the **Player State**, it may take a few frames before it fully replicates to the 
Inventory Avatar. 

During this short delay, it's common for the avatar to need its own exclusive items, that are not meant to be shared across 
different avatar types, and therefore should not be added directly to the Player State's inventory.

This creates a situation where the avatar must wait for the Inventory system to finish initializing before it can safely 
add those items. Since this process doesn't complete immediately after Begin Play, a **deferred initialization flow** is 
required.

There are two recommended ways to handle this:

1. Use an **asynchronous task** that waits for the inventory system to finish initializing.
2. Implement the **Initialization Watcher Interface** to receive a callback when initialization completes (or fails).

> **Selecting the Best Approach**
>
> The asynchronous task is ideal for one-off scenarios where you have a single avatar type that needs to add some items
> or execute blueprint-friendly logic.
> 
> If you have multiple possible avatar types and want something more streamlined, implement the interface in your base
> avatar class or blueprint type to ensure consistent behavior across all variations.
{style="note"}

### Async Inventory Initialization Task
You can use the built-in **Wait For Inventory System** task, which automatically notifies you when the inventory has
_successfully_ initialized and is ready for item operations.

<img src="inv_management_wait_and_add.png" alt="Asynchronous Initialization" width="800" border-effect="line"/>

When using this task, keep the following in mind:

1. Set a reasonable pooling interval and also a timeout.
2. Always retrieve the Inventory Manager via the **Inventory Function Library**.
3. Add items only from the **authoritative instance** (the server, in most cases).

### Initialization Watcher Interface
For simpler or event-driven setups, you can instead use the `InventoryInitializationWatcherInterface`. This interface 
can be implemented by either the **inventory owner** or the **inventory avatar**.

When the Inventory system reaches a final initialization state, the interface functions will be automatically invoked, 
allowing you to react immediately without polling or tasks.

| Function                            | Description                                             |
|-------------------------------------|---------------------------------------------------------|
| `OnInventoryInitializationFinished` | Called when the inventory has successfully initialized. |
| `OnInventoryInitializationFailed`   | Called when the inventory fails to initialize.          |


# Items and Fragments
<primary-label ref="inventory"/>

<tldr>
<ul>
    <li>Items do not have a <b>presence</b> in the game world.</li>
    <li>Items are defined by the aggregation of <b>item fragments</b>.</li>
    <li>Items are defined by an <b>Item Definition</b> (<code>NinjaInventoryItemDataAsset</code>) and represented by an <b>Item Instance</b> (<code>NinjaInventoryItem</code>).</li>
    <li>Item Fragments are <b>reusable pieces of data and logic</b> that can be added to items.</li>
    <li>All Item Instances created from the same Item Definition will <b>share</b> the same item fragments.</li>
</ul>
</tldr>

Items and item fragments are at the very center of the Inventory system. They are managed by the Inventory Manager and
are data-driven objects without physical presence in the game world.

## Inventory Items

Inventory Items are the primary object type for the Inventory System.

They are defined by the `NinjaInventoryItemDataAsset`, which is a Primary Data Asset that must be registered with the 
**[Asset Manager][1]**. This data asset contains a few properties but, most importantly, allows you to assign all 
Fragments that will contribute to the item's data and logic.

The following table provides details about the properties available in the **Item Definition**:

| Property               | Description                                                                                       |
|------------------------|---------------------------------------------------------------------------------------------------|
| Gameplay Tags          | All Gameplay Tags that describe this item. Fragments may add tags to this Gameplay Tag Container. |
| Default Instance Class | Default class used when the item is managed by an Inventory Manager.                              |
| Fragments              | All fragments adding data and logic to the item.                                                  |

One way items can be added to the Inventory Manager is by adding an Item Definition. Once the definition is fully processed, 
an **Item Instance** is created.

Item instances are very light and essentially serve as platforms for their **Fragments** to run. Item instances are 
identified by their unique identifier, `ItemId`, and provide access to their definition, fragments, and the current Inventory Manager they are assigned to.

The following table contains a non-exhaustive list of useful functions that an **Item Instance** can provide:

| Function                  | Description                                                             |
|---------------------------|-------------------------------------------------------------------------|
| `GetItemId`               | Provides the unique `FGuid` identifier for the item.                    |
| `GetData`                 | Provides the Item Definition that generated the item.                   |
| `GetInventoryManager`     | Provides the Inventory Manager that owns the item.                      |
| `GetOwnedGameplayTags`    | Provides all Gameplay Tags that represent the item.                     |
| `GetSupportedOperations`  | Provides all Gameplay Tags of supported operations.                     |
| `GetAbilitySystem`        | Provides the Ability System Component related to the Inventory Manager. |
| `FindFragmentByClass`     | Finds a fragment by its class.                                          |
| `FindFragmentByInterface` | Finds a fragment by its interface.                                      |

### Item Subclasses
<secondary-label ref="advanced"/>

The primary way to define items is via **aggregation**, adding and configuring fragments for an item. However, in certain 
situations, you might need to use **inheritance** and create your own Item subclass.

In that case, you can create subclasses or blueprints based on `NinjaInventoryItem`, and then set them to a specific 
item's definition, or globally in the project's settings, under the Ninja Inventory category.

## Item Fragments

Item Fragments are small, reusable pieces of logic focused on a specific aspect of an item.

The base fragment class is `NinjaInventoryItemFragment`, a valid implementation of `OperableItemInterface`. All concrete 
fragment classes available in the system extend from it.

By itself, an item doesn't have any logic (unless extended by a subclass). It is only meant as a platform for fragments 
to execute their tasks and persist their memories. Fragments are responsible for the actual data and **heavy-lifting**.

> The architectural standard in which external objects (fragments) modify the object they are related to (item) 
> externally is known as **Inversion of Control**, or **IoC**.

A fragment has these objectives:

1. Expose configuration parameters that define how their logic executes.
2. Execute logic on an item to accomplish tasks within a fragment's domain.
3. Expose operations accessible externally through the Inventory Manager.

Fragments are related to the **Item Definition**. They are instantiated by that Data Asset and reused by any Item 
Instance generated from that definition. This means they should be **stateless** as they are not related to any item in 
particular, which is also why their methods often receive an item as a parameter.

> An item can have **one instance** of each fragment type!
{style="note"}

To persist information related to a specific item, fragments use a **Fragment Memory**.

### Fragment Memories

Fragment memories are structures defined by each fragment, allowing them to persist their data in an item.

All memories are based on the `InventoryFragmentMemory` structure. This hierarchy is important because the system 
extensively uses the [`TInstancedStruct`][2] type to read polymorphic fragment memories.

> Since structures created in the editor cannot have a type hierarchy, new fragment memories must be created in C++.
{style="note"}

Items are responsible for storing and replicating their fragment memories. They also cache their memories in an internal 
structure, allowing access in linear `O(1)` time complexity. This also hints at the fact that items can only have **one instance** of each fragment.

Here are some examples of data stored in fragment memories:

- The **stack** set in an item instance.
- The **container** and **position** where an item is stored.
- The **durability** of an item.
- The **damage** that an item applies, picked randomly from a given range.
- The **armor** that an item provides, picked randomly from a given range.

### Fragment Operations

Fragment operations are functionalities exposed by fragments, triggered by event-like calls.

Each operation requires a **payload** represented by a structure based on the `InventoryFragmentPayload`. Once again, 
the hierarchy is important because the system uses [`TInstancedStruct`][2] for polymorphism.

> Since structures created in the editor cannot have a type hierarchy, new fragment payloads must be created in C++.
{style="note"}

Fragments expose their operations via Gameplay Tags added to their `OperationTags` container. All Gameplay Tags related 
to operations have `Inventory.Item.Fragment.Operation` as the root Gameplay Tag.

Operations are usually triggered via the **Inventory Manager** and are useful when the calling code **does not know** 
about the fragments available to an item. However, if you are familiar with the Fragment API, you can access its functionality directly.

> Fragment operations are authoritative! If you are not executing them via the Inventory Manager, make sure to handle authoritative calls.
{style="note"}

Here are some examples of operations supported by fragments:

- **Consume** an item, provided by the Consume fragment.
- **Move** or **Swap** items, provided by the Container fragment.
- **Activate** or **Deactivate** equipment, provided by the Equipment fragment.
- **Combine** or **Split** stacks, provided by the Stack fragment.

All operations provided by fragments have their **factory methods** available to Blueprints and C++ via the Inventory 
Gameplay function library. More details are available in each fragment's reference page.

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine">Asset Manager Documentation</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Plugins/StructUtils/TInstancedStruct/InstancedStruct">Instanced Struct Documentation</a>
    </category>
</seealso>

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Plugins/StructUtils/TInstancedStruct/InstancedStruct

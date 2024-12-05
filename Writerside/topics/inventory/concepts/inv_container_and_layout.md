# Containers and Layout
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Containers can represent a <b>region</b>, an <b>equipment slot</b>, or an actual <b>container</b>.</li>
        <li>Containers are defined by a <b>Container Definition</b> (<code>NinjaInventoryContainerDataAsset</code>) and represented by a <b>Container Instance</b> (<code>NinjaInventoryContainer</code>).</li>
        <li>Containers must have their definition data asset added to the <b>Asset Manager</b>.</li>
        <li>Layouts are defined by <code>NinjaInventoryLayoutDataAsset</code> and determine all containers initially available to an Inventory Manager, including the <b>default container</b>.</li>
        <li>Layouts can be provided to an Inventory Manager via the <b>default property value</b> or via the <code>InventoryManagerProviderInterface</code>.</li>
    </ul>
</tldr>

Containers and Layouts define the structure used by the inventory to store its items.

## Inventory Containers

There are many names and usages that can exemplify a container: a **Region** for items, a **Slot** that can hold equipment 
pieces, actual **Containers** representing items inside the inventory, and probably others.

Containers are defined by the Data Asset `NinjaInventoryContainerDataAsset`. You can assign Gameplay Tags to establish 
traits that will fine-tune the container's purpose, determine the specific Container Class instantiated when the container is added to an Inventory, available slots, etc.

The `NinjaInventoryContainerDataAsset` is a Primary Data Asset and, as such, it must be registered with the **[Asset Manager][1]**. 
This can be done in the Engine Settings or directly added to the `DefaultGame.ini` file.

All properties available to containers are defined in the following table:

| Property                 | Description                                                                                           |
|--------------------------|-------------------------------------------------------------------------------------------------------|
| Display Name             | The name for the container. Supports localization from [String Tables][2].                            |
| Gameplay Tags            | Gameplay Tags defining additional traits for this container.                                          |
| Container Class          | Class used to create Container Instances in an Inventory Manager.                                     |
| Priority                 | Priority applied when matched against other Containers. The lower the value, the higher the priority. |
| Slots                    | Maximum number of item slots available to this container.                                             |
| Slots Attribute          | Overrides the Slots property using a Gameplay Attribute instead.                                      |
| Item Compatibility Query | Query applied to all items before adding them, to ensure they are compatible.                         |

> The Attribute Set provided by the Inventory System, `NinjaInventoryAttributeSet`, contains an attribute for Backpack Slots.
>
> This attribute is available for convenience, but if you don't need it, you can safely ignore it.
{style="note"}

Once a container is assigned to an Inventory through its Data Asset, it is represented by the `NinjaInventoryContainer` 
class, or a subclass defined in the data asset.

### Default Containers

Default containers are important as they assist the Inventory Manager in selecting containers for new items when needed. 
They are usually identified by the `Inventory.Container.Default` Gameplay Tag, present in their `Gameplay Tags` property.

The [Inventory Layout](#inventory-layouts) must then define a Gameplay Tag Query to identify such items, allowing 
flexibility for more complex setups.

### Primary and Secondary Containers
<secondary-label ref="wip"/>

Items stored in the inventory might consume more than one container. A classic example is an item equipped in both main 
and off-hands, each hand being represented by its own container.

An item can only ever have one primary container, but it can have multiple secondary ones. The relationship between 
primary and secondary containers is defined in the Container Definition.

### Container and Position Assignment

Items added to the inventory can define their preferred container and position. However, these requests might not be viable, 
thus requiring a new container and position. This is also the case for items added to the inventory without deliberately 
defining these values.

For those situations, the Inventory Manager will attempt to determine the most appropriate container and position for 
the new item. This is based on the **Item Compatibility** for each container, ordered by their **Priority**.

If an automatic assignment is not possible, other aspects of the item might be triggered, such as the **Drop Fragment**, 
which, if present, will drop the item as a **[Pickup Actor](inv_pickup_fragment.md)**.

## Inventory Layouts

An Inventory Layout provides the initial containers available to the inventory and defines the default one.

Inventory Layouts are created from `NinjaInventoryLayoutDataAsset`. They contain a Gameplay Tag Query used to identify 
the default container, usually tagged with `Inventory.Container.Default`, and all containers added to an Inventory Manager by default.

> You should always have a valid query that identifies at least one default container. If you have more than one default 
> container, the best pick would be the one with the highest priority.
{style="note"}

You can assign a Layout to an Inventory Manager in a few different ways, as described in the following table:

| Assignment        | Description                                                                    |
|-------------------|--------------------------------------------------------------------------------|
| Property          | Directly to an Inventory Manager via its `InventoryLayout` property.           |
| Interface, Owner  | Via the `InventoryManagerProviderInterface` in the Inventory Manager's owner.  |
| Interface, Avatar | Via the `InventoryManagerProviderInterface` in the Inventory Manager's avatar. |

> The strategies above are ordered from lowest to highest priority, meaning that every time a new avatar is initialized in an Inventory Manager, it can set its Inventory Layout over all other options.

<seealso>
   <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine">Asset Manager Documentation</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/using-string-tables-for-text-in-unreal-engine">String Tables Documentation</a>
    </category>
</seealso>

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/using-string-tables-for-text-in-unreal-engine


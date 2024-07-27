# Containers and Layout
<primary-label ref="inventory"/>

<tldr>
    <b>Summary: Containers and Layout</b>
    <ul>
        <li>Containers can represent a <b>Region</b>, an <b>Equipment Slot</b> or an actual <b>Container</b>.</li>
        <li>Containers are defined by a Container Definition and represented by a Container Instance.</li>
        <li>Container Definitions are created from the <code>UNinjaInventoryContainerDataAsset</code>.</li>
        <li>Containers are represented using the base class <code>UNinjaInventoryContainer</code>.</li>
        <li>Layouts determine all containers initially available to an Inventory Manager.</li>
        <li>Layouts also specify which containers are considered the default ones in the Inventory.</li>
        <li>Layouts are immutable and can be provided directly to the Inventory or via interface.</li>
    </ul>
</tldr>

Containers and Layouts are the foundation of an Inventory. They define all available parts of the inventory that may
contain items and specific traits about these parts.

## Inventory Containers

There are many names that can be used to exemplify a container, such as a **Region** for items, a **Slot** that can hold 
equipment pieces, actual **Containers** representing items inside the inventory and so on.

Containers are defined by the Primary Data Asset `UNinjaInventoryContainerDataAsset`. You can assign Gameplay Tags to 
establish traits that will fine-tune the container's purpose, determine the specific Container Class instantiated when
the container is added to an Inventory, among other details that are listed in the following table.

| Property                 | Description                                                                   |
|--------------------------|-------------------------------------------------------------------------------|
| Display Name             | Localized name for this container.                                            |
| Gameplay Tags            | Gameplay Tags defining additional traits to this container.                   |
| Container Class          | Class used to create instances of Containers.                                 |
| Priority                 | Priority applied when matched against other Container.                        |
| Slots                    | Maximum amount of item slots available to this container.                     |
| Slots Attribute          | Overrides the Slots property, using a Gameplay Attribute instead.             |
| Item Compatibility Query | Query applied to all items before adding them, to ensure they are compatible. |

> The Attribute Set provided by the Inventory System contains an attribute for Backpack Slots that you can use or 
> safely ignore.
{style="note"}

Once a container is assigned to an Inventory, through its Data Asset, it's represented by the `UNinjaInventoryContainer`.
You can provide your own class, if you need to implement specific functionality. Classes used to represent Containers
are set to their Data Assets.

## Inventory Layouts

Containers are grouped and assigned to an Inventory Manager via an Inventory Layout, which is a Data Asset that can be 
created from `UNinjaInventoryLayoutDataAsset`. There are a few relevant pieces of information that can be defined in 
this data asset.

First, and most importantly, you can assign all containers that will be initially available to an Inventory Manager.
Items can only be added to containers available to the Manager. You can eventually add and remove containers from the
Inventory Manager, but if you are planning to have default items, then you must assign all default containers.

In the Layout, you must also define your **default container**. By default, any Container tagged with `Inventory.Container.Default`
will be considered the default container. It's highly recommended that you only keep one default container in an 
inventory at all times.

You can assign a Layout to an Inventory Manager using a few different ways, which are described in the following table:

| Assignment        | Description                                                                     |
|-------------------|---------------------------------------------------------------------------------|
| Property          | Directly to an Inventory Manager, via it's `InventoryLayout` property.          |
| Interface, Owner  | Via the `IInventoryManagerProviderInterface` in the Inventory Manager's owner.  |
| Interface, Avatar | Via the `IInventoryManagerProviderInterface` in the Inventory Manager's avatar. |

> The strategies above are ordered from lowest to highest, meaning that everytime a new Avatar is initialized in an 
> Inventory Manager, it can set its Inventory Layout over all other options.
{style="note"}


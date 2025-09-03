# Equipment Management
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Equipment Management</b></p>
    <br/>
    <ul>
        <li>The <b>Equipment Manager</b> manages <b>equipment instances</b>, which are created for items with a <b>physical presence</b> in the game world.</li>
        <li>This component works in conjunction with Containers using an <b>Equipment Layout</b>, and items with an <b>Equipment Fragment</b>.</li>
        <li>During its initialization, it will require an <b>Inventory Manager</b> provided by its owner.</li>
    </ul>
</tldr>

The `NinjaEquipmentManagerComponent` is the core of the Equipment layer in the Inventory System. This is an optional  
component that must be added to **Inventory Avatars** that will receive **physical representations** of items added to  
their inventories.

A **physical representation** is an **actor** or **mesh asset** that is shown in the game world. This is usually  
relevant for **players**, and potentially for certain **NPCs** or **enemies**, but it is most likely irrelevant for  
**chests**, **vendors**, or other non-character actors.

## Inventory Integration
The Equipment Manager waits for the inventory to **initialize**, so it can bind to relevant events. The Inventory and  
Equipment Manager will usually coexist as follows:

| Component          | Location                                                                                                                |
|--------------------|-------------------------------------------------------------------------------------------------------------------------|
| `InventoryManager` | Added to the **Inventory Avatar** (e.g., Player Character) or to the **Player State**.                                  |
| `EquipmentManager` | **Always** added to the **Inventory Avatar**. Will search for the Inventory in the Avatar first, then the Player State. |

> **Initialization and Binding State**
>
> You can check if the Equipment Manager was successfully bound to an Inventory Manager using the `IsBoundToInventoryManager` function.
>
> Alternatively, you can subscribe to the `OnBoundToInventory` event, which will broadcast once binding completes.
{style="note"}

## Item Eligibility
The Equipment Manager watches for items being **added** or **removed** from the inventory. If the item meets the  
equipment eligibility criteria, it will be processed automatically.

To be eligible, the item must:

1. Have an **[Equipment Fragment](inv_fragment_equipment.md)**.
2. Be placed inside an **[Equipment Container](inv_layout_equipment.md)**.

## Equipment Management
Most equipment logic is handled automatically through inventory events and fragment-driven state transitions.  
However, the Equipment Manager provides functions for querying and interacting with equipment programmatically.

| Function                        | Description                                                                 |
|---------------------------------|-----------------------------------------------------------------------------|
| `IsEquipmentActiveForItem`      | Checks whether there is an active equipment instance for the given item.    |
| `CountActiveEquipmentInstances` | Returns the number of currently active equipment instances.                 |
| `GetEquipmentForItem`           | Returns all equipment instances created for a given item.                   |
| `GetEquipmentByQuery`           | Returns all equipment instances that match a `GameplayTagQuery`.            |
| `GetFirstEquipmentByQuery`      | Returns the first equipment instance matching a `GameplayTagQuery`.         |
| `GetActiveEquipmentItems`       | Returns all inventory items that currently have active equipment instances. |

## Attachment Parent Finders
Attachment Parent Finders are **strategy objects** that determine how to resolve the parent component  
used for attaching an equipment actor or mesh.

They are typically used by the **Equipment Fragment** and can be overridden per Equipment State.

The system includes several built-in finders:

| Finder                             | Description                                                                     |
|------------------------------------|---------------------------------------------------------------------------------|
| `UAttachFinder_CharacterMesh`      | Always returns the avatar’s main mesh (e.g., `GetMesh()` on characters).        |
| `UAttachFinder_ComponentTag`       | Searches the avatar for a component with a matching `ComponentTag`.             |
| `UAttachFinder_InventoryInterface` | Calls `GetInventoryMesh()` from the `EquipmentSystemInterface`, if implemented. |

### Custom Finders
You can create your own finder by subclassing `NinjaEquipmentAttachParentFinder` and overriding the `FindAttachParent` method.
This allows you to define custom rules, such as attachment based on item tags, actor states, or animation conditions.

> **Best Practice**
> 
> Keep your Attachment Finders **stateless** and **fast**, as they may be called during animation events or frequent updates.
{style="note"}
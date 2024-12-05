# Equipment Manager
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>This component manages the <b>equipment lifecycle</b>.</li>
        <li>It should always be added to the <b>pawn</b> used as the inventory's avatar.</li>
        <li>Provides multiple <b>query methods</b> for Containers and Items along with functions to perform <b>operations</b> on them.</li>
        <li>Pawns with an Equipment Manager must also implement <code>EquipmentManagerProviderInterface</code>.</li>
        <li>The Equipment Manager needs to access an <b>Inventory Manager</b>.</li>
    </ul>
</tldr>

The **Equipment Manager** works in conjunction with the **[Inventory Manager](inv_inventory_manager.md)** to represent 
items in the world.

## Equipment Management

When an item is added to an **Equipment Slot**, its **[Equipment Fragment](inv_equipment_fragment.md)** will communicate
with the Equipment Manager to initialize or synchronize an **[Equipment Instance](inv_equipment.md)**.

Once ready, the Equipment Instance will use multiple functionalities from the Equipment Manager to update its state:

1. Add or remove **Skeletal or Static Meshes** from certain Equipment Slots.
2. Hide or show **Equipment Slots**.
3. Add or remove **Gameplay Attributes**, **Effects** and **Abilities**.
4. Add or remove **Containers** granted by equipped items.

## Asset Manager

An important responsibility of the Equipment Manager, that is **transparent** to the end user is its integration with 
the **Asset Manager**.

All assets set in the equipment's **state** are **soft references**, meaning they are not automatically load to memory.
When a state activates, its assets are **asynchronously** loaded on demand, with **high priority**. Once they are loaded,
they will be appropriately used.

The asset's **handle** will be kept until the state becomes inactive. When that happens, the handle is reset, allowing
the assets to be **unloaded**.

Because of this, you might see some small delays when an Equipment Instance is being created for the first time. A 
common way to circumvent that is having important or recurrent meshes loaded in the map, in a hidden area.

## Configuration

The following properties are used to adjust the Equipment Manager's operation:

| Property                           | Description                                                                                                         |
|------------------------------------|---------------------------------------------------------------------------------------------------------------------|
| `AllEquipmentContainersQuery`      | A Gameplay Tag Query that will obtain all containers that can store equipment, **including** cosmetics.             |
| `RelevantEquipmentContainersQuery` | A Gameplay Tag Query that will obtain all containers that can store equipment, **excluding** cosmetics.             |
| `SlotSocketMapping`                | Maps Equipment Slots to Sockets, which is necessary for slots that are not represented by Mesh Components (actors). |
| `InventoryManagerPollInterval`     | How often the Equipment Manager will poll for an Inventory Manager, during its initialization.                      |
| `InventoryManagerMaxWait`          | Maximum amount of time to wait for an Inventory Manager to initialize.                                              |
| `DefaultSlotData`                  | Configures default meshes for all equipment slots, that will be used when no equipment is currently assigned.       |
| `DefaultStateTag`                  | Default State Tag for new equipments, when no alternative was found in the container or equipment itself.           |

### Equipment Queries

Both **Equipment Queries** used by the Equipment Manager are used by functions that will look for Equipment Slots in
the **Inventory Layout**. It's important to different **cosmetic** and **non-cosmetic** slots, especially while 
calculating the current **Equipment Level**.

Check the [](inv_equipment.md#equipment-slots) page for more information.

### Slot Socket Mapping

Equipment Slots are usually represented by **Mesh Components** with a specific **Slot Tag**. However, this is not the
case for **Actors** that are added by the equipment.

Actors are only attached to a **socket**, yet the system has to be able to find them by Slot Tags, which is why this
configuration is important.

Check the [](inv_equipment.md#equipment-slots) page for more information.

### Initialization

The Equipment Manager will **asynchronously** poll its owner, while waiting for the **Inventory Manager** to initialize.
You can define the poll interval and the wait limit for this operation.

### Default Slots

This configures default meshes for **Equipment Slots** without an item. This is useful to determine meshes that will
represent the base character, such as a _shirt_ or _naked torso_.

They are added and removed based on the presence of an item, or deliberately, depending on the **state configuration**.

Check the [](inv_equipment.md#equipment-slots) page for more information.

## Replication

Different from the Inventory Manager, the Equipment Manager replicates to **all clients**. This is necessary since all
equipment representations must occur in all versions: _authoritative_, _autonomous_ and _simulated_.

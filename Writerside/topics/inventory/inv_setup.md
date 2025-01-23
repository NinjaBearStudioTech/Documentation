# Setup
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Install the Ninja Inventory plugin using the Epic Games Launcher.</li>
        <li>Open your project and enable the plugin: <code>Edit</code> &rightarrow; <code>Plugins</code>, search for <i>inventory</i>, and tick the checkbox for <b>Ninja Inventory</b>. Restart the engine.</li>
        <li>Add <code>NinjaInventoryManagerComponent</code> to your <b>Character</b> or <b>Player State</b>. The actor must also implement <code>AbilitySystemInterface</code>.</li>
        <li>Add <code>InventoryManagerProviderInterface</code> to the same object that has the Inventory Manager. Implement the <code>GetInventoryManager</code> function.</li>
        <li>Add <code>NinjaEquipmentManagerComponent</code> to your <b>Character</b>, regardless of where the Inventory Manager was placed.</li>
        <li>Add <code>EquipmentManagerProviderInterface</code> to your character. Implement the <code>GetEquipmentManager</code> function.</li>
    </ul>
</tldr>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Inventory** plugin.

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be 
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type 
_inventory_ and the **Ninja Inventory** plugin should appear. Tick the checkbox and restart the engine.

## C++ Libraries

If you plan to work with C++ and use classes from the Inventory System, ensure you add the following modules to your 
`Build.cs` file:

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#">
        PublicDependencyModuleNames.AddRange(new []
        {
            "CommonUI",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "InputCore",
            "ModelViewViewModel",
            "NinjaInventory",
            "NinjaInventoryCore",
            "NinjaInventoryEquipment",
            "NinjaInventoryGameplay",
            "NinjaInventoryUI",
            "StructUtils",
            "UMG"
        });
        </code-block>
    </tab>
</tabs>

## Asset Manager

The Inventory System uses **Primary Data Assets** and **soft references** to load and unload assets that should only be 
available when certain items or equipment are obtained.

You can register these assets in the following ways:

- In the Editor, configure the **Asset Manager**: `Edit` > `Project Settings` > `Asset Manager`.
- If you use a **Modular Game Feature** to add your Inventory, you can register these assets in your Feature configuration.

| Asset Name               | Base Class                         | Description                                                 |
|--------------------------|------------------------------------|-------------------------------------------------------------|
| `InventoryContainerData` | `NinjaInventoryContainerDataAsset` | Defines the data structure for **Inventory Containers**.    |
| `InventoryItemData`      | `NinjaInventoryItemDataAsset`      | Defines the data structure for **Items** and **Fragments**. |
| `EquipmentData`          | `NinjaEquipmentDataAsset`          | Defines the data structure for **Equipment**.               |
| `EquipmentSlotData`      | `NinjaEquipmentSlotDataAsset`      | Default Skeletal Meshes for unused **Equipment Slots**.     |


Once configured, your entries in the Asset Manager should look like this:

![Inventory Data Assets Setup](inv_setup_asset_manager.png "Inventory Data Assets Setup")

> **Asset Directory**
>
> If you have a specific **directory** for your Data Assets, like in the example above, make sure to set that in the
> Primary Asset type registry as well.

## Ability System

The **Ability System Component** is a prerequisite for the system to operate. Ensure that actors using the Inventory 
Manager Component also have an **Ability System Component** and implement the `AbilitySystemInterface`.

If you are using the [Inventory Attribute Set](inv_attributes.md), add it along with the appropriate initialization data. 
Also, review the [Abilities](inv_abilities.md) to learn more about abilities that should be granted by default.

## Inventory Manager

The **[](inv_inventory_manager.md)** is the primary component that must be added to any actor with an inventory.

The Inventory Manager can be added to a **Player State** or **Pawn**. Both are equally viable and the decisive factor 
should be your inventory's **persistence**. The Player State is usually a good option for inventories that should be
kept over _respawns_ or _level travel_.

During its initialization, the Inventory Manager will wait for the Ability System Component to **initialize** and obtain 
an avatar that **is not** a Player State.

> The Inventory Manager always waits for the Ability System Component to replicate before it can fully initialize.
>
> If this step results in a timeout, you will find a **warning** in your log under the **LogNinjaInventory** category.
> ```
> [NinjaInventoryLog] UNinjaInventoryAction_WaitForAbilitySystem: Waited 3s for the required object. Giving up...
> ```

### Inventory Provider Interface

After adding the Inventory Manager to the appropriate actor, the next step is to add the `InventoryManagerProviderInterface` 
and implement the `GetInventoryManager` function to return the component.

## Equipment Manager

The [**Equipment Manager**](inv_equipment_manager.md) is not a mandatory component but will likely be added to any actors 
using items with a **physical presence** in the game world.

Similar to the Inventory Manager, the Equipment Manager also has a prerequisite for its initialization, requiring the 
**Inventory Manager** to be **replicated** and **initialized**.

> If this step results in a timeout, you will find a **warning** in your log under the **LogNinjaInventory** category.
> ```
> [NinjaInventoryLog] UNinjaInventoryAction_WaitForInventoryManager: Waited 3s for the required object. Giving up...
> ```

The Equipment Manager must be added to the actual **Pawn**, regardless of where the Inventory Manager was added.

### Equipment Provider Interface

After adding the Equipment Manager to the appropriate pawn, the next step is to add the `EquipmentManagerProviderInterface` 
and implement the `GetEquipmentManager` function to return the component.

<seealso style="cards">
   <category ref="related">
        <a href="inv_troubleshooting.md" summary="Debugging the inventory and accessing the logs.">Debugger and Logs</a>
        <a href="inv_create_item.md" summary="How to create your first container and add it to the inventory.">How-to: Create a Container</a>        
    </category>
   <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine" summary="Loading and unloading assets with the Asset Manager.">Asset Manager</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/game-features-and-modular-gameplay-in-unreal-engine" summary="Build standalone features that you can quickly activate or deactivate.">Game Features</a>
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine" summary="High-level view of the Gameplay Ability System.">Gameplay Ability System</a>
    </category>
</seealso>
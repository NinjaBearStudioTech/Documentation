# Setup
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>Install the Ninja Inventory plugin to your engine, using the Epic Games Launcher.</li>
        <li>Open your project and enable the plugin: <code>Edit</code> &rightarrow; <code>Plugins</code>, search for <i>inventory</i> and tick the checkbox for <b>Ninja Inventory</b>. Restart the engine.</li>
        <li>Add the <code>NinjaInventoryManagerComponent</code> to your <b>Character</b> or <b>Player State</b>. The actor must also have the <code>AbilitySystemInterface</code>.</li>
        <li>Add the <code>InventoryManagerProviderInterface</code> to the same object that has the Inventory Manager. Implement the <code>GetInventoryManager</code> function.</li>
        <li>Add the <code>NinjaEquipmentManagerComponent</code> to your <b>Character</b>, regardless of where the Inventory Manager was placed.</li>
        <li>Add the <code>EquipmentManagerProviderInterface</code> to your character. Implement the <code>GetEquipmentManager</code> function.</li>
    </ul>
</tldr>

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugins** it can be 
installed to any compatible engine versions.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type 
_inventory_ and the **Ninja Inventory** plugin should come up. Tick the checkbox and restarted the engine.

## C++ Libraries

> If your project only uses Blueprints, you can skip this step.

If you are planning on working on C++ and using classes from the Inventory System, then make sure to add the following
modules to your `Build.cs` file:

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

The following assets must be registered with the **Asset Manager**, in the Project Settings page, or in the `DefaultGame.ini`
file.

| Asset                    | Description                                                    |
|--------------------------|----------------------------------------------------------------|
| `InventoryContainerData` | Contains information about Inventory Containers.               |
| `InventoryItemData`      | Contains information about Items and its Fragments.            |
| `EquipmentData`          | Contains information about Equipment, its States and Actors.   |
| `EquipmentSlotData`      | Contains information about default meshes for Equipment Slots. |

## Ability System

The **Ability System Component** is a pre-requisite for the system to operate. Make sure that actors using the Inventory
Manager Component also have an **Ability System Component** and implement the `AbilitySystemInterface`.

If you are using the [Inventory Attribute Set](inv_attributes.md), then go ahead and add it, along with the appropriate
initialization data. Also, make sure to check the [Abilities](inv_abilities.md) to learn more about abilities that should
be granted by default.

## Inventory Manager

The [**Inventory Manager**](inv_inventory_manager.md) is the primary component that must be added to any actor with an
inventory.

The Inventory Manager can be added to a **Player State** or **Pawn**. The former being the common location for **Players**
and the latter for all other scenarios.

During its initialization, the Inventory Manager will wait for the Ability System Component to **initialize** and obtain
an avatar that **is not** a Player State.

> The Inventory Manager always waits for the Ability System Component to replicate, before it can fully initialize.
> 
> If this step results in a timeout, you will find a **warning** in your log, under the **LogNinjaInventory** category.
> ```
> [NinjaInventoryLog] UNinjaInventoryAction_WaitForAbilitySystem: Waited 3s for the required object. Giving up...
> ```

### Inventory Provider Interface

After adding the Inventory Manager to the appropriate actor, the next step is adding the `InventoryManagerProviderInterface`
and implementing the `GetInventoryManager`, returning the component.

## Equipment Manager

The [**Equipment Manager**](inv_equipment_manager.md) is not a mandatory component, but will most likely be added to any
actors that are using items with a **physical presence** in the game world.

Similar to the Inventory Manager, the Equipment Manager also has a pre-requisite for its initialization, but this time
it requires the **Inventory Manager** to be **replicated** and **initialized**.

> If this step results in a timeout, you will find a **warning** in your log, under the **LogNinjaInventory** category.
> ```
> [NinjaInventoryLog] UNinjaInventoryAction_WaitForInventoryManager: Waited 3s for the required object. Giving up...
> ```

The Equipment Manager must be added to the actual **Pawn**, regardless of where the Inventory Manager was added.

### Equipment Provider Interface

After adding the Equipment Manager to the appropriate pawn, the next step is adding the `EquipmentManagerProviderInterface`
and implementing the `GetEquipmentManager`, returning the component.

<seealso style="cards">
   <category ref="related">
        <a href="inv_configuration.md" summary = "Configuration settings that affect the inventory behavior.">Configuration</a>
        <a href="inv_debugger_and_logs.md" summary = "Debugging the inventory and accessing the logs.">Debugger and Logs</a>
        <a href="inv_create_item.md" summary = "How to create your first container and add it to the inventory.">How-to: Create a Container</a>        
        <a href="inv_create_item.md" summary = "How to create your first item and add it to the inventory.">How-to: Create an Item</a>
    </category>
   <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine" summary = "Loading and unloading assets with the Asset Manager.">Asset Manager</a>
        <a href="inv_debugger_and_logs.md" summary = "https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine.">Gameplay Ability System</a>
    </category>
</seealso>

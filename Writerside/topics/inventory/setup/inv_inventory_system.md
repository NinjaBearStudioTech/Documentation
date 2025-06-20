# Inventory System
<primary-label ref="inventory"/>

<tldr>
    <p><b>Summary: Inventory System</b></p>
    <br/>
    <ul>
        <li>The <b>Inventory Manager</b> is responsible for managing <b>Containers</b> and <b>Items</b>.</li>
        <li>The Inventory Manager can be added to an <b>Actor</b> or <b>Player State</b>.</li>
        <li>The Inventory Manager can optionally work in conjunction with an <b>Ability System Component</b>.</li>
        <li>You can optionally implement <code>InventorySystemInterface</code> for faster access to the Inventory Manager.</li>
    </ul>
</tldr>

The Inventory System manages **Containers** and **Items**, providing a flexible way to handle inventory logic across different actors.  
It should be added to an **Actor** or **Player State**, depending on your design goals.

- **Actor**: Inventories with limited persistency, such as those for _chests_, _vendors_, or _enemies_, should have the Inventory Manager added directly to the actor.
- **Player State**: Players that require an inventory to persist over multiple levels should have the Inventory Manager added to the Player State.

## Inventory Manager Component
The Inventory Manager Component is the main component in the system and should be added to any actor or player state that needs access to an inventory.

<procedure title="Add the Inventory Manager Component" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Base Player State</b>, add the <b>Inventory Manager Component</b>.</p>
        <p>The component can be added using either Blueprint or C++:</p>
        <tabs group="sample">
            <tab title="Blueprint" group-key="bp">
                <img src="inv_setup_inventory_manager.png" alt="Add the Inventory Manager Component" thumbnail="true" border-effect="line"/>
            </tab>
            <tab title="C++" group-key="cpp">
                <p><b>Header</b></p>
                <code-block lang="c++" src="inv_setup_inventory_manager_component.h"/>
                <p><b>Implementation</b></p>
                <code-block lang="c++" src="inv_setup_inventory_manager_component.cpp"/>
            </tab>
        </tabs>
    </step>
</procedure>

The Inventory Manager provides important **properties** that can be used to adjust its behavior.

| Property                                 | Description                                                                                                                                                                                       |
|------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Default Container Query                  | A query used to identify the default container in the inventory.                                                                                                                                  |
| Initial Containers                       | All containers added to the inventory by default.                                                                                                                                                 |
| Initial Items                            | All items added to the inventory by default.                                                                                                                                                      |
| Item Processor Class                     | A dedicated class containing all the logic that determines which containers should receive new items.                                                                                             |
| Items Per Tick                           | How many items can be processed per tick. This keeps the item processing from consuming too many resources per tick.                                                                              |
| Should Fail on Missing Ability Component | If true, initialization will fail if an Ability System Component is not found.                                                                                                                    |
| Ability System Poll Interval             | How frequently (in seconds) the Inventory Manager checks for an Ability System Component during initialization.                                                                                   |
| Ability System Max Wait                  | Maximum time (in seconds) to wait for the ASC before giving up and potentially failing the initialization.                                                                                        |
| Automatically Load From Disk             | Whether the Inventory Manager will attempt to load inventory data from a save slot automatically during initialization.                                                                           |
| Save Game User Index                     | Index for the Save User file. You can create dynamic behaviors by extending `GetUserIndexForSaveGameSlot`.                                                                                        |
| Save Game Slot Name                      | Name of the Save Slot.                                                                                                                                                                            |

### Ability Component Binding
The Inventory Manager Component will automatically bind to an Ability System Component if the function `ShouldBindToAbilityComponent`
returns `true`.

By default, this will happen if the component owner implements `AbilitySystemInterface` or, in case of a **Player State**
owner that does not implement the interface, having its **Pawn** implementing the interface.

> **Modify Binding Behavior**
>
> You can alter, force the binding or completely disable it by overwriting `ShouldBindToAbilityComponent`, either in
> Blueprints or C++. 
{style=note}

### Initialization States
While initializing, the Inventory will go through several states, each representing a distinct step in the process. The  
current state can be viewed through the [**Gameplay Debugger**](inv_gameplay_debugger.md).

| State                           | Description                                                                      |
|---------------------------------|----------------------------------------------------------------------------------|
| NotInitialized                  | Initialization has not started yet.                                              |
| WaitingForAbilitySystem         | Inventory is waiting for the Ability System Component (ASC) to become available. |
| BoundToAbilitySystem            | Inventory is connected to the ASC and will begin initializing items.             |
| InitializingFromSaveGame        | Inventory is loading data from a saved game file.                                |
| InitializedFromSaveGame         | Inventory successfully initialized using saved game data.                        |
| InitializingFromDefaultSettings | Inventory is initializing from default containers and items.                     |
| InitializedFromDefaultSettings  | Inventory successfully initialized using default settings.                       |
| InitializingItems               | Items and fragments are being fully initialized.                                 |
| Initialized                     | Inventory has completed initialization and is ready to use.                      |
| FailedToInitialize              | An error occurred and the inventory failed to initialize.                        |

You can query the current initialization state using the following functions from the Inventory Manager:

| Function                          | Description                                                          |
|-----------------------------------|----------------------------------------------------------------------|
| `GetInventoryInitializationState` | Provides the current initialization state.                           |
| `IsInventoryInitialized`          | Utility function to confirm that the inventory has been initialized. |
| `WasLoadedFromSaveSlot`           | Informs if the inventory was loaded from a **save slot**.            |

## Inventory System Interface
The recommended way to retrieve the Inventory Manager is by using the `GetInventoryManager` function in the `NinjaInventoryFunctionLibrary`.

This function can retrieve the Inventory Manager from Actors, Controllers, and Player States, by searching in the most 
likely locations.

To avoid repeated component lookups, you can optionally implement the `InventorySystemInterface` on the actor or player 
state that owns the Inventory Manager.

<procedure title="Add the Inventory System Interface" collapsible="true" default-state="expanded">
    <step>In your <b>inventory owner</b> (Actor or Player State), add the <code>InventorySystemInterface</code>.</step>
    <step>Implement the <code>GetInventoryManager</code> function so it returns the <b>Inventory Manager Component</b>.</step>
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="inv_setup_inventory_interface.png" alt="Add the Inventory System Interface" width="800" thumbnail="true" border-effect="line"/>
        </tab>
        <tab title="C++" group-key="cpp">
            <p><b>Header</b></p>
            <code-block lang="c++" src="inv_setup_inventory_system_interface.h"/>
            <p><b>Implementation</b></p>
            <code-block lang="c++" src="inv_setup_inventory_system_interface.cpp"/>
        </tab>
    </tabs>
</procedure>

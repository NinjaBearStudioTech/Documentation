# Setting Up Ninja Combat
<primary-label ref="combat"/>

This page summarizes the setup required for **Ninja Combat** after the plugin has been installed and enabled.

For the general installation process, see the [**Installing Plugins**](installing_plugins.md) guide.

## Prerequisites

| Requirement             | Notes                                                                                                                          |
|-------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| Gameplay Ability System | Required. Ninja Combat is built on top of GAS.                                                                                 |
| Ninja G.A.S.            | Optional, but recommended. If used, configure it before setting up Ninja Combat.                                               |
| Ninja Input             | Optional. Required only if you want to activate combat abilities through Ninja Input handlers.                                 |
| Ninja Inventory         | Optional. Required only if you want equipment or weapons to be provided by Ninja Inventory. This can also be configured later. |

## Setup Checklist

| Step                           | Required          | Guide                                       |
|--------------------------------|-------------------|---------------------------------------------|
| Install and enable the plugin  | Yes               | [Installing Plugins](installing_plugins.md) |
| Add C++ module dependencies    | Yes, if using C++ | [Installing Plugins](installing_plugins.md) |
| Configure Collision Settings   | Yes               | [Collision Settings](collision_settings.md) |
| Configure GAS for Ninja Combat | Yes               | See below                                   |
| Configure Physical Materials   | Optional          | See below                                   |

## Gameplay Ability System Setup
Ninja Combat requires the **Gameplay Ability System** to be configured for combat actors. If you are using **[Ninja G.A.S.](gas_overview.md)**, 
configure that plugin first, then continue with the steps below.

### Ability System Globals
The Gameplay Ability System must use the **Ability System Globals** and **Gameplay Cue Manager** provided by Ninja Combat. 
If your project already has custom versions of these classes, they should inherit from the Ninja Combat classes.

| Class                  | Base Implementation                |
|------------------------|------------------------------------|
| Ability System Globals | `UNinjaCombatAbilitySystemGlobals` |
| Gameplay Cue Manager   | `UNinjaCombatGameplayCueManager`   |

<procedure title="Option 1: Set GAS classes via Project Settings" collapsible="true" default-state="expanded">
    <tip>The <b>Gameplay Ability Settings</b> page is only available in Unreal Engine 5.5 and above.</tip>
    <step>Open <b>Edit</b> &rarr; <b>Project Settings</b>.</step>
    <step>Select the <b>Gameplay Ability Settings</b> category.</step>
    <step>
        <p>Set the Ability System Globals and Gameplay Cue Manager classes to the Ninja Combat implementations.</p>
        <p><img src="cbt_setup_gas.png" alt="GAS Settings Page" thumbnail="true" border-effect="line" width="600"/></p>
    </step>
</procedure>

<procedure title="Option 2: Set GAS classes via DefaultGame.ini" collapsible="true" default-state="expanded">
    <step>Open your <code>DefaultGame.ini</code> file, located in your project's <code>Config</code> folder.</step>
    <step>
        <p>Add the required Ninja Combat GAS classes to the <code>[AbilitySystemGlobals]</code> section.</p>
        <code-block lang="ini" src="cbt_gas_global_settings.ini"/>
    </step>
</procedure>

## Physical Materials
Physical Materials are optional, but useful when weapons and projectiles should react differently based on the surface 
they hit. For example, a weapon impact may use different effects for flesh, stone, metal, or wood.

If your project already has a footsteps or surface-reaction system, you can usually consolidate the same Physical Surface 
and Physical Material setup for Ninja Combat.

### Physical Surfaces
Physical Surfaces identify the type of surface represented by a Physical Material.

<procedure title="Create Physical Surfaces" collapsible="true" default-state="expanded">
    <step>Open <b>Edit</b> &rarr; <b>Project Settings</b> &rarr; <b>Physics</b>.</step>
    <step>
        <p>In the <b>Physical Surface</b> section, add all entries required by your project.</p>
        <img src="cbt_setup_physical_surfaces.png" alt="Configuring Physical Surfaces" width="800" thumbnail="true" border-effect="line"/>
    </step>
</procedure>

Alternatively, you can add surfaces through `DefaultEngine.ini`, under the `[/Script/Engine.PhysicsSettings]` section.

<code-block lang="ini" src="cbt_setup_physical_surfaces.ini" collapsible="true" collapsed-title="Physical Surfaces"/>

### C++ Physical Surfaces
If you need to reference Physical Surfaces in C++, create a small header file with aliases matching your project setup.

<code-block lang="C++" src="cbt_setup_physical_surfaces.h" collapsible="true" collapsed-title="CustomPhysicalSurfaces.h"/>

### Physical Material Assets
Once your Physical Surfaces are configured, create Physical Materials and assign the correct surface type to each one.

<procedure title="Create Physical Materials" collapsible="true" default-state="expanded">
    <step>Create a new <b>Physical Material</b> from the <b>Content Browser</b>. They are available in the <b>Physics</b> category.</step>
    <step>When prompted to select a base class, select <code>NinjaCombatPhysicalMaterial</code></step>
    <step>
        <p>In the Physical Material, set the <b>Physical Surface</b> that matches it.</p>
        <img src="cbt_setup_physical_materials.png" alt="Configuring Physical Materials" width="800" thumbnail="true" border-effect="line"/>
    </step>
    <step>
        <p>Repeat these steps for all Physical Surfaces used by your project.</p>
        <img src="cbt_setup_physical_materials_collection.png" alt="Physical Materials Collection" width="800" thumbnail="true" border-effect="line"/>
    </step>
</procedure>

You can assign Physical Materials in different places:

| Source              | Assignment                                                                                                          |
|---------------------|---------------------------------------------------------------------------------------------------------------------|
| Skeletal Meshes     | In each collider in the **Physics Asset**, or through **PhysMat Override** in the Skeletal Mesh Component settings. |
| Static Meshes       | In the Collision Settings for the asset, or through **PhysMat Override** in the Static Mesh Component settings.     |
| Pawns or Characters | In their mesh components, or in dedicated **Collision Components** attached to bones in the skeleton.               |
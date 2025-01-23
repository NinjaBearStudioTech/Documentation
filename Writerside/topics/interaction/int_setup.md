# Setup
<primary-label ref="interaction"/>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Interaction** plugin.

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type
_inventory_ and the **Ninja Interaction** plugin should appear. Tick the checkbox and restart the engine.

## C++ Libraries

If you plan to work with C++ and use classes from the Interaction System, ensure you add the following modules to your
`Build.cs` file:

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#">
        PublicDependencyModuleNames.AddRange(new []
        {
            "GameplayAbilities",
            "GameplayBehaviorsModule",
            "GameplayBehaviorSmartObjectsModule",
            "GameplayTags",
            "GameplayTasks", 
            "ModelViewViewModel",
            "NinjaInteraction",
            "NinjaInteractionGameplay",
            "NinjaInteractionUI",
            "SmartObjectsModule",
            "UMG"
        });
        </code-block>
    </tab>
</tabs>

## Collision Channels

There are two roles involved in the collision system:

- **Interaction Scan Collision**: One or more Collision Components attached to the Interaction Manager's owner, responsible for scanning and detecting interactable targets within their range.
- **Interaction Target Collision**: A Collision Component attached to Interactable Actors. Enables interactable actors to be detected by the scan.

In this step, we will create a dedicated **Collision Preset** for each one of them. These presets will determine the
behavior for the **Object Channel** and **Trace Channel** dedicated to the Interaction System.

This configuration is done in the **Project Settings** panel, in the **Collision** category.

<img src="int_setup_collision_overview.png" alt="Collision Panel" thumbnail="true" border-effect="line"/>

### Object Channels

First, create a new **Object Channel** named `InteractionObject`, the **Default Response** should be `Ignore`. This
Object Channel is used to represent objects in the world that can be **detected** by interaction scanners. 

### Trace Channels

Next, create a new **Trace Channel** named `InteractionTrace`, the **Default Response** should be `Ignore`. This Trace
Channel is used to ensure that an interaction scanner has **line of sight** to a detected object.

### Presets

With the collision channels done, we are ready to configure two presets, one for the **Interaction Scan Collision** and
one for the **Interaction Target Collision**.

The **Source Preset** is set as follows:

- The **Collision** is enabled for **Query Only**.
- The **Object Type** is set to **Interaction Object**.
- All **Collision Responses are set to **Ignore**, except for **Interaction Object**, which is set to **Overlap**.

<img src="int_setup_collision_preset_source.png" alt="Collision Source Preset" thumbnail="true" border-effect="line"/>

The **Target Preset** is set as follows:

- The **Collision** is enabled for **Query Only**.
- The **Object Type** is set to **Interaction Object**.
- All **Collision Responses are set to **Ignore**, except for **Interaction Trace** and **Interaction Object**, which are set to **Block**.

<img src="int_setup_collision_preset_target.png" alt="Collision Target Preset" thumbnail="true" border-effect="line"/>

## Ability System

The **Ability System Component** is a prerequisite for the system to operate. Ensure that actors using the Interaction
Manager Component also have an **Ability System Component** and implement the `AbilitySystemInterface`.

Usually, both Interaction Abilities should also be granted by default. To know more about them, make sure to review the
[Abilities](int_abilities.md).
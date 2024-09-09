# Setup
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li><b>Download</b> and <b>install</b> the plugin.</li>
        <li>Make sure that all <b>pre-requisites</b> are executed before configuring the Combat System.</li>
        <li>If your project uses <b>C++</b>, make sure to add the correct <b>modules</b> to your <code>Build.cs</code> file.</li>
        <li>Configure the <b>Ability System</b> elements used by the Combat System.</li>
        <li>Add the necessary <b>Components</b> and <b>Interfaces</b> to your Character.</li>
    </ul>
</tldr>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Combat** plugin.

## Pre-Requisites
Before setting up the component, there are some pre-requisites to address.

First, a working **Gameplay Ability System** setup:
1. Add the **Ability System Component** to your Pawn or Player State.
2. Properly implement the **Ability System Interface** on your base class.
3. You should be able to add **Attribute Sets**, **Gameplay Effects** and **Gameplay Abilities**.
4. If you are using [Ninja G.A.S.](gas_overview.md), configure it first.

Then, make sure that you have the **Input** configured:
1. Your Player Character is ready to handle **Input Actions**.
2. If you are using [Ninja Input](ipt_overview.md), configure it first.

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type
_Combat_ and the **Ninja Combat** plugin should appear. Tick the checkbox and restart the engine.

## C++ Modules

If you plan to work with C++ and use classes from the Combat System, ensure you add the following modules to your
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
            "NinjaCombat",
            "NinjaCombatCamera",
            "NinjaCombatCore",
            "NinjaCombatActorPool",
            "NinjaCombatUI",
            "NinjaCombatActorWeapon",
            "StructUtils",
            "UMG"
        });
        </code-block>
    </tab>
</tabs>

## Ability System

There are two steps to execute during the initial setup: **Configure the Ability System Globals** and adding the 
**Combat Attribute Set**. 

As you explore other pages, or the how-tos, you will learn about other GAS-related aspects that can be configured later
on.

### Ability System Globals

The Ability System must be configured to use the **Global Class** and the **Cue Manager** provided by the project, or
a **custom subclass** exclusive to your project.

Add the following settings to your `DefaultGame.ini`, located in the `Config` folder.

``` ini
[/Script/GameplayAbilities.AbilitySystemGlobals]
AbilitySystemGlobalsClassName="/Script/NinjaCombat.NinjaCombatAbilitySystemGlobals"
GlobalGameplayCueManagerClass="/Script/NinjaCombat.NinjaCombatGameplayCueManager"
```

### Combat Attribute Set

Add the `NinjaCombatAttributeSet` to your character's Ability System Component. You find the sample data to initialize
it in the appropriate Attribute Set reference page.

## Collision Channels

You may want to create dedicated trace channels for Melee Scans and Projectiles. One way of doing that, for example is by
adding the following lines to your `DefaultEngine.ini` file, located in your `Config` folder.

```ini
[/Script/Engine.CollisionProfile]
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Weapon")
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel2,DefaultResponse=ECR_Block,bTraceType=True,bStaticObject=True,Name="Projectile")
```

Here is a breakdown of these collision types, so you can make sure that actors will also react correctly to them:

1. The **Weapon** channel is used to trace weapon collisions during **Melee Attacks**.
2. The **Projectile** channel is used to detect impacts from **Projectile Impacts**.

> **Ignore or Block?**
> 
> You should consider if you want your melee and ranged attacks only interacting with possible targets, or with 
> everything else too, so you could do things like adding decals to walls after hitting them with a sword or fireball.
{style="note"}

> **Double-check your Game Trace Channels**
> 
> The Trace Channels from the sample above might already be in use for other purposes in your game. Double-check that
> they are not conflicting with anything else to avoid odd collision issues. 
> 
> Also make sure that you are not duplicating the Collision Profile category itself.
{style="warning"}

Finally, assign these Collision Channels in your Combat Settings: `Edit` > `Project Settings` > `Ninja Combat` 

![Initial Settings](cbt_setup_settings.png "Initial Settings")

## Combat Component

Your main Character class must have the **Combat Manager** component added to it, along with the appropriate **Combat
System Interface**. Make sure to return the **Combat Manager** from the `GetCombatManager` function.

> **How about the other Components and Functions?**
>
> You don't need to worry about other components or methods in this interface for now, except for the **Weapon Manager** 
> and **Movement Component**, both listed below. 
>
> For more information about the other components, and how to use these interface functions, check the 
> **[Extensions](cbt_extensions.md)** page.
{style="note"}

### Weapon Manager

Create the appropriate **[Weapon Manager](cbt_weapon_architecture.md#weapon-manager)** and make sure to return it in the 
**Combat System Interface**. By default, you have **two options** available for the Weapon Manager type:

- **Default**: A basic Weapon Manager that can be used as-is for simpler scenarios.
- **Equipment**: This Weapon Manager is compatible with the **[Inventory System](inv_overview.md)**.

> **One step at a time**
> 
> Even if you plan to integrate with Ninja Inventory, consider starting with the **Default Weapon Manager**, so you 
> can make sure that your system works as expected, before introducing more layers to it.

### Movement Component

If you want to use the provided Combat **Character Movement Component**, make sure to override the default one in your
character, either in C++ or in your Blueprint.

You are not required to use this Movement Component in your project, and it is also fine to use a completely different
Movement Solution.
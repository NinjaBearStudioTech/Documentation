# Setup
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Install the Ninja Combat plugin using the Epic Games Launcher.</li>
        <li>Open your project and enable the plugin: <code>Edit</code> &rightarrow; <code>Plugins</code>, search for <i>combat</i>, and tick the checkbox for <b>Ninja Combat</b>. Restart the engine.</li>
        <li>Add <code>NinjaCombatWeaponManagerComponent</code> to your <b>Character</b>. The actor must implement <code>AbilitySystemInterface</code>.</li>
        <li>Add <code>NinjaCombatDamageManagerComponent</code> to the same object that has the Inventory Manager. Implement the <code>GetInventoryManager</code> function.</li>
        <li>Add <code>NinjaCombatDefenseManagerComponent</code> to the same object that has the Inventory Manager. Implement the <code>GetInventoryManager</code> function.</li>
        <li>Add <code>CombatSystemInterface</code> to your character and implement the appropriate <i>Getter</i> functions for the components above.</li>
        <li>Add and initialize the <code>UNinjaCombatAttributeSet</code> to your character's Ability System Component.</li>
        <li>Set the correct <b>Ability System Global Objects</b> to your <code>DefaultGame.ini</code> file.</li>
        <li>Create the appropriate <b>Collision Channels</b>: <code>Weapon</code>, <code>Projectile</code> and <code>Opportunity</code>.</li>
    </ul>
</tldr>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Combat** plugin.

## Pre-Requisites
Before setting up the component, there are some pre-requisites to address.

First, a working **Gameplay Ability System** setup:
1. Add the **Ability System Component** to your Pawn or Player State.
2. Properly implement the **Ability System Interface** on them.
3. Being able to add **Attribute Sets**, **Gameplay Effects** and **Gameplay Abilities**.

Then, make sure that you have the **Input** configured:
1. Your Player Character is ready to handle **Input Actions**
2. If you are using [Ninja Input](ipt_overview.md), configure it first.

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type
_Combat_ and the **Ninja Combat** plugin should appear. Tick the checkbox and restart the engine.

## C++ Libraries

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
            "NinjaCombatActorPool",
            "NinjaCombatUI",
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
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel3,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=True,Name="Opportunity")
```

Here is a breakdown of these collision types, so you can make sure that actors will also react correctly to them:

1. The **Weapon** and **Projectile** collisions are relevant to your character's meshes, so it should **Block** them.
2. The **Opportunity** collision is relevant to your character's capsule, so it should **Overlap** it.

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

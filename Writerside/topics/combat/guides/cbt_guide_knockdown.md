# Knockdown and Recovery
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to configure **knockdown** and **recovery** for combatants.

Knockdown is an optional fatal damage reaction. When enabled, fatal damage can place a combatant into a temporary
knocked down state instead of immediately starting the normal death flow. The combatant can then recover through a
Gameplay Event, or die if the knockdown duration expires.

For more information, see [**Damage Reactions and Vulnerable States**](cbt_concept_vulnerable_states.md).

## Prerequisites

### Collision and Components

Your collision channels, combat components, Ability System setup, and base character setup should already be configured.
For more information, see [**Combat Setup**](cbt_setup.md) and [**Combat First Steps**](cbt_first_steps.md).

### Damage Pipeline

The combatant must use a **Damage Data** asset through its Damage Manager or Combat Manager. This asset defines the damage
outcome pipeline used to resolve fatal damage as knockdown.

## Animation Assets

Knockdown usually uses three animation-related pieces:

* An **Animation Blueprint** that can react to the knocked down state.
* A **Knock Down Montage** that plays when the combatant enters knockdown.
* A **Recovery Montage** that plays when the combatant recovers.

### Animation Instance

The Animation Blueprint should react to the combatant's knocked down state. The default Ninja Combat Animation Instance
already exposes `bKnockedDown`, which can be used by the Anim Graph.

<procedure title="Configure the Animation Instance" collapsible="true" default-state="collapsed">
    <step>Create an Animation Blueprint using <code>NinjaCombatAnimInstance</code> as the base class.</step>
    <step>In your Anim Graph or state machine, use <code>bKnockedDown</code> to blend into and out of knocked down animation states.</step>
    <step>Make sure your Animation Blueprint has a full-body Slot that can be used by the knockdown and recovery montages.</step>
</procedure>

### Animation Montages

The **Knock Down Ability** and **Knock Down Recovery Ability** each play an Animation Montage.

<procedure title="Create the Knockdown Montages" collapsible="true" default-state="collapsed">
    <step>Create an Animation Montage for the transition into knockdown.</step>
    <step>Create an Animation Montage for the recovery animation.</step>
    <step>Set both montages to use the full-body Slot configured in your Animation Blueprint.</step>
    <step>Adjust blend times as needed so the transitions into and out of the knocked down state feel smooth.</step>
</procedure>

## Movement Component
<secondary-label ref="optional"/>

If your character should move differently while knocked down, use a movement component that can react to the combat state.

Ninja Combat provides `NinjaCombatCharacterMovementComponent`, which can listen to combat state changes and adjust movement
settings such as walk speed.

<procedure title="Configure Knockdown Movement" collapsible="true" default-state="collapsed">
    <step>Open your Character Blueprint or base character class.</step>
    <step>Select the Movement Component.</step>
    <step>Configure the movement settings used while the character is knocked down.</step>
</procedure>

For more information, see [**Combat Components**](cbt_concept_components.md).

## Knockdown Abilities

Knockdown uses two Gameplay Abilities:

-`CombatAbility_KnockDown`, which handles entering the knocked down state.
-`CombatAbility_KnockDownRecovery`, which handles recovery.

Both abilities should usually be granted by default to combatants that can be knocked down and recovered.

### Configure the Knock Down Ability

<procedure title="Configure the Knock Down Ability" collapsible="true" default-state="collapsed">
    <step>Create a Gameplay Ability Blueprint using <code>CombatAbility_KnockDown</code> as the base class.</step>
    <step>Set the <b>Default Animation Montage</b> to the knockdown montage created earlier.</step>
    <step>Keep the default <b>Knocked Down State Effect Class</b>, or assign a custom effect based on <code>CombatEffect_KnockedDown</code>.</step>
    <step>Keep the default <b>Dead Effect Class</b>, or assign a custom death effect used when the knockdown duration expires.</step>
    <step>Grant this ability to the combatant.</step>
</procedure>

### Configure the Recovery Ability

<procedure title="Configure the Knock Down Recovery Ability" collapsible="true" default-state="collapsed">
    <step>Create a Gameplay Ability Blueprint using <code>CombatAbility_KnockDownRecovery</code> as the base class.</step>
    <step>Set the <b>Default Animation Montage</b> to the recovery montage created earlier.</step>
    <step>Keep the default <b>Recovery Effect Class</b>, or assign a custom effect based on <code>CombatEffect_RecoverFromKnockDown</code>.</step>
    <step>Grant this ability to the combatant.</step>
</procedure>

## Knockdown Attributes

The default knockdown flow uses two Gameplay Attributes:

| Attribute                | Description                                                          |
|--------------------------|----------------------------------------------------------------------|
| `KnockDownDuration`      | Defines how long the combatant can remain knocked down before dying. |
| `KnockDownHealthPercent` | Defines how much health is restored when recovering from knockdown.  |

Both values must be greater than zero for the default Knock Down outcome to resolve fatal damage as knockdown.

<procedure title="Configure Knockdown Attributes" collapsible="true" default-state="collapsed">
    <step>Open the attribute initialization table assigned to your combatant.</step>
    <step>Set <code>NinjaCombatAttributeSet.KnockDownDuration</code> to a value greater than <code>0</code>.</step>
    <step>Set <code>NinjaCombatAttributeSet.KnockDownHealthPercent</code> to a value greater than <code>0</code>.</step>
</procedure>

## Damage Setup

The combatant must opt into knockdown through its Damage Data and Combat Manager configuration.

<procedure title="Configure Knockdown Damage Resolution" collapsible="true" default-state="collapsed">
    <step>Open the Damage Data asset assigned to the combatant.</step>
    <step>Add the <b>Knock Down Damage Outcome</b> to the damage outcome pipeline.</step>
    <step>Make sure the Damage Data asset is assigned to the combatant's Damage Manager or Combat Manager.</step>
    <step>Open the combatant's Combat Manager.</step>
    <step>Enable <b>Can Enter Knockdown State</b>.</step>
</procedure>

Once this is configured, fatal damage can be redirected into knockdown instead of immediately starting the death flow.

> **Bypassing Knockdown**
>
> Damage can bypass knockdown by using the appropriate bypass tag in the incoming damage source tags. This is useful for
> attacks that should always kill instead of allowing recovery.
> {style="tip"}

## Recovery

Recovery can be triggered by any system that sends the `Combat.Event.RecoverFromKnockDown` Gameplay Event to the knocked
down combatant. Common recovery sources include:

* Another player interacting with a fallen ally.
* A trigger volume.
* A gameplay objective.
* A scripted event.
* Custom Blueprint or C++ logic.

The only requirement is that the recovering combatant currently has the knocked down state.

### Recovery Volume Example

This example uses a Trigger Box to recover knocked down combatants that overlap it. You can use the same event flow from
other systems, such as Ninja Interaction.

<procedure title="Create a Recovery Volume" collapsible="true" default-state="collapsed">
    <step>Create a Blueprint based on <b>Trigger Box</b>.</step>
    <step>Create a function named <code>HasKnockDownEffect</code> that receives an Actor.</step>
    <step>In <code>HasKnockDownEffect</code>, retrieve the Actor's Ability System Component.</step>
    <step>Create an active Gameplay Effect query that checks for <code>CombatEffect_KnockedDown</code> as the effect definition.</step>
    <step>Return whether the Ability System Component has an active Gameplay Effect matching that query.</step>
    <step>Create a function named <code>SendRecoveryEvent</code> that receives an Actor.</step>
    <step>In <code>SendRecoveryEvent</code>, check for authority and retrieve the Actor's Ability System Component.</step>
    <step>Send a Gameplay Event using the <code>Combat.Event.RecoverFromKnockDown</code> Gameplay Tag.</step>
    <step>In the Event Graph, bind to the collision component's <b>On Begin Overlap</b> event on authority.</step>
    <step>When an Actor overlaps, call <code>HasKnockDownEffect</code>.</step>
    <step>If the Actor is knocked down, call <code>SendRecoveryEvent</code>.</step>
</procedure>

## Give Up
<secondary-label ref="optional"/>

A knocked down combatant can also be forced into the death flow by sending the `Combat.Event.GiveUp` Gameplay Event.

This can be used for player-controlled give-up actions, timers, AI behavior, or scripted events.

<procedure title="Trigger Give Up" collapsible="true" default-state="collapsed">
    <step>Retrieve the knocked down combatant's Ability System Component.</step>
    <step>Send a Gameplay Event using the <code>Combat.Event.GiveUp</code> Gameplay Tag.</step>
</procedure>

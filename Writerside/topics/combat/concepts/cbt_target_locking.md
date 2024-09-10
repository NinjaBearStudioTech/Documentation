# Target Locking
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Targets are collected using the <b>Gameplay Targeting System</b>.</li>
        <li>The <b>Target Lock</b> ability collects targets and optionally tracks the distance. Targets are stored by the <b>Target Manager Component</b>.</li>
        <li>Targets can be set or cleared using <b>Gameplay Events</b>.</li>
        <li>The <b>Ninja Combat Marker Actor</b> can be used to represent a player's current target.</li>
    </ul>
</tldr>

## Target Lock Ability

### Targeting Presets

### Gameplay Events

The **Target Lock** ability can receive a new target or clear its current one via **Gameplay Events**.

A **new target** can be set by sending a Gameplay Event using the `Combat.Event.Target.Acquired`. The new target will be
obtained from the first **optional object**.

The current target can be **cleared** by sending a Gameplay Event using the `Combat.Event.Target.Dismissed`. This will
also end the Target Lock Ability's execution.

## Target Manager Component

The main **Combat Manager** component is the default implementation for the Target Manager, which is defined by the
`CombatTargetManager` Interface.

## Combat Marker Actor

This Actor is used to represent the Player's **current target**. It can provide a **cosmetic** elements such as the 
target's health bar or status effects.

The Target Manager Component manages the Combat Marker Actor's lifecycle.

## Integrated Systems

A common requirement for a **Target Lock** system is to have its owner **strafing** whenever they are locked on a given
target. To that end, two relevant systems are automatically integrated with the Target Lock: **Movement** and 
**Animation**.

### Character Movement Manager

The default **Combat Character Movement Manager** component can automatically toggle **strafing** if its owner has a 
locked target.

### Combat Animation Instance

The base **Combat Animation Instance** can automatically modify the value of its **strafing** property depending on 
whether the owner has a locked target or not.
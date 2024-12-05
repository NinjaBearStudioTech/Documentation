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

The **Target Locking** is feature built using the **Gameplay Targeting System** to select a target to be locked on. 

## Target Lock Ability

The Target Lock ability is responsible for collecting potential targets and track them until one of these things happen:

1. The target is **deliberately deselected**.
2. A certain **distance threshold** is passed. 
3. The target's **death delegate** is broadcast.
4. The Target Lock ability ends.

<img src="cbt_target_ability.png" alt="Target Lock Ability" thumbnail="true" border-effect="line"/>

Within the **Target Lock** category, you can set many relevant aspects of the lock, here's a breakdown of these
properties.

| Property                 | Description                                                                                |
|--------------------------|--------------------------------------------------------------------------------------------|
| Targeting Preset         | Targeting Preset data used to collect the appropriate target.                              |
| Next Targeting Preset    | A different preset that can be used if a next target is selected.                          |
| Move to New Targets      | If set to true, the Ability collects new targets when the current one becomes unavailable. |
| Perform Async Targeting  | Configures the Gameplay Targeting System to collect targets asynchronously.                |
| Distance Threshold       | An optional threshold that, if exceeded, deselects the current target.                     |
| Target Lock Effect Class | Gameplay Effect applied to the target once a target is locked.                             |

### Activation

The Target Lock Ability can be activated normally, by **Gameplay Tags** or the **Ability Class**, but it can also be 
activated via **Gameplay Events**. This can be useful to AI Agents collecting their targets using the **Perception System**.

The Gameplay Event activation allows the new target to be provided in the **Event Payload**. Events can be used to 
either **activate** or **deactivate** the ability.

| Gameplay Event                  | Description                                                                                  |
|---------------------------------|----------------------------------------------------------------------------------------------|
| `Combat.Event.Target.Acquired`  | A **new target** is set, obtained from the first **Optional Object** in the event's Payload. |
| `Combat.Event.Target.Dismissed` | The current target is **cleared**. This will also end the Target Lock Ability's execution.   |

> **Add this Ability By Default**
> 
> The Target Lock ability is meant to be added to characters by default, so it is always ready to be activated, either
> via **Gameplay Tags**, **Ability Class** or **Gameplay Events**.

### Targeting Presets

Targets are selected using **Gameplay Targeting System**, which provides a powerful and declarative way to find actors 
in the world.

It uses **Targeting Presets**, along with **Targeting Tasks**, to **Select**, **Filter** and **Sort** targets. You can 
find more details about this framework in the [official documentation][1].

In the following image, you can see a sample of what a Targeting Preset could look like for the Target Locking ability. 

<img src="cbt_target_preset.png" alt="Selecting Targets" thumbnail="true" border-effect="line"/>

1. The **AOE Selection Task** collects targets in a _sphere_, with a radius of 1600. It is set to ignore the source actor and instigator.
2. Selected actors are filtered by the **Filter Actor Task**, so only `PluginLabsCharacter` subclasses are selected.
3. Selected actors are filtered again by the **Facing Filter Task** to ensure an angle of 60 degrees from the source.
4. Finally, actors are filtered one last time to make sure they are not dead.

You can represent any criteria using Targeting Presets, and you can also create new tasks of any category.

## Target Manager Component

The **Combat Manager** component is the default implementation for the Target Manager, which is defined by the `CombatTargetManager` 
Interface. This implementation provides the following properties that can adjust the Target Lock's
behavior:

- **Control Rotation**: Enables or disables automatic rotation of the Controller to face the current target.
- **Predict Target**: Allows the local player to predict the target, before waiting for server confirmation.

### Controller Rotation

The default Target Manager implementation (the Combat Manager) can optionally rotate the **Controller** to focus on
the **locked target**. The following properties adjust this behavior.

| Property                    | Description                                                                        |
|-----------------------------|------------------------------------------------------------------------------------|
| `bRotateControllerToTarget` | Determines if the controller should be automatically rotated to the locked target. |
| `bLockControllerPitch`      | Determines if the pitch should be locked or allow input.                           |
| `bLockControllerYaw`        | Determines if the yaw should be locked or allow input.                             |
| `RotationInterpSpeed`       | Determines how fast the rotation happens.                                          |

## Combat Marker Actor

This Actor is used to represent the Player's **current target**. It can provide a **cosmetic** elements such as the 
target's health bar or status effects. The **Target Manager Component** manages the Combat Marker Actor's lifecycle. 

### Placement

The Combat Marker Actor attached to a **Scene Component** present on the target. This Scene Component should be placed
in the appropriate location, above the character's head, for example.

Any Scene Component or subcomponents can be used. Regardless of the component type, it must be tagged with 
`Combat.Component.TargetLockAnchor`. 

<img src="cbt_target_marker_placement.png" alt="Target Lock Placement" thumbnail="true" border-effect="line"/>

### Widgets

It will usually contain certain widgets that informs the player which target is currently selected. A common feature in 
this actor is a **Widget Component**, hosting a widget that might benefit from the **[Combat Viewmodels](cbt_user_interface.md#umg-viewmodels)**.

The following example demonstrates a widget that can be used in a Marker Actor. Notice the Viewmodels bound to multiple
components in the widget.

<img src="cbt_target_marker_widget.png" alt="Target Lock Widget" thumbnail="true" border-effect="line"/>

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

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-targeting-system-in-unreal-engine

<seealso style="cards">
    <category ref="related">
        <a href="cbt_character_animation.md" summary="Information about animation elements.">Animation Elements</a>
        <a href="cbt_movement_component.md" summary="Details about the Movement Component.">Movement Support</a>
        <a href="cbt_integration_input.md" summary="Integration with Ninja Input.">Ninja Input Integration</a>
    </category>
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-targeting-system-in-unreal-engine" summary="Official documentation for the Gameplay Targeting System.">Gameplay Targeting System</a>
    </category>
</seealso>
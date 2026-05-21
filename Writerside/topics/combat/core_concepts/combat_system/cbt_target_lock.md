# Target Lock
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Target Lock system allows players or AI to <b>lock onto enemies</b> for focused movement and attacks.</li>
        <li>Locking is <b>visualized through a Marker Actor</b>, which attaches to the target and can be fully customized.</li>
        <li>The <b>Target Lock Ability</b> manages acquisition, switching, and disengaging from targets based on targeting presets.</li>
        <li><b>Gameplay Effects and Events</b> can be used to track or react to the lock state in other systems.</li>
    </ul>
</tldr>

Certain games allow players to **lock onto a specific target**, helping them focus their attacks regardless of
**camera movement** or **other nearby enemies**.

A locked target should also be considered by other systems, such as [](cbt_motion_warping.md), to ensure that attacks 
**prioritize the locked target**, and [Movement](cbt_movement_component.md), since locking onto a target commonly shifts 
the character into **strafing movement**.

The Target Lock functionality is implemented through a dedicated **Gameplay Ability**, which uses the **[](cbt_gameplay_targeting_system.md)** 
and a dedicated **Marker Actor** to visually represent the current locked-on target.

## Marker Actor
The **Marker Actor** is the first participant in the Target Lock system. It visually represents which target is
currently locked on by the player, typically using a **widget** such as a _dot_, an _arrow_, or other visual markers.

> **Target Awareness**
>
> The Marker Actor is always **aware of its current locked-on target**. You can retrieve it at any time via
> the `GetCurrentTarget` function.
{style="note"}

The Marker Actor is automatically **attached** to the current target’s **Scene Component** tagged with
`Combat.Component.TargetLockAnchor`. This behavior, along with others, can be customized in Blueprint or C++ child classes.

| Function              | Description                                                                                                                                                    |
|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `FindAttachAnchor`    | Finds the anchor point for the target. By default, selects a **Scene Component** with the appropriate **Gameplay Tag**. Can be overridden for advanced setups. |
| `AttachToTarget`      | Handles the **attachment logic** when locking onto a target.                                                                                                   |
| `DetachFromTarget`    | Handles the **detachment logic** when unlocking or switching targets.                                                                                          |
| `HandleTargetSet`     | Hook for custom logic when a new target is locked.                                                                                                             |
| `HandleTargetCleared` | Hook for custom logic when a target is cleared.                                                                                                                |

The base actor extends `NinjaCombatMarkerActor`, which provides a built-in **Widget Component** and is fully compatible
with the [Actor Pool](cbt_actor_pooling.md) provided by Ninja Combat.

<procedure title="Creating a Marker Actor" collapsible="true" default-state="expanded">
    <step>Create a new <b>Gameplay Widget</b> to represent the marker (e.g., a simple <i>dot</i> or <i>arrow</i>).</step>
    <step>
        <p>In your Content Browser, create a new Actor based on <code>NinjaCombatMarkerActor</code>.</p>
        <img src="cbt_target_lock_marker_widget.png" alt="Marker Widget" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Assign the created <b>Widget</b> to the <b>Target Lock Widget Component</b> of your new actor.</p>
        <img src="cbt_target_lock_marker_actor.png" alt="Marker Actor" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

## Target Manager Component
Targets are **managed** and **replicated** by a **Target Manager Component**.  
By default, the **Combat Manager Component** fulfills this role, but any Actor Component implementing `CombatTargetManagerInterface` can be used.

The Target Manager is responsible for:

- **Instantiating** the **Marker Actor**, based on a predefined class.
- **Storing**, **replicating**, and **broadcasting** the current target when it is **set** or **cleared**.

### Controller Rotation
The default Target Manager (provided by the Combat Manager Component) also offers **optional controller rotation** toward the locked target.  
This improves gameplay by keeping the character and camera naturally aligned during lock-on.

The following properties control this behavior:

| Property                    | Description                                                                          |
|-----------------------------|--------------------------------------------------------------------------------------|
| `bRotateControllerToTarget` | If true, automatically rotates the Controller to face the locked target.             |
| `bLockControllerPitch`      | If true, locks the pitch during lock-on. If false, player input can still modify it. |
| `bLockControllerYaw`        | If true, locks the yaw during lock-on. If false, player input can still modify it.   |
| `RotationInterpSpeed`       | Determines the interpolation speed when rotating toward the locked target.           |

## Target Lock Ability
The **Target Lock Ability** is assigned to any character intended to lock onto targets. Once activated, it collects the
best available target using a **[Targeting Preset](cbt_gameplay_targeting_system.md)** and synchronizes it with the
**Target Manager Component**.

| Property                 | Description                                                                                |
|--------------------------|--------------------------------------------------------------------------------------------|
| Targeting Preset         | Targeting Preset used to find an eligible target.                                          |
| Next Targeting Preset    | Optional alternate preset used when selecting a new target after one is dismissed.         |
| Move to New Targets      | If true, automatically searches for a new target when the current one becomes unavailable. |
| Perform Async Targeting  | If true, collects targets asynchronously using the Gameplay Targeting System.              |
| Distance Threshold       | Optional distance limit — exceeding it deselects the current target.                       |
| Target Lock Effect Class | Gameplay Effect applied to the **target** when a lock is established.                      |
| Source Lock Effect Class | Gameplay Effect applied to the **source** (locker) when a lock is established.             |

<procedure title="Configuring the Target Lock Ability" collapsible="true" default-state="expanded">
    <step>
        <p>Create a new <b>Targeting Preset</b> that will be used to find <b>eligible targets</b>. You can configure filters and selection criteria, remembering that <b>tasks are executed in order</b>.</p>
        <img src="cbt_target_lock_targeting_preset.png" alt="Target Lock Preset" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_TargetLock</code>. Set your <b>Targeting Preset</b> in the ability's properties.</p>
        <img src="cbt_target_lock_ability.png" alt="Target Lock Ability" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

### Gameplay Effects
The Target Lock Ability is pre-configured to apply **Gameplay Effects** to both the **source** and the **target**.  
By default, these effects simply assign Gameplay Tags that can be tracked by other systems, but you can extend them
to include additional logic or modifiers as needed.

### Gameplay Events
You can activate or deactivate the Target Lock Ability either **manually** (by class or tag) or **automatically** via
**Gameplay Events**:

- To **activate** the ability using a Gameplay Event, send `Combat.Event.Target.Acquired`, providing the **new target actor** as the payload's **first optional actor**.
- To **deactivate** the ability, send `Combat.Event.Target.Dismissed`.

Once the Target Lock Ability is configured, players (or AI) will be able to seamlessly acquire, track, and disengage 
targets during combat.

## Integrated Systems
A common requirement for a **Target Lock** system is to have its owner **strafing** whenever they are locked onto a target.  
Two relevant systems are automatically integrated with Target Lock:

- **Character Movement Manager**: The default **Combat Character Movement Manager** component can automatically toggle **strafing** when its owner has a locked target.
- **Combat Animation Instance**: The base **Combat Animation Instance** automatically updates its **strafing** property based on whether the owner currently has a locked target.

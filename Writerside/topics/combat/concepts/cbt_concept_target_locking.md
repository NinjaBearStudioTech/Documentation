# Target Locking
<primary-label ref="combat"/>

Certain games allow players to **lock onto a specific target**, helping them focus their attacks regardless of
**camera movement** or **other nearby enemies**.

A locked target is also relevant to other systems, such as [**Motion Warping**](cbt_concept_motion_warping.md), to ensure
that attacks **prioritize the locked target**, and [**Movement**](cbt_concept_components.md#combat-movement-component), since
locking to a target commonly shifts the character into **strafing movement**.

> **Internal Integration**
>
> If you are using the **Motion Warping Component** and the **Character Movement Component** provided by Ninja Combat,
> or your own subclasses of these components, these integrations are immediately available.

The Target Lock functionality is implemented through a dedicated **Gameplay Ability**, a **Targeting Preset** and a
**Marker Actor** to visually represent the current locked-on target.

## Target Manager Component

Targets are **managed** and **replicated** by a **Target Manager Component**, defined by `CombatTargetManagerInterface`.
By default, the **Combat Manager Component** is a valid implementation for that component.

The Target Manager is responsible for **instantiating** the **Marker Actor** and also **storing**, **replicating**, and
**broadcasting** the current target when it is **set** or **cleared**.

### Listening to Target Changes

Other systems can react to target changes by binding to the Target Manager Component through `BindToCombatTargetChangedDelegate`.

This is useful for systems that need to update behavior when a target is locked, switched, or cleared, such as UI,
movement, camera logic, animation, or custom combat assists.

When the listener is no longer valid, it should unbind using `UnbindFromTargetChangedDelegate`.

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

## Marker Actor

The **Marker Actor**, `NinjaCombatMarkerActor`, visually represents which target is currently locked on by the player.
It can use any visual elements, such as widgets or particle systems to represent that a given actor is the current
locked-on target.

> **Target Awareness**
>
> The Marker Actor is **always aware of its current locked-on target**. You can retrieve it at any time via the available
> `GetCurrentTarget` function.
{style="note"}

If the marker widget needs to know which actor is currently locked, implement `CombatActorAwareInterface`. The Marker Actor
automatically sends the current target to compatible widgets when the target is set or cleared.

The Marker Actor is automatically **attached to the current target's Scene Component** tagged as `Combat.Component.TargetLockAnchor`.
This behavior, along with others, can be customized in Blueprint or C++ child classes.

| Function              | Description                                                                                                                                                    |
|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `FindAttachAnchor`    | Finds the anchor point for the target. By default, selects a **Scene Component** with the appropriate **Gameplay Tag**. Can be overridden for advanced setups. |
| `AttachToTarget`      | Handles the **attachment logic** when locking onto a target.                                                                                                   |
| `DetachFromTarget`    | Handles the **detachment logic** when unlocking or switching targets.                                                                                          |
| `HandleTargetSet`     | Hook for custom logic when a new target is locked.                                                                                                             |
| `HandleTargetCleared` | Hook for custom logic when a target is cleared.                                                                                                                |

The base actor is also a **poolable actor**, integrated with the [**Actor Pool**](cbt_concept_actor_pooling.md).

## Target Lock Ability

The **Target Lock Ability** is assigned to any character intended to lock onto targets. Once activated, it collects the
best available target using a **Targeting Preset**, supports **target cycling** and synchronizes them with the
**Target Manager Component**.

| Property                          | Description                                                                                     |
|-----------------------------------|-------------------------------------------------------------------------------------------------|
| Targeting Preset                  | Targeting Preset used to find an eligible target.                                               |
| Perform Async Targeting           | If true, collects targets asynchronously using the Gameplay Targeting System.                   |
| Track Distance                    | If true, tracks distance from the current target.                                               |
| Distance Threshold                | Optional distance limit. Exceeding it deselects the current target.                            |
| Adjacent Target Collision Channel | Collision channel used to find adjacent targets when cycling left or right.                    |
| Adjacent Target Distance          | Maximum distance used to find adjacent targets when cycling left or right.                     |
| Trace Complex Adjacent Targets    | If true, the adjacent target overlap uses complex collision.                                   |
| Target Lock Effect Class          | Gameplay Effect applied to the **source** when it locks onto a target.                         |
| Source Lock Effect Class          | Gameplay Effect applied to the **target** when it is locked by the source.                     |

### Gameplay Effects
The Target Lock Ability is pre-configured to apply **Gameplay Effects** to both the **source** and the **target**.  
By default, the source receives a Gameplay Effect indicating that it is locked onto a target, while the target receives
a Gameplay Effect indicating that it is being locked by the source.

These effects simply assign Gameplay Tags that can be tracked by other systems, but you can extend them to include
additional logic or modifiers as needed.

### Target Death
When the current target dies, the Target Lock Ability clears the target and ends.

If your game should automatically move to another target, override `HandleTargetDeath` in Blueprint or C++ and run your
own target acquisition logic before ending the ability.

### Gameplay Events
You can activate or deactivate the Target Lock Ability either **manually** (by class or tag) or **automatically** via
**Gameplay Events**:

| Event                           | Description                                                                                                               |
|---------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| `Combat.Event.Target.Acquired`  | Activates the ability from an external system, locking to the Actor provided in the payload.                              |
| `Combat.Event.Target.Scan`      | Re-runs the Targeting Preset to find a target. If a target is already locked, it is kept if no new valid target is found. |
| `Combat.Event.Target.Left`      | Moves to a target to the left from the current one, if any. Cycles around targets.                                        |
| `Combat.Event.Target.Right`     | Moves to a target to the right from the current one, if any. Cycles around targets.                                       |
| `Combat.Event.Target.Dismissed` | Cancels the target lock.                                                                                                  |

Once the Target Lock Ability is configured, players (or AI) will be able to seamlessly acquire, track, and disengage
targets during combat.

> **Target Locking for AI**
>
> Players usually have an Input configured to activate the Target Lock Ability. AI can send a Gameplay Event to activate
> the ability whenever a Perception Target is confirmed. [**Ninja Bot**](bot_overview.md) performs this automatically.
>
> For AI or external systems that provide the target directly through `Combat.Event.Target.Acquired`, the ability does not
> require a Targeting Preset. In that case, the payload must provide a valid Actor as the event's Optional Object.
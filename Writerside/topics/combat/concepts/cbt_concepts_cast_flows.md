# Cast Flows
<primary-label ref="combat"/>

The **Cast Ability** is a flexible Gameplay Ability base for casts that need to be **created**, **placed**, or **triggered**
in the world. It can be used for many kinds of world-based casts, including:

- **Immediate explosions** that damage nearby enemies.
- **Hazard pools** or **healing zones** that remain in the world and affect overlapping targets.
- **Meteors**, **blizzards** or other delayed impacts that strike a targeted location.

A **Cast Flow** describes how the ability resolves that cast. Each flow uses the **same base ability**, but changes how
**targets are collected** and, in some cases, **where the Cast Actor spawns**.

Cast Flows can use **Targeting Presets**, **Ability Targeting Actors**, dedicated **Cast Actor Blueprints**, or a combination
of these systems. Each flow can be created **independently**, although some supporting assets may be shared between examples.

This page explains the main concepts used by Cast Flows, including targeting modes, cast triggers, commit times, Gameplay
Effects, Cast Actors, and extension points.

## Ability Targeting Actor

An **Ability Targeting Actor** is used when the Cast Ability needs a confirmation step before resolving the cast.

You can use any Targeting Actor provided by the Gameplay Ability System. Ninja Combat also provides
`NinjaCombatAbilityTargetingActor`, a generic base class that can collect targets using a Targeting Preset or broadcast 
its own location when the actor is only being used for placement.

This class is compatible with the [**Actor Pool**](cbt_actor_pooling.md).

> **Begin Play**
>
> Since the provided Ability Targeting Actor is compatible with the [**Actor Pool**](cbt_actor_pooling.md), it may be 
> instantiated before they are actually needed. Avoid using `BeginPlay` for startup logic. Use `HandleTargetActorActivated` 
> instead.
{style="note"}

## Cast Actor

A **Cast Actor** is used when the ability needs to create an actor in the world, such as a meteor, lava pool, aura,
explosion volume, or similar world-based cast.

Use `NinjaCombatCastActor` as the base class when possible. The Cast Actor is responsible for collecting targets and
applying the Gameplay Effect configured by the ability.

If you cannot use the provided base class, any actor that implements `CombatCastInterface` can be used instead.

Regardless of whether you are using `NinjaCombatCastActor` or your own interface implementation, implement `StartCast`
with the activation logic that should run when the actor becomes relevant to the cast.

> **Begin Play**
>
> Since Cast Actors are compatible with the [**Actor Pool**](cbt_actor_pooling.md), they may be instantiated before they
> are actually needed. Avoid using `BeginPlay` for cast startup logic. Use `StartCast` instead.
{style="note"}

### Cast Interface

Any actor used as a Cast Actor must implement `CombatCastInterface`. This interface provides the data needed by the Cast 
Ability and defines the function used to start the cast.

| Function                  | Description                                                                                                   |
|---------------------------|---------------------------------------------------------------------------------------------------------------|
| `GetCastOwner`            | Returns the actor responsible for the cast.                                                                   |
| `SetCastOwner`            | Sets the actor responsible for the cast. Usually invoked by the Cast Ability when preparing the actor.        |
| `SetGameplayEffectHandle` | Sets the Gameplay Effect Handle that the Cast Actor can apply to collected targets.                           |
| `StartCast`               | Starts the cast, allowing the actor to run activation logic, collect targets, and apply the Gameplay Effect.  |

## Cast Ability

The **Cast Ability** coordinates the full Cast Flow. Depending on its configuration, it can collect targets directly, wait
for target confirmation, spawn a Cast Actor, or combine targeting and spawning into the same flow.

### Cast Triggers

Once the ability activates, it may wait for a specific trigger before starting the cast.

| Trigger                | Description                                                                                                                                                                                                        |
|------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Ability Activation** | The cast starts immediately, as soon as the Gameplay Ability activates.                                                                                                                                            |
| **Gameplay Event**     | The cast starts when the ability receives the `Combat.Event.Cast` Gameplay Event. This can be sent by gameplay code, Blueprint logic, or the provided **Trigger Cast** Animation Notify.                           |
| **Delayed**            | The cast starts after a configured delay. From there, it behaves similarly to **Ability Activation**. This option is only compatible with non-interactive flows, such as **Targeting System** and **Spawn Actor**. |

### Targeting Modes

The Cast Ability supports multiple targeting modes for different usage scenarios.

| Targeting                                 | Description                                                                                                        |
|-------------------------------------------|--------------------------------------------------------------------------------------------------------------------|
| **Targeting System**                      | Applies the Cast Gameplay Effect to all targets collected by the **Targeting System**.                             |
| **Spawn Actor**                           | Spawns or activates a **Cast Actor**, which collects targets and applies the Cast Gameplay Effect.                 |
| **Wait For Confirmation**                 | Waits for a **Targeting Actor** to collect and confirm targets, then applies the Cast Gameplay Effect.             |
| **Wait For Confirmation And Spawn Actor** | Waits for a **Targeting Actor** to confirm a location, then spawns or activates a **Cast Actor** at that location. |

### Commit Times

For flexibility, the Cast Ability allows you to fine-tune when costs and cooldowns are committed.

| Commit Time           | Description                                                                  |
|-----------------------|------------------------------------------------------------------------------|
| **Ability Activates** | Costs and cooldowns are committed as soon as the Gameplay Ability activates. |
| **Cast Starts**       | Costs and cooldowns are committed when the cast starts.                      |
| **Targets Acquired**  | Costs and cooldowns are committed when targets are acquired.                 |
| **Ability Ends**      | Costs and cooldowns are committed when the ability ends.                     |

### Cast Gameplay Effect

The **Cast Gameplay Effect** is applied to the targets collected by the Cast Ability. This is usually a damage or benefit
effect, but it can be any Gameplay Effect that fits your design.

The number of targets collected by the Cast Ability is available through the `Tag_Combat_Data_CastHits` magnitude tag.

You can further **modify the Gameplay Effect Spec** generated or applied by the Cast Ability. Modifications are usually
done by adding **Dynamic Tags** or **Set By Caller Magnitudes** to the effect, which can be used by **Effect Executions**
or **Modifier Calculations**.

You can extend the following Cast Ability functions for customization:

| Function                             | Description                                                                               |
|--------------------------------------|-------------------------------------------------------------------------------------------|
| `GetDynamicGameplayTags`             | Adds dynamic Gameplay Tags to the effect spec as targets are acquired.                    |
| `GetAdditionalSetByCallerMagnitudes` | Adds or overrides Set By Caller magnitudes in the effect spec.                            |
| `ApplyGameplayEffectToData`          | Provides full control over how the spec is applied to each target. Available only in C++. |

### Confirmation State Gameplay Effect

The **Confirmation State Gameplay Effect** is applied to the owner while the ability is waiting for target confirmation.

Tags granted by this effect can be used to adjust input or AI behavior. For example, the player's Primary Action could
confirm the cast instead of triggering an attack, or a bot could wait briefly before sending a confirmation event.

This effect is removed when targeting is confirmed or cancelled.

### Successful Gameplay Effect

The **Successful Gameplay Effect** is optionally applied to the owner when the cast successfully triggers.

This can be used for cosmetic feedback through Gameplay Cues, or for tags and temporary self-effects that should happen
when the cast starts.

This effect is not removed by the ability, so its duration, stacking, and removal rules are controlled by the Gameplay
Effect itself.

### Extension Points

The Cast Ability provides functions for key internal events. These can be extended when a Cast Flow needs additional logic.

| Function                    | Description                                                                                 |
|-----------------------------|---------------------------------------------------------------------------------------------|
| `HandleDelayFinished`       | Executed when the delay finishes and the ability is ready to start the cast.                |
| `HandleCastStarted`         | Executed when the cast starts, regardless of the selected trigger.                          |
| `HandleTargetsReady`        | Handles targets collected through the Gameplay Targeting System.                            |
| `HandleCastActorReady`      | Handles a Cast Actor that has been initialized but not spawned yet.                         |
| `HandleCastActorSpawned`    | Handles a Cast Actor that has been spawned or activated from the pool.                      |
| `HandleTargetDataConfirmed` | Handles target data confirmed by the Targeting Actor, based on the **Targeting** property.  |
| `HandleTargetDataCancelled` | Handles the cancellation of target selection.                                               |

## Authoring Animations

The Cast Ability expects an **Animation Montage**. The montage can be simple or section-based, depending on how the cast 
is triggered.

For immediate casts, such as casts using **Targeting Presets** or directly spawned **Cast Actors**, you can use a simple 
montage. If the ability is configured to start the cast from a **Gameplay Event**, the montage should include the **Trigger 
Cast** Animation Notify, which sends that event to the ability.

For interactive casts, such as casts using **Ability Targeting Actors**, the montage can include named sections that 
represent the targeting lifecycle. The ability can move between these sections when the cast is waiting for confirmation, 
confirmed, or cancelled.

| Section       | Description                                                                                                                |
|---------------|----------------------------------------------------------------------------------------------------------------------------|
| **Default**   | Entry section where the animation starts. Usually transitions into the **Loop** section.                                   |
| **Loop**      | Looped section that plays while the ability is waiting for target confirmation. Usually transitions into itself.           |
| **Confirmed** | Section played when the cast is confirmed. This name must match the ability's **Section When Confirmed** property.         |
| **Cancelled** | Section played when target selection is cancelled. This name must match the ability's **Section When Cancelled** property. |

> **Montage Section Names**
>
> The relevant **section names are configurable** in the ability, and they must always match the section names 
> authored in the **Animation Montage**.
{style="tip"}

## Cast Requests

The Cast Ability uses **Cast Requests** as data transfer objects between animation, the ability, and the internal cast 
execution tasks.

Cast Requests are usually created by the **Trigger Cast** Animation Notify and sent to the ability through the `Combat.Event.Cast` 
Gameplay Event. The ability reads the request from the event payload and uses it to continue the Cast Flow.

A Cast Request can also contain logic used to spawn or retrieve a Cast Actor, including support for the 
[**Actor Pool**](cbt_actor_pooling.md).

> **Modifying the Cast Actor**
>
> You can **modify the Cast Actor after it is spawned or retrieved** by overriding `ModifyCastActor`, either in Blueprint 
> or C++.
> 
> Keep in mind that the actor may have been retrieved from the pool, so **temporary changes should be reset** before the 
> actor is returned to the pool.
{style="note"}
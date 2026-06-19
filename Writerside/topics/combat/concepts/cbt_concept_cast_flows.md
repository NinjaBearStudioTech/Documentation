# Cast Flows
<primary-label ref="combat"/>

The **Cast Ability** is a flexible Gameplay Ability base for casts that need to be **created**, **placed**, or **triggered**
in the world. It can be used for world-based effects such as explosions, healing zones, hazard pools, meteors, blizzards,
auras, and delayed impacts.

A **Cast Flow** describes how the ability resolves that cast. Each flow uses the same base ability, but changes how targets
are collected and, in some cases, where a Cast Actor is placed.

Cast Flows can use **Targeting Presets**, **Ability Targeting Actors**, **Cast Actor Blueprints**, or a combination of these
systems.

## Ability Targeting Actor

An **Ability Targeting Actor** is used when the cast needs a confirmation step before it resolves. For example, a player
may aim an area on the ground, confirm the location, and then trigger the cast.

You can use any Targeting Actor provided by the Gameplay Ability System. Ninja Combat also provides
`NinjaCombatAbilityTargetingActor`, a generic base class that can collect targets using a Targeting Preset or broadcast its
own location when the actor is only being used for placement.

This class is compatible with the [**Actor Pool**](cbt_concept_actor_pooling.md).

> **Begin Play**
>
> Since the provided Ability Targeting Actor is compatible with the [**Actor Pool**](cbt_concept_actor_pooling.md), it may be
> instantiated before it is actually needed. Do not use `BeginPlay` for startup logic, use the targeting actor activation
> hooks instead.
{style="note"}

## Cast Actor

A **Cast Actor** is used when the ability needs to place an actor in the world. Examples include a lava pool, aura, explosion
volume, meteor marker, lingering hazard, or healing zone.

Use one of the provided `NinjaCombatCastActor` classes as the base class when possible. Cast Actors are compatible with the
[**Actor Pool**](cbt_concept_actor_pooling.md).

The Cast Actor owns the actor lifecycle, collision, and cast event notifications. Specialized gameplay rules are handled by
**Cast Behaviors** hosted by the actor's `NinjaCombatCastBehaviorComponent`.

The following Cast Actor classes are available:

| Cast Actor                    | Description                                       |
|-------------------------------|---------------------------------------------------|
| `NinjaCombatCastActor`        | Base class without a specific collision shape.    |
| `NinjaCombatCastActor_Sphere` | Cast Actor that uses a Sphere collision shape.    |
| `NinjaCombatCastActor_Box`    | Cast Actor that uses a Box collision shape.       |

If you need a different collision type, use `NinjaCombatCastActor` as a starting point and assign the collision component
from your subclass. If you cannot use the provided base classes, any actor that implements `CombatCastInterface` can be
used instead.

> **Begin Play**
>
> Since Cast Actors can be pooled, they may exist before they are used. Avoid using `BeginPlay` for cast startup logic.
> Use the cast lifecycle and Cast Behaviors instead.
{style="note"}

### Cast Lifecycle

Cast Actors separate the **active gameplay lifecycle** from the **actor or pool lifecycle**.

| Lifecycle Step   | Description                                                                                  |
|------------------|----------------------------------------------------------------------------------------------|
| `Activated`      | The Cast Actor becomes active, either from Begin Play or from the Actor Pool.                |
| `Prepared`       | The Cast Actor prepares runtime data before the cast starts.                                 |
| `Started`        | The cast starts affecting the world.                                                         |
| `Overlap Begin`  | Another actor begins overlapping the Cast Actor collision.                                   |
| `Overlap End`    | Another actor stops overlapping the Cast Actor collision.                                    |
| `Effect Applied` | A cast behavior confirms that effects were applied to a target.                              |
| `Effect Removed` | A cast behavior confirms that managed effects were removed from a target.                    |
| `Dissipated`     | The cast reaches the end of its active gameplay lifecycle.                                   |
| `Deactivated`    | The actor is destroyed, hidden, or returned to the Actor Pool.                               |

`Dissipated` and `Deactivated` are deliberately separate. Use **Dissipated** for the end of active gameplay, and
**Deactivated** for final actor or pool cleanup.

## Cast Behaviors

**Cast Behaviors** are instanced objects owned by a `NinjaCombatCastBehaviorComponent`. They receive cast lifecycle events
from the owning Cast Actor and execute in order.

The default Cast Actor behavior stack includes:

| Behavior                             | Purpose                                                   |
|--------------------------------------|-----------------------------------------------------------|
| **Floor Alignment**                  | Places the cast cleanly on the floor when it starts.      |
| **Cast Effect**                      | Applies the cast Gameplay Effect to valid targets.        |
| **Dissipation**                      | Ends the active cast after its configured duration.       |

Optional behaviors can be added when needed:

| Behavior                             | Purpose                                                                       |
|--------------------------------------|-------------------------------------------------------------------------------|
| **Sphere Cone Effect**               | Filters sphere overlaps to a forward-facing cone.                             |
| **Cosmetics**                        | Executes Gameplay Cues for selected cast lifecycle events on clients.         |

Cast Behaviors are intended to make Cast Actors easier to configure and extend without placing every rule directly on the
actor class.

> **Cosmetics**
>
> Cast visuals are usually best handled directly on the Cast Actor with normal components, Blueprints, Niagara Systems,
> decals, sounds, materials, and timelines.
>
> Target impact visuals are usually best handled by Gameplay Cues configured on the Gameplay Effect applied to the target.
> Animation-driven casts can also trigger cosmetics from the animation or montage that starts the cast.
>
> Use the Cast Cosmetics Behavior only when you need lightweight Gameplay Cues tied to cast lifecycle events.
{style="tip"}

## Cast Interface

Any actor used as a Cast Actor must implement `CombatCastInterface`. The interface lets the ability, actor, and behaviors
communicate through a consistent lifecycle. At a high level, the interface supports:

- Binding and unbinding to cast lifecycle events.
- Preparing and starting the cast.
- Registering applied or removed cast effects.
- Dissipating the active cast.
- Providing the Gameplay Effect class and level used by cast behaviors.
- Returning targets confirmed as affected by the cast.

Most projects should use the provided Cast Actor classes instead of implementing the interface from scratch.

## Cast Ability

The **Cast Ability** coordinates the full Cast Flow. Depending on its configuration, it can collect targets directly, wait
for target confirmation, spawn a Cast Actor, or combine targeting and spawning into the same flow.

### Cast Triggers

Once the ability activates, it may wait for a specific trigger before starting the cast.

| Trigger                | Description                                                                                                             |
|------------------------|-------------------------------------------------------------------------------------------------------------------------|
| **Ability Activation** | The cast starts immediately, as soon as the Gameplay Ability activates.                                                 |
| **Gameplay Event**     | The cast starts when the ability receives the `Combat.Event.Cast` Gameplay Event.                                       |
| **Delayed**            | The cast starts after a configured delay. This is intended for non-interactive flows.                                   |

### Targeting Modes

The Cast Ability supports multiple targeting modes for different usage scenarios.

| Targeting                                 | Description                                                                                            |
|-------------------------------------------|--------------------------------------------------------------------------------------------------------|
| **Targeting System**                      | Applies the Cast Gameplay Effect to targets collected by the Targeting System.                         |
| **Spawn Actor**                           | Spawns or activates a Cast Actor. The actor and its behaviors handle target collection and effects.    |
| **Wait For Confirmation**                 | Waits for a Targeting Actor to collect and confirm targets, then applies the Gameplay Effect.          |
| **Wait For Confirmation And Spawn Actor** | Waits for a Targeting Actor to confirm placement, then spawns or activates a Cast Actor.               |

### Commit Times

For flexibility, the Cast Ability allows you to choose when costs and cooldowns are committed.

| Commit Time           | Description                                                                  |
|-----------------------|------------------------------------------------------------------------------|
| **Ability Activates** | Costs and cooldowns are committed as soon as the Gameplay Ability activates. |
| **Cast Starts**       | Costs and cooldowns are committed when the cast starts.                      |
| **Targets Acquired**  | Costs and cooldowns are committed when targets are acquired.                 |
| **Ability Ends**      | Costs and cooldowns are committed when the ability ends.                     |

### Cast Gameplay Effect

The **Cast Gameplay Effect** is applied to targets collected by the cast. This is usually a damage or benefit effect, but it
can be any Gameplay Effect that fits your design.

The Cast Ability applies the effect directly when using:

- **Targeting System**
- **Wait For Confirmation**

When using a Cast Actor flow, the Cast Actor and its behaviors handle effect application instead. This lets actor-based
casts own their world presence, collision, duration, and target interactions.

The number of targets collected by direct ability-applied casts is available through the `Tag_Combat_Data_CastHits`
magnitude tag.

### Combat Magnitudes

Cast Actors, projectiles, weapons, owners, instigators, and other effect sources can provide additional Set By Caller
magnitudes through `CombatMagnitudeProviderInterface`.

This allows project-specific data such as damage, poise damage, scaling values, or other magnitudes to be supplied by the
source of the effect without duplicating effect setup across abilities and actors.

### Confirmation State Gameplay Effect

The **Confirmation State Gameplay Effect** is applied to the owner while the ability is waiting for target confirmation.

Tags granted by this effect can be used to adjust input or AI behavior. For example, the player's Primary Action could
confirm the cast instead of triggering an attack.

This effect is removed when targeting is confirmed or cancelled.

### Successful Gameplay Effect

The **Successful Gameplay Effect** is optionally applied to the owner when the cast successfully triggers.

This can be used for feedback, tags, temporary self-effects, or Gameplay Cues that should happen when the cast starts. Its
duration, stacking, and removal rules are controlled by the Gameplay Effect itself.

## Authoring Animations

The Cast Ability expects an **Animation Montage**. The montage can be simple or section-based, depending on how the cast is
triggered.

If the ability starts the cast from a **Gameplay Event**, the montage should include the **Trigger Cast** Animation Notify,
which sends that event to the ability.

For interactive casts, such as casts using Ability Targeting Actors, the montage can include sections for targeting,
confirmation, and cancellation.

| Section       | Description                                                                                                        |
|---------------|--------------------------------------------------------------------------------------------------------------------|
| **Default**   | Entry section where the animation starts.                                                                          |
| **Loop**      | Looped section that plays while the ability is waiting for target confirmation.                                    |
| **Confirmed** | Section played when the cast is confirmed.                                                                         |
| **Cancelled** | Section played when target selection is cancelled.                                                                 |

> **Montage Section Names**
>
> The relevant section names are configurable in the ability, and they must match the section names authored in the
> Animation Montage.
{style="tip"}

## Cast Requests

The Cast Ability uses **Cast Requests** as data transfer objects between animation, the ability, and cast execution.

Cast Requests are usually created by the **Trigger Cast** Animation Notify and sent to the ability through the
`Combat.Event.Cast` Gameplay Event. The ability reads the request from the event payload and uses it to continue the Cast
Flow.

A Cast Request can also contain logic used to spawn or retrieve a Cast Actor, including support for the
[**Actor Pool**](cbt_concept_actor_pooling.md).

> **Modifying the Cast Actor**
>
> You can modify the Cast Actor after it is spawned or retrieved by overriding `ModifyCastActor`, either in Blueprint or
> C++.
>
> Keep in mind that the actor may have been retrieved from the pool, so temporary changes should be reset before the actor
> is returned to the pool.
{style="note"}

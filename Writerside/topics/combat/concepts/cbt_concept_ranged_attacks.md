# Ranged Attacks
<primary-label ref="combat"/>

Ranged Combat in Ninja Combat is built around **three main pieces**:

1. A **Projectile Request** that describes which projectile should be spawned and how it should be initialized.
2. A **Projectile Actor** that owns the projectile lifecycle and broadcasts projectile events.
3. A **Launch Projectile Ability** that receives or creates requests, spawns projectiles, and starts their launch.

Most ranged attacks are driven by **Animation Montages**. During the montage, a **Launch Projectile Animation Notify**
can create a Projectile Request and send it to the active Launch Projectile Ability. The ability then spawns the projectile,
prepares it, and launches it through the projectile interface.

> **Firearms are a separate module**
>
> Ranged combat originally means projectile-based combat such as "fireballs" and "grenades". It includes projectile
> variations, such as bouncing projectiles, explosive projectiles, "homing projectiles" and so on.
>
> For information on firearms, please check the [**Firearms Page**](cbt_concept_firearms.md).
> {style="note"}

## Projectile Requests

A **Projectile Request** is the transfer object used to spawn a projectile. It contains the projectile class, spawn data,
instigator information, launch source, and any project-specific data needed by the projectile or its components.

Projectile Requests can be created in different ways:

| Source                     | Description                                                                  |
|----------------------------|------------------------------------------------------------------------------|
| **Animation Notify**       | Creates a request during an Animation Montage and sends it to the ability.   |
| **Ability Activation**     | The ability creates its own request as soon as it activates.                 |
| **Delayed Ability Launch** | The ability waits for a configured delay, then creates its own request.      |
| **Custom Gameplay Event**  | A project-specific event provides a fully configured request to the ability. |

Event-based projectile launches are expected to provide a valid Projectile Request. When the Launch Projectile Ability is
configured to launch from a Gameplay Event, receiving no request is treated as an invalid setup instead of silently creating
a fallback request.

> **Event-driven launches**
>
> Event-driven launches are useful when the Animation Notify, weapon, or combatant must decide the projectile class,
> launch source, or request data. Ability-driven launches are useful for simpler attacks where the ability owns the full
> projectile setup.
> {style="tip"}

## Projectile Actors

A **Projectile Actor** owns the projectile lifecycle. It implements the Projectile Interface and exposes a small API used
by abilities, components, and pooling systems.

The standard lifecycle is:

| Event           | Description                                                                  |
|-----------------|------------------------------------------------------------------------------|
| **Activated**   | The projectile has entered an active lifecycle.                              |
| **Setup**       | The projectile is preparing launch data, ignored actors, and component data. |
| **Launch**      | The projectile has started movement.                                         |
| **Hit**         | The projectile reported a raw contact with another object.                   |
| **Bounce**      | The projectile bounced and reported bounce data.                             |
| **Impact**      | The projectile confirmed a gameplay impact, usually after applying effects.  |
| **Exhausted**   | The projectile stopped acting as an active gameplay projectile.              |
| **Deactivated** | The projectile is being cleaned up before pool reuse.                        |

The projectile actor broadcasts these events to its projectile components. This allows the actor to stay focused on
lifecycle, while components decide what each event means for launch behavior, hit processing, bouncing, exhaustion,
blasts, or cosmetics.

> **Hit vs. Impact**
>
> A **Hit** is a raw contact reported by the projectile. An **Impact** is a confirmed gameplay result, usually after the
> hit processor accepts the hit and successfully applies a Gameplay Effect.
>
> This distinction allows a projectile to bounce, scan, or overlap many objects without treating every contact as a
> successful gameplay impact.
> {style="tip"}

### Projectile Interface

The **Projectile Interface**, `CombatProjectileInterface`, exposes the public API used by abilities and components. Common
functions include:

| Function                | Description                                                                             |
|-------------------------|-----------------------------------------------------------------------------------------|
| `PrepareLaunch`         | Prepares the projectile before launch. Safe to call more than once for the same launch. |
| `Launch`                | Starts the projectile launch lifecycle and broadcasts the launch event.                 |
| `ApplyVelocity`         | Applies velocity to the projectile movement component.                                  |
| `RegisterProjectileHit` | Reports a raw projectile hit.                                                           |
| `RegisterConfirmedHit`  | Reports a confirmed gameplay impact after effects have been applied.                    |
| `Exhaust`               | Stops the projectile as an active gameplay projectile.                                  |
| `GetSpeed`              | Provides the projectile's current movement speed.                                       |
| `GetInitialSpeed`       | Provides the projectile's configured launch speed.                                      |
| `GetImpactEffectClass`  | Provides the Gameplay Effect used by the default hit processor.                         |
| `GetImpactEffectLevel`  | Provides the level used when creating the impact Gameplay Effect.                       |
| `GetDamage`             | Optionally provides a damage value as a Set By Caller magnitude.                        |
| `GetPoiseConsumption`   | Optionally provides a poise consumption value as a Set By Caller magnitude.             |
| `GetActorsHit`          | Provides actors that have received confirmed impacts from this projectile.              |

The interface is intentionally high-level. More specific behavior, such as bounce response, scan rules, blast targeting,
or cosmetics, is handled by projectile components.

## Projectile Components

Projectile behavior is built through components. A projectile can use only the components it needs, which allows simple
arrows, homing missiles, bouncing projectiles, grenades, and blast projectiles to share the same core lifecycle.

### Launch Components

A **Launch Component** reacts to the projectile launch event and applies the projectile's initial velocity.

The default launch component launches the projectile forward using the projectile's initial speed. Specialized launch
components can calculate a target location before launch and rotate the projectile toward that location.

Common launch variants include:

| Component            | Description                                                            |
|----------------------|------------------------------------------------------------------------|
| **Launch Component** | Launches the projectile forward.                                       |
| **Launch Location**  | Launches the projectile toward a stored or calculated world location.  |
| **Launch Camera**    | Launches the projectile toward the owning player's camera center.      |
| **Launch Targeting** | Uses the Targeting System to select a launch location or target actor. |

A targeting launch can also enable projectile movement homing when a target actor is selected.

> **Launch preparation**
>
> `PrepareLaunch` is separated from `Launch` so the projectile can resolve ignored actors, setup data, targeting data, or
> launch locations before movement begins. This is especially useful for pooled projectiles and projectiles launched from
> Animation Notifies.
> {style="tip"}

### Scan Component

A **Projectile Scan Component** scans the projectile path between frames and reports raw hits to the projectile.

This is useful for fast-moving projectiles where relying only on movement collision can miss targets. The scan component
does not apply damage by itself. It only detects hits and reports them through `RegisterProjectileHit`.

The projectile's hit processor, exhaustion policy, cosmetics, and blast components can then respond to the reported hit.

### Hit Processor Component

A **Hit Processor Component** listens for raw projectile hits and decides whether they should become confirmed impacts.

The default hit processor can:

* Apply a hit policy, such as hitting each actor once.
* Adjust hit results from simple collision to mesh collision.
* Create target data from the accepted hit.
* Apply the projectile's impact Gameplay Effect.
* Add dynamic tags and Set By Caller magnitudes.
* Register confirmed impacts back to the projectile.

Common hit policies include:

| Hit Policy              | Description                                                           |
|-------------------------|-----------------------------------------------------------------------|
| **Always Hit**          | Every reported hit can be accepted.                                   |
| **Hit Once Ever**       | Each actor can only be accepted once during the projectile lifecycle. |
| **Hit Once Per Bounce** | Each actor can be accepted once per bounce or trajectory generation.  |

> **Confirmed impacts**
>
> The default hit processor only records accepted hits after the Gameplay Effect is successfully applied. This means
> `GetActorsHit` represents actors affected by the projectile, not every object touched by raw collision.
> {style="note"}

### Bounce Component

A **Bounce Component** listens for projectile bounce events and can override the projectile's next travel direction.

The default Projectile Movement Component can handle natural bouncing by itself. The Bounce Component is useful when a
projectile needs extra behavior after a bounce, such as reflecting manually, selecting a new target, or enabling homing.

Common bounce response modes include:

| Response Mode                    | Description                                                             |
|----------------------------------|-------------------------------------------------------------------------|
| **Natural**                      | Lets the Projectile Movement Component continue naturally.              |
| **Reflection**                   | Applies a reflected velocity from the impact normal.                    |
| **Target Next Actor**            | Redirects the projectile toward a selected target.                      |
| **Target Next Actor and Homing** | Redirects the projectile and enables homing toward the selected target. |

The Bounce Component does not own exhaustion policy. If a projectile should expire after a certain bounce condition, that
should be handled by the exhaustion component or by a custom component.

### Exhaustion Component

An **Exhaustion Component** decides when a projectile should stop being active.

Exhaustion is different from deactivation. Exhaustion means the projectile stops acting as a gameplay projectile: movement
can stop, collision can be disabled, and exhaustion events can trigger final effects. Deactivation is used for pool cleanup
before reuse.

Common exhaustion triggers include:

| Trigger    | Description                                                |
|------------|------------------------------------------------------------|
| **Manual** | The projectile only exhausts when explicitly told to.      |
| **Hit**    | The projectile exhausts after a raw hit.                   |
| **Impact** | The projectile exhausts after a confirmed gameplay impact. |
| **Bounce** | The projectile exhausts after a bounce event.              |
| **Timer**  | The projectile exhausts after a timer started on launch.   |

> **Exhaustion before deactivation**
>
> If a pooled projectile is deactivated before it has exhausted, the projectile can force exhaustion first. This ensures
> final exhaustion events still run before the projectile is cleaned up for reuse.
> {style="note"}

### Blast Components

A **Blast Component** applies area or multi-target effects when the projectile reaches a configured trigger.

Blast triggers can include raw hits, confirmed impacts, exhaustion, or a timer. The base blast component owns the shared
pipeline, while subclasses decide how targets are collected.

The blast pipeline usually works like this:

1. The projectile emits the configured trigger event.
2. The blast component collects target data.
3. The blast component creates an outgoing Gameplay Effect spec.
4. The blast effect is applied to collected targets.
5. A blast Gameplay Cue is executed.
6. Confirmed blast impacts are optionally registered back to the projectile.

Common blast variants include:

| Component           | Description                                                               |
|---------------------|---------------------------------------------------------------------------|
| **Blast Sphere**    | Collects targets using a radial sphere scan or overlap plus confirmation. |
| **Blast Targeting** | Uses the Targeting System to collect blast targets with richer rules.     |

Sphere blasts work well for grenades, fireballs, explosive arrows, shockwaves, and similar effects. Targeting-based blasts
are useful when target collection needs team filtering, sorting, line-of-sight rules, cone checks, or other gameplay-specific
filters.

## Launch Projectile Ability

The **Launch Projectile Ability** is responsible for starting ranged attacks that spawn projectiles.

Depending on its configuration, the ability can launch a projectile:

| Trigger                | Description                                                           |
|------------------------|-----------------------------------------------------------------------|
| **Ability Activation** | Creates and launches a projectile immediately.                        |
| **Gameplay Event**     | Waits for a gameplay event that provides a Projectile Request.        |
| **Delayed**            | Waits for a configured delay, then creates and launches a projectile. |

The ability can also control when cost and cooldown are committed:

| Commit Time             | Description                                                         |
|-------------------------|---------------------------------------------------------------------|
| **Ability Activates**   | Cost and cooldown are committed when the ability starts.            |
| **Projectile Launches** | Cost and cooldown are committed when the projectile is launched.    |
| **Ability Ends**        | Cost and cooldown are committed when the ability ends successfully. |

When the projectile is ready, the ability calls the projectile API to prepare and launch it. This keeps the ability focused
on orchestration, while the projectile and its components own the actual projectile behavior.

> **Projectile effects**
>
> Projectile impact effects are handled by projectile components, not by the Attack Ability. The ability creates or receives
> a Projectile Request, spawns the projectile, and launches it. The projectile's hit processor and blast components decide
> how Gameplay Effects are applied.
> {style="tip"}

## Animation Notify

The **Launch Projectile Animation Notify** is the most common way to launch projectiles from attack animations.

The Animation Notify creates a Projectile Request and sends it through a Gameplay Event to the active Launch Projectile Ability. 
This allows the animation to define the exact frame where the projectile should be spawned or launched, while still letting 
the ability manage the overall attack lifecycle.

Animation-driven projectile launches are useful for:

* Throwing a projectile at the release frame.
* Spawning a magic projectile after a casting gesture.
* Launching from a weapon socket.
* Coordinating projectile launch with montage sections or combo steps.
* Passing attack-specific request data into the projectile spawn pipeline.

## Cosmetics

Ranged cosmetics are handled through **Gameplay Cues** and projectile events.

A projectile can map lifecycle events such as `Launch`, `Hit`, `Impact`, `Bounce`, `Exhausted`, and `Deactivated` to one or
more Gameplay Cues. This allows projectiles to trigger trails, muzzle flashes, impacts, bounces, explosions, final bursts,
or cleanup effects without hardcoding Niagara Systems or sounds directly into the projectile actor.

Blast components can also execute their own blast Gameplay Cue. This cue represents the blast occurrence itself, not each
individual target affected by the blast.

> **Gameplay Cue routing**
>
> Projectile cosmetics are event-driven. Use projectile event cues for lifecycle cosmetics, Gameplay Effects for target
> impact cosmetics, and blast cues for area effects.
> {style="tip"}

## Common Projectile Setups

Different projectiles can be built by combining the same components in different ways:

| Projectile Type         | Common Components                                                               |
|-------------------------|---------------------------------------------------------------------------------|
| **Simple Arrow**        | Launch Component, Hit Processor, Exhaustion on Impact, Cosmetics.               |
| **Fast Projectile**     | Launch Component, Scan Component, Hit Processor, Exhaustion on Impact.          |
| **Bouncing Projectile** | Launch Component, Bounce Component, Hit Processor, Exhaustion policy.           |
| **Homing Projectile**   | Launch Targeting Component, Hit Processor, Exhaustion policy, Cosmetics.        |
| **Grenade**             | Launch Component, Exhaustion Timer, Blast on Exhaustion, Blast Sphere.          |
| **Fireball**            | Launch Location or Camera Component, Hit Processor, Blast on Impact, Cosmetics. |

Most projects can start with the default projectile actor and default components, then add custom subclasses only when
target selection, filtering, movement response, or effect application needs project-specific rules.

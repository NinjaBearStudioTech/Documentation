# Ranged Attacks
<primary-label ref="combat"/>

Ranged Combat in Ninja Combat is built around **projectile-based attacks** such as fireballs, arrows, grenades, magic bolts,
and other spawned projectiles.

Most ranged attacks use four pieces:

1. A **Projectile Request** that describes which projectile should be spawned and how it should be initialized.
2. A **Projectile Actor** that owns the projectile lifecycle, collision, movement, and public projectile API.
3. A **Projectile Behavior Component** that owns the projectile's ordered behavior stack.
4. A **Launch Projectile Ability** that receives or creates requests, spawns projectiles, and starts the launch.

Most ranged attacks are driven by **Animation Montages**. During the montage, a **Launch Projectile Animation Notify** can
create a Projectile Request and send it to the active Launch Projectile Ability. The ability then spawns the projectile,
prepares it, and launches it.

> **Firearms are a separate module**
>
> Ranged combat here refers to projectile-based combat such as fireballs, arrows, grenades, bouncing projectiles, explosive
> projectiles, and homing projectiles.
>
> For information on firearms, please check the [**Firearms Page**](cbt_concept_firearms.md).
{style="note"}

## Projectile Requests

A **Projectile Request** is the transfer object used to spawn a projectile. It contains the projectile class, spawn data,
instigator information, launch source, and any project-specific data needed by the projectile or its behaviors.

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
{style="tip"}

## Projectile Actors

A **Projectile Actor** owns the core projectile lifecycle. It implements the Projectile Interface and exposes the public API
used by abilities, behaviors, and pooling systems.

The actor owns the physical projectile pieces, such as collision and projectile movement. Specialized gameplay logic is
handled by instanced **Projectile Behaviors** owned by the actor's **Projectile Behavior Component**.

The standard lifecycle is:

| Event           | Description                                                                 |
|-----------------|-----------------------------------------------------------------------------|
| **Activated**   | The projectile has entered an active lifecycle.                             |
| **Setup**       | The projectile is preparing launch data and runtime context.                |
| **Launch**      | The projectile has started movement.                                        |
| **Hit**         | The projectile reported a raw contact with another object.                  |
| **Bounce**      | The projectile bounced and reported bounce data.                            |
| **Impact**      | The projectile confirmed a gameplay impact.                                 |
| **Exhausted**   | The projectile stopped acting as an active gameplay projectile.             |
| **Deactivated** | The projectile is being cleaned up before pool reuse.                       |

> **Hit vs. Impact**
>
> A **Hit** is a raw contact reported by the projectile. An **Impact** is a confirmed gameplay result, usually after the hit
> processor accepts the hit and successfully applies a Gameplay Effect.
{style="tip"}

### Projectile Interface

The **Projectile Interface**, `CombatProjectileInterface`, exposes the public API used by abilities, behaviors, and other
combat systems that interact with a projectile.

At a high level, the interface supports:

- Binding and unbinding projectile event listeners.
- Preparing and launching the projectile.
- Applying movement velocity.
- Reporting raw hits and confirmed impacts.
- Exhausting the projectile.
- Providing current speed, initial speed, impact Gameplay Effect, impact effect level, and impact strength.
- Returning actors confirmed as affected by the projectile.

The interface is the main contract for projectile actors. More specific behavior, such as launch targeting, scan rules,
hit filtering, bounce response, blasts, exhaustion, or cosmetics, is still handled by projectile behaviors.

## Projectile Behaviors

Projectile gameplay is built through instanced **Projectile Behaviors**. A projectile can use only the behaviors it needs, 
which allows simple arrows, homing missiles, bouncing projectiles, grenades, and blast projectiles to share the same core lifecycle.

Projectile Behaviors are owned by the **Projectile Behavior Component**. The component receives projectile lifecycle events 
from the actor and forwards them to each behavior in order.

The default projectile actor creates a Projectile Behavior Component with a standard behavior stack, but additional behaviors 
can be added by projectile subclasses or Blueprint defaults.

| Behavior          | Added by Default | Purpose                                                                                                                 |
|-------------------|------------------|-------------------------------------------------------------------------------------------------------------------------|
| **Launch**        | Yes              | Applies the initial projectile velocity and supports normal, targeted, camera-guided, or homing launches.               |
| **Hit Processor** | Yes              | Converts accepted raw hits into confirmed gameplay impacts.                                                             |
| **Scan**          | Yes              | Scans the projectile path between frames and reports raw hits, helping fast projectiles detect missed targets.          |
| **Exhaustion**    | Yes              | Decides when the projectile stops acting as active gameplay, such as after an impact, bounce, or timer.                 |
| **Cosmetics**     | Yes              | Routes projectile lifecycle events to Gameplay Cues on non-dedicated servers.                                           |
| **Bounce**        | No               | Handles custom behavior after bouncing, such as redirecting the projectile or selecting a new target.                   |
| **Blast**         | No               | Applies area or multi-target effects triggered by impact, exhaustion, timer, or other projectile events.                |
| **Z Lock**        | No               | Keeps the projectile at a fixed Z location relative to its instigator, or maintains its initial Z during its lifecycle. |

> **Exhaustion before deactivation**
>
> Exhaustion means the projectile stops acting as an active gameplay projectile. Deactivation is final actor or pool
> cleanup. Keeping these separate allows final gameplay and cosmetic events to run before the projectile is reused.
{style="note"}

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

When the projectile is ready, the ability prepares and launches it. This keeps the ability focused on orchestration, while
the projectile and its behaviors own the actual projectile behavior.

> **Projectile effects**
>
> Projectile impact effects are handled by projectile behaviors, not by the Attack Ability. The ability creates or receives
> a Projectile Request, spawns the projectile, and launches it. The projectile's behaviors decide how Gameplay Effects are
> applied.
{style="tip"}

## Animation Notify

The **Launch Projectile Animation Notify** is the most common way to launch projectiles from attack animations.

The Animation Notify creates a Projectile Request and sends it through a Gameplay Event to the active Launch Projectile
Ability. This allows the animation to define the exact frame where the projectile should be spawned or launched, while still
letting the ability manage the overall attack lifecycle.

Animation-driven projectile launches are useful for:

- Throwing a projectile at the release frame.
- Spawning a magic projectile after a casting gesture.
- Launching from a weapon socket.
- Coordinating projectile launch with montage sections or combo steps.
- Passing attack-specific request data into the projectile spawn pipeline.

## Gameplay Effects

Projectile impact effects are usually applied by projectile behaviors, such as the Hit Processor or Blast behaviors. The
projectile provides the Gameplay Effect class and level used for its impact, while the behavior decides when that effect
should be applied.

## Custom Damage

Normally, projectile damage is defined by the Gameplay Effect itself. The Combat Damage Execution can calculate damage
from the source's **Base Damage** attribute, modifiers applied to that attribute, target defenses, mitigation, and any other
game-specific combat rules.

A projectile or another effect source can override values used by the damage execution by providing Set By Caller
magnitudes before the Gameplay Effect is applied. The most common combat magnitudes are:

| Tag                       | Description                                              |
|---------------------------|----------------------------------------------------------|
| `Combat.Data.Damage`      | Overrides or provides the pending damage value.          |
| `Combat.Data.PoiseDamage` | Overrides or provides the poise damage applied by a hit. |

These values can be injected through the combat magnitude provider function/interface used by the damage pipeline. This
keeps damage values close to the projectile or source that owns them, while still letting the Gameplay Effect and Combat
Damage Execution handle the final calculation.

The base projectile actor already implements this behavior, so projects can set projectile damage and poise damage on the
projectile defaults without creating a custom behavior just to provide common damage magnitudes.

## Cosmetics

Ranged cosmetics are handled through **Gameplay Cues** and projectile events.

A projectile behavior can map lifecycle events such as `Launch`, `Hit`, `Impact`, `Bounce`, `Exhausted`, and `Deactivated`
to one or more Gameplay Cues. This allows projectiles to trigger trails, muzzle flashes, impacts, bounces, explosions,
final bursts, or cleanup effects without hardcoding Niagara Systems or sounds directly into the projectile actor.

Blast behaviors can also execute their own blast Gameplay Cue. This cue represents the blast occurrence itself, not each
individual target affected by the blast.

> **Gameplay Cue routing**
>
> Use projectile event cues for projectile lifecycle cosmetics, Gameplay Effects for target impact cosmetics, and blast
> cues for area effects.
{style="tip"}

## Common Projectile Setups

Different projectiles can be built by combining the same behaviors in different ways:

| Projectile Type         | Common Behaviors                                                               |
|-------------------------|--------------------------------------------------------------------------------|
| **Simple Arrow**        | Launch, Hit Processor, Exhaustion, Cosmetics.                                  |
| **Fast Projectile**     | Launch, Scan, Hit Processor, Exhaustion.                                       |
| **Bouncing Projectile** | Launch, Bounce, Hit Processor, Exhaustion.                                     |
| **Homing Projectile**   | Targeted Launch, Hit Processor, Exhaustion, Cosmetics.                         |
| **Grenade**             | Launch, Timed Exhaustion, Blast, Cosmetics.                                    |
| **Fireball**            | Targeted Launch, Hit Processor, Blast, Cosmetics.                              |

Most projects can start with the default projectile actor and default behavior stack, then add custom behavior subclasses
only when target selection, filtering, movement response, or effect application needs project-specific rules.

# Melee Combat
<primary-label ref="combat"/>

Melee Combat in Ninja Combat is built around **three main pieces**:

1. A **Melee Scan** that detects targets during an attack.
2. A **combatant** or **weapon** that implements the **Melee Interface**.
3. A **Melee Attack Ability** that starts scans, receives scan results, and applies damage.

Most melee attacks are driven by **Animation Montages**. During the montage, one or more **Melee Scan Animation Notify
States** open scan windows, create scan instances, and send them to the active Melee Attack Ability.

## Melee Scans

Melee Scans **detect targets** during a melee attack. They are usually **opened and closed by animation**, using the
**Melee Scan Animation Notify State**. A melee scan is created from **Melee Scan Request Data**, which defines:

| Property                   | Description                                                                                           |
|----------------------------|-------------------------------------------------------------------------------------------------------|
| **Source**                 | Determines whether the scan comes from the ability owner or from an equipped weapon.                  |
| **Scan Mode**              | Defines how the scan is performed, such as line traces, shape sweeps, or component overlaps.          |
| **Weapon Query**           | Finds the source weapon when the scan source is weapon-based.                                         |
| **Component Tag**          | Selects a specific mesh or scene component from the melee source when multiple are available.         |
| **Scan Socket Prefix**     | Identifies the sockets used to perform the scan.                                                      |
| **Scan Channels**          | Defines which collision object types can be detected by the scan.                                     |
| **Melee Hit Override**     | Optional Gameplay Effect that overrides the effect provided by the interface or Melee Attack Ability. |
| **Melee Scan Class**       | Defines the runtime scan object responsible for scan behavior and target filtering.                   |
| **Melee Scan Tags**        | Adds traits to the scan, which can be used by other gameplay systems.                                 |
| **Trail Gameplay Cue Tag** | Gameplay Cue added while the scan is active and removed when the scan ends.                           |

> **Scan Sockets**
>
> Socket-based scans use sockets from the source mesh. These sockets should follow a shared prefix, such as `sScan`, and
> a sortable suffix, such as `sScan_01`, `sScan_02`, and `sScan_03`.
>
> The same sockets can also be reused by weapon trails, unless the trail setup uses a different socket prefix.
{style="tip"}

The **scan mode** controls how targets are detected:

| Scan Mode             | Description                                                                   |
|-----------------------|-------------------------------------------------------------------------------|
| **Line Trace**        | Performs traces across sockets and between their positions on each frame.     |
| **Box Sweep**         | Performs a box-shaped sweep between previous and current frame positions.     |
| **Capsule Sweep**     | Performs a capsule-shaped sweep between previous and current frame positions. |
| **Sphere Sweep**      | Performs a sphere-shaped sweep between previous and current frame positions.  |
| **Component Overlap** | Hits targets that overlap with the selected component while the scan is open. |

The **source** object is expected to implement the **Melee Interface**, `CombatMeleeInterface`. This allows the combat system
to retrieve the proper **Mesh or Shape Components** used for socket-based, shape-based, and component overlap setups.

### Melee Scan Animation Notify State

The **Melee Scan Animation Notify State** owns Melee Scan Request Data and creates a runtime `NinjaCombatMeleeScan` when
the scan window opens. The runtime scan is sent to the active ability through the melee scan Gameplay Event payload.

Existing notify assets can continue using the legacy individual properties. New assets should use the Request Data
property directly. Both paths produce the same request data before the runtime scan is created.

## Melee Interface

The **Melee Interface**, `CombatMeleeInterface`, exposes the data and objects required by Melee Scans and melee damage
processing. This interface was implemented by the **Owner** during [**Combat First Steps**](cbt_first_steps.md). The
**base Weapon Actor** already implements this interface.

The interface exposes the mesh or shape component used for scans, the Gameplay Effect used for hits, and the cosmetic
hooks used by melee trails and impact effects.

| Function                      | Description                                                                                                                                                                       |
|-------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `GetMeleeMesh`                | Provides the main mesh component that represents the melee source. By default, finds a mesh component tagged with `Combat.Component.MeleeScanSource`.                             |
| `GetMeleeMeshByTag`           | Provides the main mesh component that represents the melee source, filtered by a Gameplay Tag. Returns no component when the tag is invalid.                                      |
| `GetMeleeOverlap`             | Provides the shape component used for collision overlaps. By default, finds a shape component tagged as the melee scan overlap source.                                            |
| `GetMeleeOverlapByTag`        | Provides the shape component used for collision overlaps, filtered by a Gameplay Tag. Returns no component when the tag is invalid.                                               |
| `GetHitEffectClass`           | Provides the Gameplay Effect applied when the source hits a target. This is optional and can be provided by the Melee Attack Ability instead.                                     |
| `GetHitEffectLevel`           | Provides the Gameplay Effect level used when applying this interface's Effect Class. Returning zero or lower discards this value and uses the Melee Attack Ability value instead. |
| `GetAttackTrails`             | Provides Niagara Components used as attack trails. By default, returns Niagara Components tagged as weapon trails.                                                                |
| `GetMeleeHitPhysicalStrength` | Provides the strength of the melee hit, for physical animations. Defaults to `10000`.                                                                                             |
| `GetImpactTrails`             | Provides Niagara Components used as impact trails. By default, returns Niagara Components tagged as impact trails.                                                                |
| `StartMeleeTrailsCosmetics`   | Starts rendering melee trails, considering the current tags. This is cosmetic-only and has an empty default implementation.                                                       |
| `StopMeleeTrailsCosmetics`    | Stops rendering melee trails, considering the current tags. This is cosmetic-only and has an empty default implementation.                                                        |
| `HandleMeleeDamageCosmetics`  | Allows the melee source to react to melee damage that has been applied to a target. This is cosmetic-only and has an empty default implementation.                                |

> **Gameplay Effect Priority**
>
> A hit Gameplay Effect can be defined by the Melee Attack Ability, the Melee Interface, or the Melee Scan. When more than one
> is available, they are selected in this order:
>
> **Melee Scan > Melee Interface > Melee Attack Ability**
{style="tip"}

### Combatant Sources

Combatants can be used directly as melee sources for unarmed attacks, creature attacks, claws, tails, or any attack where
the scan source belongs to the character instead of an equipped weapon.

Owner-based scans use the ability owner as the source, so they do not require a Weapon Query. The combatant should
provide the mesh or overlap component used by the scan, and may also handle its own melee cosmetics.

### Weapon Sources

Weapons are the most common melee scan source. A weapon provides the mesh or overlap component used by the scan, the
sockets that define socket-based traces or sweeps, and the cosmetic data used for trails and impacts.

Weapon-based scans retrieve their source through the Weapon Manager, using the Weapon Query defined in the Melee Scan.
The base `NinjaCombatWeaponActor` already implements the Melee Interface and exposes common melee properties.

## Melee Attack Ability

The **Melee Attack Ability**, `CombatAbility_MeleeAttack`, is responsible for executing melee attacks and processing scan
results.

For animation-driven attacks, the ability usually plays an Animation Montage and listens for Melee Scan events generated
by notify states. When a scan starts, the notify state creates a runtime `NinjaCombatMeleeScan` and sends it through a
Gameplay Event. The ability requires event-based scans to provide this runtime scan in the event payload.

The ability can also create its own melee scan without an animation notify. This is useful for attacks that should scan
immediately when the ability starts, or after a simple delay.

| Trigger                | Description                                                                                        |
|------------------------|----------------------------------------------------------------------------------------------------|
| **Ability Activation** | Creates a melee scan from the ability's default request data as soon as the ability starts.        |
| **Gameplay Event**     | Waits for a Melee Scan event and requires the payload to include a valid runtime melee scan.       |
| **Delayed**            | Waits for the activation delay, then creates a melee scan from the ability's default request data. |

The ability can commit its cost and cooldown at different moments:

| Commit Time           | Description                                          |
|-----------------------|------------------------------------------------------|
| **Ability Activates** | Commits as soon as the ability activates.            |
| **Melee Scan Starts** | Commits when a valid melee scan is ready to start.   |
| **Targets Acquired**  | Commits only after the scan finds valid target data. |
| **Ability Ends**      | Commits when the ability ends successfully.          |

When the ability creates its own scan, it uses **Default Melee Scan Request** and **Melee Scan Duration**. The request data
contains the scan setup, while the combat system resolves runtime objects such as the weapon, mesh, overlap component, sockets,
and causer.

> **Event-Based Scans**
>
> Event-based melee attacks do not create a fallback scan from the ability. The event payload must include a valid
> `NinjaCombatMeleeScan`, usually created by a Melee Scan Animation Notify State.
{style="note"}

The hit Gameplay Effect can come from the ability, the melee source, or the scan itself. This allows broad defaults at the
ability level, source-specific hit effects from the Melee Interface, and attack-specific overrides at the scan level.

The Melee Attack Ability also provides debug options that can display scan paths and hit targets, which is useful when
tuning socket placement, scan timing, and collision channels.

> **Ability-Level Defaults**
>
> Define common attack behavior in the **Melee Attack Ability**. Use the **Melee Interface** for source-specific scan,
> effect, and cosmetic data. Use the **Melee Scan Request Data** for attack-specific scan setup, such as left and right hand attacks.
{style="tip"}

## Custom Damage

Melee damage is usually defined by the Gameplay Effect applied by the Melee Attack Ability. In the default combat damage
flow, the **Combat Damage Execution** can calculate damage from values such as the source's Base Damage Attribute, active
modifiers, target mitigation, and any other attributes captured by the effect.

Weapons can override specific damage values by adding **Set By Caller Magnitudes** to the outgoing Gameplay Effect Spec.
These magnitudes are provided through the combat magnitude provider flow, so weapons, equipment, or other effect sources
can contribute values without adding damage-specific functions to the Melee Interface.

Common melee damage magnitudes supported by the system are defined by `Combat.Data` prefixes. Weapon Actors specifically
will provide properties to set values to the following data tags.

| Gameplay Tag              | Description                                                            |
|---------------------------|------------------------------------------------------------------------|
| `Combat.Data.Damage`      | Overrides the pending damage value used by the damage Gameplay Effect. |
| `Combat.Data.PoiseDamage` | Overrides the poise damage value used by the damage Gameplay Effect.   |

The base `NinjaCombatWeaponActor` already implements this behavior. If its damage override options are enabled, it
provides the appropriate Set By Caller magnitudes when the melee hit Gameplay Effect is created.

## Melee Scan Request

The **Melee Scan Request**, `NinjaCombatMeleeScan`, is the transfer object that represents an active melee scan. It is
created by a Melee Scan Animation Notify State or by the Melee Attack Ability, and then passed to the ability task that
performs the scan.

A scan request carries the resolved scan setup used during combat, such as the source actors, scan mesh or overlap
component, socket names, scan channels, scan tags, trail Gameplay Cue, optional hit override, and any targets already
collected during the active scan.

Most melee attacks use animation-driven scans. In this case, the **Melee Scan Animation Notify State** creates the scan
request and sends it to the active **Melee Attack Ability** through a Gameplay Event. Event-based melee abilities expect
that event payload to contain a valid `NinjaCombatMeleeScan`.

The **Melee Attack Ability** can also create a scan request directly when the attack is triggered by **Ability
Activation** or **Delayed** mode. In those cases, the ability uses its own melee scan settings and scan duration instead
of waiting for a notify-provided scan.

Most projects can use the default scan request class. However, a custom scan class can be used when the default behavior
needs to be changed.

Common reasons to provide a custom scan class include:

- Overriding how targets are collected.
- Filtering actors before they are registered as hits.
- Changing which actors are ignored by the scan.
- Resolving component overlaps in a project-specific way.
- Adding scan-specific gameplay rules.

The main extension point is `ScanForTargets`, which is called while the scan is active. Custom implementations can collect
or filter hit results before they are passed back to the ability for damage processing.

> **Repeated Hits**
>
> By default, a scan does not register the same target more than once. Custom scan classes can change this by enabling
> `bAllowMultipleHitsOnSameTarget`.
{style="note"}

> **Shape Leniency**
>
> Shape-based scan requests can apply leniency to make sweeps slightly more forgiving without changing the source
> animation, socket setup, or shape dimensions configured in the melee scan setup.
{style="tip"}

## Cosmetics

Melee cosmetics are handled through **Gameplay Cues** and the Ninja Combat cosmetics pipeline.

Attack trails are usually active while a Melee Scan is open. Impact cosmetics are triggered when a hit is registered.
Both are delegated to the melee source, which can be either the combatant or the weapon.

The default trail Gameplay Cue is `GameplayCue.Combat.MeleeTrails`. It is handled by the **Combat Manager Component**,
which adds and removes the cue during the scan. The cue then reaches the melee source, where the Melee Interface functions
start or stop the configured trail cosmetics.

Impact cosmetics follow the same source-based approach. When melee damage is applied, the source can react through
`HandleMeleeDamageCosmetics`, usually by forwarding the hit data to its cosmetics component.

Projects can also handle these Gameplay Cues directly. The Ninja Combat cosmetics component is only a convenience layer
for common melee effects, such as Niagara Systems, sounds, camera shakes, attack trails, and impact trails.
# Melee Attacks
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>weapon</b> or <b>character</b> performing the attack must implement the <b>Melee Interface</b>.</li>
        <li>The <b>Attack Ability</b> is used to execute <b>Melee Attacks</b>. Once it activates, it will listen to many <b>Melee Scan Events</b>.</li>
        <li><b>Melee Scans</b> events are sent usually using the <b>Melee Scan Notify State</b> to start and stop the scan.</li>
        <li>At the end of each frame, the <b>Damage Gameplay Effect</b> is applied to all targets collected by the <b>Melee Scan</b>.</li>
    </ul>
</tldr>

**Melee Attacks** are one of the _core features_ of Ninja Combat. They are usually implemented using a combination of 
**Animation Montages** and **Gameplay Abilities**, collecting potential targets, and applying specified **Damage Effects**.

## Melee Weapon Interface
Any object, such as **Pawns** or **Weapons**, meant to execute **melee attacks** must implement `CombatMeleeInterface`.
It contains functions meant to expose relevant data and objects used by the combat system to process targets and apply damage. 

| Function                     | Description                                                                                                                    |
|------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| `GetMeleeMesh`               | Provides the mesh used by **Melee Scans**. Usually the Weapon Mesh.                                                            |
| `GetMeleeMeshByTag`          | Provides the mesh used by **Melee Scans**, identified by a specific tag. For cases where a weapon has more than one scan area. |
| `GetHitEffectClass`          | Provides a **Gameplay Effect** applied when this actor generates a **hit**. Overrides the Ability Hit Effect.                  |
| `GetHitEffectLevel`          | Level used when instantiating the **Damage Gameplay Effect**.                                                                  |
| `GetDamage`                  | Optionally provides a **damage** value magnitude set to the Gameplay Effect using `combat.data.damage` as the **data tag**.    |
| `GetPoiseConsumption`        | Optionally provides a **poise** value magnitude set to the Gameplay Effect using `combat.data.poise` as the **data tag**.      |
| `GetMeleeImpactStrength`     | Defines a strength applied when **physical reactions** are enabled.                                                            |
| `GetAttackTrails`            | Provides **cosmetic trails** that should be activated by the Melee Scan, during a melee attack.                                |
| `GetImpactTrails`            | Provides **cosmetic impact trails** used when the weapon hits (i.e. blood trails).                                             | 
| `StartMeleeTrailsCosmetics`  | Activates **attack trails and sounds** when necessary.                                                                         |
| `StopMeleeTrailsCosmetics`   | Deactivates **attack trails and sounds** when necessary.                                                                       |                                                                    
| `HandleMeleeDamageCosmetics` | Invoked by the Damage System to render **cosmetics** from a registered hit, via the **Gameplay Cue** system.                   |

> **Gameplay Effect Priority**
>
> You can define a Gameplay Effect in three places: **Attack Ability**, **Melee Interface**, and **Melee Scan**.
>
> If a Gameplay Effect is present in one or more of these slots, the selection order is **Melee Scan > Melee Interface > Attack Ability**.
{style="note"}

## Weapon Actor
The Weapon Actor (`NinjaCombatWeaponActor`) is an **abstract class** that can be used as a base for all your weapons. It
properly implements the **Melee Weapon Interface**, executing the expected logic and exposing properties for adjustment.

The Base Weapon Actor comes with the **Weapon Cosmetics Component**, used to handle all cosmetic assets registered to the
weapon, such as sounds and particles. This component is also integrated with the **Asset Manager**, supporting soft
references and loading on demand.

<procedure title="Prepare the Weapon for Melee Scans" collapsible="true" default-state="expanded">
    <step>Open the <b>Static or Skeletal Meshes</b> used to represent your melee weapons.</step>
    <step>Disable their default collisions, so they won't interfere with your gameplay.</step>
    <step>
        <p>Place sockets along the scan area, such as the blade. These will be used by both <b>melee scans</b> and <b>weapon trails</b>.</p>
        <img src="cbt_wpatk_melee_weapon_sockets.png" alt="Weapon Sockets" border-effect="line" thumbnail="true"/>
        <note>
            <p><b>Naming Convention</b></p>
            <p>All sockets should start with the <b>same prefix</b>, such as <code>sScan</code>, followed by numbers that can be <b>ordered</b> (e.g. <code>sScan1</code>, <code>sScan2</code>, <code>sScan3</code>). This convention is used by the system to determine first/last sockets across the scan area.</p>
        </note>
        <note>
            <p><b>Sockets for Melee Scans and Trails</b></p>
            <p>By default, these sockets are shared between <b>melee scans</b> and <b>weapon trails</b>, unless overridden by setting a different prefix in the <b>Scan Notify</b> or <b>Weapon Cosmetics Component</b>.</p>
        </note>
    </step>
</procedure>

<procedure title="Configure a Melee Weapon" collapsible="true" default-state="expanded">
    <step>Open one of your <b>melee weapon Blueprints</b>, such as the <b>Sword Weapon Actor</b>, created in the <b><a href="cbt_weapon_actors.md">Weapon Actors page</a></b>.</step>
    <step>
        <p>Implement the <code>GetMeleeMesh</code> function, returning the <b>Static or Skeletal Mesh</b> that will be used for <b>Melee Scans</b>.</p>
        <img src="cbt_wpatk_melee_get_mesh_implementation.png" alt="Weapon Setup" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>In the <b>Melee</b> category, in the <b>Defaults panel</b>, add any cosmetics that you'd like, such as the <b>Impact particles and sounds</b>.</p>
        <img src="cbt_wpatk_melee_weapon.png" alt="Weapon Setup" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

> **Base Weapon Class**
>
> It's highly recommended creating a **base weapon class or blueprint** containing any additional components, properties and logic.
> You can use `NinjaCombatWeaponActor` as a base class or, if you have a different class hierarchy, implement the appropriate interfaces.
{style="note"}

> **Gameplay Effect Priority**
>
> You can define a Gameplay Effect in three places: **Attack Ability**, **Melee Interface**, and **Melee Scan**.
>
> If a Gameplay Effect is present in one or more of these slots, the selection order is **Melee Scan > Melee Interface > Attack Ability**.
{style="note"}

## Melee Scans
Melee Scans are used to detect **weapon hits** during an attack. They are usually driven by animation, but the system
has a clear separation between the **Animation Notify State**, placed in each **attack Animation Montage**, and the 
**backend that actually scans for targets**.

<procedure title="Configuring a Melee Scan" collapsible="true" default-state="expanded">
    <step>Create or open an <b>Animation Montage</b> that represents the <b>melee attack</b>.</step>
    <step>
        <p>Add the <b>Melee Scan Notify State</b>, covering all frames where the melee scan should occur.</p>
        <img src="cbt_wpatk_melee_scan_notify_state.png" alt="Melee Scan Notify State" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>In the <b>Melee Scan</b> details, configure the <b>Gameplay Tag Query</b> used to retrieve the correct weapon from the <b><a href="cbt_weapon_manager.md"/></b>, to retrieve the weapon.</p>
        <img src="cbt_wpatk_melee_scan_weapon_query.png" alt="Melee Scan Weapon Query" border-effect="line"/>
    </step>
    <step>
        <p>Ensure that the selected <b><a href="cbt_collisions.md">Scan Channels</a></b> include <b>CombatObject</b>.</p>
        <note>
            <p><b>Default Scan Channels</b></p>
            <p>You can add your default Scan Channels, used by all melee scans, in the <b>Combat Settings</b> page, in your <b>Project Settings</b></p>
        </note>
    </step>
</procedure>

Here is a summary of each property available in the Melee Scan panel.

| Property               | Description                                                                                                                                                                                                |
|------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Source                 | Determines if this Melee Scan happens from the **owner** or from a **weapon**.                                                                                                                             |
| Weapon Query           | For Melee Scans happening from the **weapon**, this query is used to retrieve the correct weapon from the **Weapon Manager**.                                                                              |
| Melee Mesh Tag         | An optional Gameplay Tag that can identify a specific mesh, in case multiple meshes are available.                                                                                                         |
| Scan Socket Prefix     | A prefix for all **sockets** in the **source mesh** used to perform the scan.                                                                                                                              |
| Scan Channel           | All **collision object types** that will be detected by this Melee Scan.                                                                                                                                   |
| Scan Mode              | How the scan is performed (i.e. _line traces_ or _shape sweeps_. Appropriate settings will be shown for each option. See list below for details on each option.                                            |
| Melee Hit Override     | An optional **Gameplay Effect** that overrides the one set in the Ability or provided by the melee scan source. Follows the priority previously defined: **Melee Scan > Melee Interface > Attack Ability** |
| Melee Scan Class       | The **Melee Scan Request** class, that defines how this scan collects and filters hit targets. Can be customized to change scan logic.                                                                     |
| Melee Scan Tags        | Gameplay Tags containing **additional traits** to this melee scan, such as being a parry opportunity for its targets.                                                                                      |
| Trail Gameplay Cue Tag | Gameplay cue that will be **added** and **removed** during the Melee Scan.                                                                                                                                 |

The following options are available for the **Scan Mode**:
- **Line Trace**: Creates lines between each socket and then between their current positions and their positions on last frame. This is the default option.
- **Box Sweep**: Creates a box shape, with the provided extent, centered at the defined socket.
- **Capsule Sweep**: Creates a capsule shape, with the provided extent, centered at the defined socket.
- **Sphere Sweep**: Creates a sphere shape, with the provided radius, centered at the defined socket.

### Melee Scan Request Class
This object is used to transfer melee scan data between all the framework layers: **Animation**, **Ability**, and **Task**.
It also contains the logic to perform scans and consolidate targets. 

> **Single or Multiple Hits per Target**
>
> Via `bAllowMultipleHitsOnSameTarget` property, you can define if targets can be hit only **once** or **multiple times** 
> during a melee scan. By default, melee scans can only hit a target **once**.
{style=note}

If you need to **modify the Melee Scan logic**, this is the place to look into. You can set a Melee Scan Class to **each**
Melee Scan Animation Notify State or **globally**, in the **Ninja Combat Project Settings**.

> **Modifying the Melee Scan Logic**
>
> You can modify the Melee Scan logic executed by the Melee Scan Class in the `ScanForTargets` function. This function
> can be modified in Blueprints or C++.
> 
> In this function, you can customize how targets are collected per frame. The method receives scan parameters and can 
> filter or modify the final hit list before it's passed to the ability system for damage processing.
{style=note}

### Cosmetics
The default Trail Gameplay Cue defined by `GameplayCue.Combat.MeleeTrails` is already handled by the Combat Manager
Component, using the sound and particle effects set in the Melee Weapon.

The **Combat Manager** handles this Gameplay Cue and forwards it to the Melee Effect Causer - the Weapon or Combatant -
to handle the start and end of the cue, via the `StartMeleeTrailsCosmetics` and `StopMeleeTrailsCosmetics`.

## Attack Ability
The **Attack Ability** is responsible for **Melee** and **Ranged** attacks. To get started with Melee Attacks, all you
need to do is setting the **Default Animation Montage** and make sure to assign this Gameplay Ability to your character.

<img src="cbt_wpatk_attack_ability_melee.png" alt="Melee Ability" border-effect="line" thumbnail="true"/>

There are three important **property groups** in this Ability, that are relevant for **melee attacks**.

- **Melee Attack**: All properties that will define the melee attack's behavior. More information about this ability can be found in its [reference page][1].
- **Animation**: Here you can set your **Animation Provider** and the **Animation Montage**. We'll cover this in more detail in the [Character Animation page][2].
- **Motion Warping**: Used to improve the **connection between attacker and targets**. We'll cover this in more detail in the [Motion Warping][3] and [Gameplay Targeting System][4] pages. 
- **Debug**: Enabling debug in this ability will show the **trajectory** and **targets hit** by the **melee scan**.

[1]: cbt_ability_attack.md
[2]: cbt_character_animation.md
[3]: cbt_motion_warping.md
[4]: cbt_gameplay_targeting_system.md
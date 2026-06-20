# Creating Melee Attacks
<primary-label ref="combat"/>

This guide shows how to create a basic **melee attack** using an **Attack Ability**, an **Animation Montage**, a
**Melee Scan**, and optional **Motion Warping**.

The setup is agnostic to the melee source. The same flow works for attacks scanned from the **combatant**, such as
punches, claws, or creature attacks, and for attacks scanned from an equipped **weapon**.

For more information, see the documentation for [**Melee Attacks**](cbt_concept_melee_attacks.md).

> **Target Locking**
>
> Parts of this guide are shared with the [**Target Lock**](cbt_guide_target_lock.md) guide. If you are working on
> both, you will be able to reuse and skip certain steps.

## Prerequisites

### Collision and Components

Your collision channels, combat components, and base character setup should already be configured. For more information,
see [**Combat Setup**](cbt_setup.md) and [**Combat First Steps**](cbt_first_steps.md).

### Input Handling

Make sure your input setup can activate gameplay abilities. For more information, see
[**Combat and Input Integration**](integration_combat_input.md). Integration with Ninja Input is optional, but input
handling for ability activation should already be configured.

### Weapon Management
<secondary-label ref="optional"/>

If your melee scans originate from **weapons**, make sure to configure them first. For more information, see
[**Weapon Management**](cbt_concept_weapon_management.md).

## Motion Warping

[**Motion Warping**](cbt_concept_motion_warping.md) is commonly used by melee attacks to move the attacker closer to the
target by adjusting the animation's **root motion**.

This requires adding the **Motion Warping Component** to your character and implementing the appropriate getter function
from the **Combat System Interface**.

<procedure title="Add the Motion Warping Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatMotionWarpingComponent</code>.</step>
    <step>Implement <code>GetMotionWarpingComponent</code> from the <code>CombatSystemInterface</code>, returning your <b>Motion Warping Component</b>.</step>
</procedure>

> **Component Conflicts**
>
> If your character already uses the Motion Warping Component provided by Unreal Engine, then you need to **replace it
> with the one provided by the Combat framework**.
{style="warning"}

## Targeting Preset

Motion Warping can use a **Targeting Preset** to find the target that the attack should warp toward. We will create a
preset that prioritizes the [**locked target**](cbt_concept_target_locking.md) first. If no locked target is available, the
preset will collect targets using a fallback area scan.

<procedure title="Create a Targeting Preset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_melee_targeting_preset.png" alt="Targeting Preset" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Targeting Preset</b> asset.</step>
    <step>
        <p>Add the <b>Current Target Selection Task</b> and set the following properties:</p>
        <ul>
            <li>Set it to <b>Select Targets in Area</b>, so it will perform a scan as a fallback when no target is locked on.</li>
            <li>Set the <b>Maximum Distance for Target Lock</b> to <code>500</code>.</li>
            <li>Set the <b>Facing Angle Threshold</b> to <code>75</code>.</li>
            <li>Set the <b>Shape Type</b> to <b>Capsule</b>.</li>
            <li>Set the <b>Collision Channel</b> to <b>Combat Object</b>.</li>
            <li>Set the <b>Radius</b> to <code>200</code>, or any other value that fits your design.</li>
        </ul>
    </step>
    <step>Add the <b>Dead Filter Task</b>.</step>
    <step>Add the <b>Facing Filter Task</b> and set the <b>Maximum Angle</b> to <code>60</code>.</step>
    <step>Add the <b>Distance Sort Task</b>.</step>
</procedure>

> **Task Order**
>
> Targeting Tasks are executed in order, so add tasks respecting this flow: **Selection > Filtering > Sorting**.
{style="tip"}

## Owner-Based Scans

Owner-based scans are used when the melee source is the **combatant** instead of an equipped weapon. This is a good fit
for punches, kicks, claws, bites, tail attacks, creature attacks, and any melee hit that should be scanned from the
character's own mesh.

In this setup, the Animation Montage defines both the **movement correction** and the **active hit frames** for the melee
attack. It usually includes three types of Animation Notify States: **Track Motion Warp Target**, **Motion Warping**, and
**Melee Scan**.

<procedure title="Configure the Attack Montage (Owner)" collapsible="true" default-state="collapsed">
    <step>
        <p>Select the Animation Sequence that represents the Melee Attack Ability and create an <b>Animation Montage</b> from it.</p>
    </step>
    <step>
        <p>If applicable, select the correct <b>Slot</b> for the Animation Montage, based on the setup in your <b>Animation Instance</b>.</p>
    </step>
    <step>
        <p>Add a <b>Track Motion Warp Target</b> notify state during the part of the animation where the target should be resolved or tracked.</p>
        <p>Set <code>Combat Warp</code> as the <b>Warp Name</b> and assign the <b>Targeting Preset</b> created earlier.</p>
        <warning>
            <p><b>Warp Name</b></p>
            <p>The Warp Name must match between the <b>Track Motion Warp Target</b> notify and the <b>Motion Warping</b> notify.</p>
        </warning>
        <img src="cbt_guide_melee_animation_warp_target.png" alt="Warp Target" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Add a <b>Motion Warping</b> notify state during the root motion section that should be adjusted.</p>
        <p>Set the <b>Root Motion Modifier</b> to <b>Skew Warp</b> and set <code>Combat Warp</code> as the <b>Warp Name</b>.</p>
        <img src="cbt_guide_melee_animation_motion_warping.png" alt="Motion Warping" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Add a <b>Melee Scan</b> notify state over the frames where the attack should be active. Configure the following properties:</p>
        <ul>
            <li>Set the <b>Source</b> to <b>Owner</b>.</li>
            <li>Set the <b>Scan Mode</b> to <b>Sphere Sweep</b>.</li>
            <li>Set the <b>Scan Socket</b> to <code>middle_01_r</code>, or the appropriate bone or socket name for your skeleton.</li>
            <li>Add <b>CombatObject</b> and <b>Destructible</b> as the <b>Scan Channels</b>.</li>
            <li>Set the <b>Sphere Radius</b> to <code>40</code>, or another appropriate size.</li>
        </ul>
        <img src="cbt_guide_melee_animation_scan_owner.png" alt="Melee Scan (Owner)" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

## Weapon-Based Scans

Weapon-based scans are used when the melee source is an equipped **Weapon** instead of the combatant. This is the usual
setup for swords, axes, spears, shields, and other attacks where the hit area should follow a weapon mesh.

In this setup, the weapon provides the mesh and scan sockets, while the **Weapon Manager** provides the active weapon
instance to the Melee Scan. The Animation Montage still controls the attack timing, Motion Warping, and the active scan
frames.

This section uses the default **Weapon Manager Component** and **Weapon Actor** provided by Ninja Combat. If you are using
[**Ninja Inventory**](inv_overview.md), see the [**Combat and Inventory Integration**](integration_combat_inventory.md)
page for the inventory-based replacements.

<procedure title="Configure a Weapon Mesh" collapsible="true" default-state="collapsed">
    <step>Open the <b>skeletal or static mesh</b> that represents your <b>weapon</b>. In this example, we'll use a sword.</step>
    <step>
        <p>Add a socket at the center of the blade and name it <code>sScan01</code>.</p>
        <img src="cbt_guide_melee_weapon_socket.png" alt="Weapon Socket" border-effect="line" thumbnail="true"/>
    </step>
    <step>Make sure that the asset has <b>no collision</b>, since regular mesh collision can interfere with gameplay collision and scan results.</step>
</procedure>

<procedure title="Create the Weapon Actor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Weapon Actor</b> based on <code>NinjaCombatWeaponActor</code>.</step>
    <step>Add a <b>Static Mesh Component</b> or <b>Skeletal Mesh Component</b> for the weapon mesh.</step>
    <step>Implement <code>GetMeleeMesh</code>, returning the mesh component used by the Melee Scan.</step>
    <step>Create a <b>Child Blueprint</b> and set the sword mesh configured earlier.</step>
    <step>Add <code>Combat.Weapon.Sword</code>, or any other identifying tags, to the list of <b>Weapon Tags</b>.</step>
</procedure>

<procedure title="Add the Weapon Manager Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatWeaponManagerComponent</code>.</step>
    <step>Implement <code>GetWeaponManagerComponent</code> from the <code>CombatSystemInterface</code>, returning your <b>Weapon Manager Component</b>.</step>
    <step>Add your weapon Blueprint to the list of <b>Default Weapon Classes</b>.</step>
</procedure>

<procedure title="Configure the Attack Montage (Weapon)" collapsible="true" default-state="collapsed">
    <step>
        <p>Select the Animation Sequence that represents the Melee Attack Ability and create an <b>Animation Montage</b> from it.</p>
    </step>
    <step>
        <p>If applicable, select the correct <b>Slot</b> for the Animation Montage, based on the setup in your <b>Animation Instance</b>.</p>
    </step>
    <step>
        <p>Repeat the same steps used by owner-based scans for <b>Track Motion Warp Target</b> and <b>Motion Warping</b>.</p>
    </step>
    <step>
        <p>Add a <b>Melee Scan</b> notify state over the frames where the attack should be active. Configure the following properties:</p>
        <ul>
            <li>Set the <b>Source</b> to <b>Weapon</b>.</li>
            <li>Set the <b>Weapon Query</b> so the <b>Weapon Manager</b> can find the weapon configured earlier.</li>
            <li>Set the <b>Scan Mode</b> to <b>Box Sweep</b>, which works well for this sword example.</li>
            <li>Set the <b>Scan Socket</b> to <code>sScan</code>, matching the socket prefix added to the weapon mesh.</li>
            <li>Add <b>CombatObject</b> and <b>Destructible</b> as the <b>Scan Channels</b>.</li>
            <li>Set the <b>Box Half Extent</b> to <code>2, 2, 50</code>, or another size that fits your weapon. Use the socket gizmo in the weapon mesh to orient these dimensions.</li>
        </ul>
        <img src="cbt_guide_melee_animation_scan_weapon.png" alt="Melee Scan (Weapon)" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

## Configure the Attack Ability

The **Attack Ability** plays the montage, listens for Melee Scan events, and applies damage to valid targets.

### Create a Melee Damage Effect

Create a Gameplay Effect that represents the damage applied by the melee attack.

<procedure title="Create the Damage Gameplay Effect" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Gameplay Effect</b> asset based on <code>CombatEffect_MeleeHit</code>.</step>
    <step>If the damage or poise values are provided by the melee source, make sure the effect supports the expected Set By Caller magnitudes.</step>
</procedure>

Common Set By Caller tags used by melee sources include:

| Tag                  | Purpose                                               |
|----------------------|-------------------------------------------------------|
| `combat.data.damage` | Damage value provided by the melee source.            |
| `combat.data.poise`  | Poise consumption value provided by the melee source. |

> **Gameplay Effect Priority**
>
> A hit Gameplay Effect can be defined by the Attack Ability, the Melee Interface, or the Melee Scan.
>
> When more than one is available, they are selected in this order:
>
> **Melee Scan > Melee Interface > Attack Ability**
{style="tip"}

### Configure the Ability

<procedure title="Configure the Attack Ability" collapsible="true" default-state="collapsed">
    <step>In your Attack Ability folder, create a new <b>Gameplay Ability Blueprint</b> using <code>CombatAbility_MeleeAttack</code> as the base class.</step>
    <step>Set the <b>Default Animation Montage</b> to the montage configured earlier.</step>
    <step>Set the default <b>Hit Gameplay Effect</b> to the Gameplay Effect created earlier.</step>
    <step>Configure the <b>Ability Tags</b> used to activate this Attack Ability.</step>
    <step>Optionally, set the <b>Optimal Melee Distance</b>.</step>
    <step>Optionally, enable <b>Debug Mode</b> to visualize melee scans and impacts.</step>
</procedure>

> **Optimal Melee Distance**
>
> If Motion Warping is enabled, the Attack Ability's **Optimal Melee Distance** can be used by the Motion Warping
> Component to adjust how close the attacker moves toward the target.
{style="note"}
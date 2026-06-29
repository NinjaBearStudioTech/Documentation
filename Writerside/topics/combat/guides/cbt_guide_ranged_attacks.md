# Configuring Ranged Attacks
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to create a basic **ranged attack** using a **Gameplay Ability**, an **Animation Montage**, and a
**Projectile Actor**.

The setup works with different ranged sources. The same flow works for projectiles launched from the **combatant** and
for projectiles launched from an equipped **weapon**. The shared prerequisite is that the projectile source must implement
`ICombatRangedInterface`.

For more information, see the documentation for [**Ranged Attacks**](cbt_concept_ranged_attacks.md).

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

If your projectiles originate from **weapons**, make sure to configure them first. For more information, see
[**Weapon Management**](cbt_concept_weapon_management.md).

## Projectile Actor

The projectile actor is launched by a Gameplay Ability and owns the Gameplay Effect application.

<procedure title="Create the Damage Gameplay Effect" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_projectile_damage.png" alt="Damage Gameplay Effect" thumbnail="true" border-effect="line"/>
    <step>In your Projectile Ability folder, create a new <b>Gameplay Effect Blueprint</b> using <code>CombatEffect_RangedHit</code> as the base class.</step>
    <step>Optionally, add a <b>Gameplay Cue</b> that should be applied to each target affected by the projectile.</step>
</procedure>

<procedure title="Create the Projectile Actor" collapsible="true" default-state="collapsed">
    <step>In your Blueprints folder, create a new <b>Projectile Actor Blueprint</b> using <code>NinjaCombatProjectileActor</code> as the base class.</step>
    <step>
        <p>Review the default <b>Projectile Behaviors</b> and adjust settings as needed:</p>
        <ul>
            <li>In the <b>Hit Processor</b> behavior, set the <b>Hit Adjustment Trace Channel</b> to <code>CombatObject</code>.</li>
            <li>In the <b>Scan</b> behavior, set the <b>Scan Channel</b> to <code>CombatObject</code>.</li>
            <li>In the <b>Exhaustion</b> behavior, adjust the <b>Active Duration</b> as needed.</li>
        </ul>
    </step>
    <step>
        <p>Add a <b>Niagara Component</b> to the <b>Root Sphere</b>. Set <b>Auto Activate</b> to <code>false</code>.</p>
        <tip>Although you can assign particles and sound assets directly to these components, it is usually better to keep this Blueprint as an <b>abstract parent</b> for your Projectile Actors.</tip>
    </step>
    <step>
        <p>In the <b>My Blueprint</b> tab, expand <b>Overridable Functions</b> and add the following events to the <b>Event Graph</b>.</p>
        <ul>
            <li>Double-click <code>LaunchProjectile</code> to add this event to the graph. Right-click the node and select <b>Add Call to Parent Function</b>.</li>
            <li>Double-click <code>Exhaust</code> to add this event to the graph. Right-click the node and select <b>Add Call to Parent Function</b>.</li>
        </ul>
        <note>Always call the <b>Parent Function</b> in your base <b>Projectile Actors</b>, since the base class runs important setup logic there.</note>
    </step>
    <step>
        <img src="cbt_guide_projectile_actor_graph.png" alt="Projectile Actor Graph" width="780" thumbnail="true" border-effect="line"/>
        <p>Implement the new events, activating and deactivating components.</p>
        <ul>
            <li>When <b>launching the projectile</b>, activate the <b>VFX</b> component. Make sure the component is set to <b>Reset</b>.</li>
            <li>When the projectile <b>exhausts</b>, deactivate the VFX.</li>
        </ul>
    </step>
    <step>Close the base Blueprint and create a new <b>Child Blueprint</b>. This child Blueprint is the one that will be used by the ability.</step>
    <step>Assign the Niagara System and Sound assets that should be used by this Projectile Actor.</step>
    <step>Set the Gameplay Effect applied by the Projectile Actor to the <b>Impact Effect Class</b>.</step>
</procedure>

## Gameplay Ability

The Gameplay Ability will activate, wait for a Gameplay Event from the animation, and launch the projectile. 

While using **Gameplay Event** mode, the ability can launch a Projectile Actor class provided by the **Projectile Payload**, 
or use the **Fallback Projectile Class** configured in the ability.

<procedure title="Create the Animation Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_projectile_montage_notify.png" alt="Projectile Animation Montage (with Notify)" thumbnail="true" border-effect="line"/>
    <step>Select the Animation Sequence that represents the ranged attack and create an <b>Animation Montage</b> from it.</step>
    <step>If applicable, select the correct <b>Slot</b> for the Animation Montage, based on the setup in your <b>Animation Instance</b>.</step>
    <step>Navigate to the point in the Animation Montage where the projectile should launch, then add the <b>Launch Projectile</b> Animation Notify.</step>
    <step>
        <p>Configure the Animation Notify with a proper <b>Source</b> and <b>Origin Socket</b>.</p>
        <tip>
            <p><b>Weapon Sources</b></p>
            <p>If you are using a <b>weapon</b> as the source, make sure to add a <b>socket</b> to the weapon's mesh and configure the <b>Weapon Query</b>.</p>
        </tip>
    </step>
</procedure>

<procedure title="Create the Projectile Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_projectile_ability.png" alt="Projectile Ability" thumbnail="true" border-effect="line"/>
    <step>
        <p>Create a new <b>Gameplay Ability</b> using <code>CombatAbility_LaunchProjectile</code> as the base class.</p>
    </step>
    <step>
        <p>Configure the Projectile Ability with the following values:</p>
        <ul>
            <li><b>Projectile Trigger</b>: <b>Gameplay Event</b></li>
            <li><b>Commit Time</b>: <b>Ability Activates</b></li>
            <li><b>Fallback Projectile Class</b>: the <b>Projectile Blueprint</b></li>
        </ul>
    </step>
    <step>Add any <b>Gameplay Tags</b> required to activate the ability.</step>
</procedure>
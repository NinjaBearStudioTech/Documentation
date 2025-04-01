# Collision Settings
<primary-label ref="combat"/>

<tldr>
    <p><b>Summary: Configuring Collisions for Ninja Combat</b></p>
    <br/>
    <ul>
        <li>Configure a new <b>Object Channel</b> for <b>Combat Objects</b>.</li>
        <li>Configure new <b>Trace Channels</b> for <b>Projectiles</b> and for <b>Opportunity Attacks</b>.</li>
        <li>Configure new <b>Collision Presets</b> that will be applied to <b>Combat Character Meshes</b> and <b>Combat Collision Components</b>.</li>
    </ul>
</tldr>

In this page, you will learn how to configure the necessary **Collisions** that will be used by **Ninja Combat**. These
are used by **Melee Scans**, **Projectile Traces** and **Opportunity Line-of-Sight**.

## Object and Trace Channels
Ninja Combat uses **Object** and **Trace** channels to detect important gameplay events, such as melee hits. For more 
details about Object and Trace Channels, check the [official Unreal Engine documentation][1].

<procedure title="Configure the Combat Object channel" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Object Channel</b> section, create a new channel, by clicking the <b>New Object Channel</b> button, and name it <b>CombatObject</b>. Set its <b>default response</b> to <b>ignore</b>.</step>
</procedure>

<procedure title="Configure Combat Trace channels" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Trace Channel</b> section, create a new channel, by clicking the <b>New Trace Channel</b> button, and name it <b>ProjectileScan</b>. Set its <b>default response</b> to <b>ignore</b>.</step>
    <step>Create another new channel, by clicking the <b>New Trace Channel</b> button, and name it <b>OpportunityScan</b>. Set its <b>default response</b> to <b>ignore</b>.</step>
</procedure>

## Collision Presets
To simplify assigning the correct channels, and their **block** responses, to relevant actors in the world, we will 
create **Collision Presets** that can be easily assigned. 

> Using presets helps you apply consistent collision rules to characters, projectiles, and custom components without
> having to configure each one manually.
{style=note}

The **CombatMesh** preset can be assigned to any Combat Mesh (such as the main character mesh) and has the exact same
responses as the **CharacterMesh**, but it includes the combat-related traces.

Other colliders, such as projectiles or dedicated character collision components can use the **CombatCollider** preset
that only blocks combat-related traces.

<procedure title="Configure the Combat Mesh preset" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Preset</b> section, create a new entry, name it <b>CombatMesh</b>.</step>
    <step>
        <p>Set <b>Collision Enabled</b> to <b>Query Only</b>, the <b>Object Type</b> to <b>CombatObject</b> and a meaningful description like <i>Handles common mesh responses and blocks combat traces</i>.</p>
        <tip>Make sure <b>CombatObject</b> was created in the <i>Object Channel</i> section above, or it won't show in the dropdown!</tip>
    </step>
    <step>
        <p>Set the <b>Collision Responses</b> so they match the <b>Character Mesh</b> responses, making sure to <b>block</b> combat-related types.</p>
        <p><img src="cbt_setup_collisions_combat_mesh.png" alt="Combat Mesh Collision" border-effect="line"/></p>
    </step>
</procedure>

<procedure title="Configure the Combat Collider preset" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Preset</b> section, create a new entry, name it <b>CombatCollider</b>.</step>
    <step>
        <p>Set <b>Collision Enabled</b> to <b>Query Only</b>, the <b>Object Type</b> to <b>CombatObject</b> and a meaningful description like <i>Only blocks channels related to the combat system</i>.</p>
        <tip>Make sure <b>CombatObject</b> was created in the <i>Object Channel</i> section above, or it won't show in the dropdown!</tip>
    </step>
    <step>
        <p>Set the <b>Collision Responses</b> so only combat-related types are <b>blocked</b>.</p>
        <p><img src="cbt_setup_collisions_combat_collider.png" alt="Combat Mesh Collision" border-effect="line"/></p>
    </step>
</procedure>

## Default Melee Scan Collisions
Set default channels for melee scans so they automatically use the correct setup without requiring manual configuration for each notify.
You can still fine-tune them in each notify, as needed. 

<procedure title="Configure default Melee Scan channels" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Ninja Combat</b> settings (Edit &rarr; Project Settings &rarr; Ninja Combat).</step>
    <step>
        <p>Set the <b>Melee Scan Channels</b> to <code>CombatObject</code>, <code>Destructible</code> and <code>WorldStatic</code>.</p>
        <p><img src="cbt_setup_collisions_melee_scan.png" alt="Combat Mesh Collision" thumbnail="true" border-effect="line" width="600"/></p>
    </step>
</procedure>

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/collision-in-unreal-engine---overview

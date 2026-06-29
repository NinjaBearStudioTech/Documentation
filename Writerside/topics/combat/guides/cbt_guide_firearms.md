# Configuring Firearms

<primary-label ref="combat"/>
<secondary-label ref="guide"/>

The **Firearms Module** allows you to design weapons that operate using **hitscans** or **projectiles**. For more 
information, check the [**Firearms documentation**](cbt_concept_firearms.md).

This guide covers **hitscan-based** weapons. Projectile-based firearms follow the same general setup, but use projectile 
definitions instead of hitscan impact handling, similar to [**ranged combat**](cbt_guide_ranged_attacks.md).

## Surfaces for Hitscans

Hitscan firearms use an **Impact Table** to represent surface impacts. This table defines the particles and sounds used 
for each surface configured in your project.

For more information, check the setup for [**Physical Materials**](cbt_setup.md#).

<procedure title="Configure the Impact Table" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_impacts.png" alt="Impact Table" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Data Table</b> based on <code>CombatImpactCosmeticsTableRow</code>.</step>
    <step>
        <p>Add a new row for each <b>Physical Material</b> relevant to your project.</p>
        <ul>
            <li>Name each row after the corresponding <b>Physical Material Data Asset</b>.</li>
            <li>Configure <b>Particles</b> and <b>Sound Effects</b> as needed.</li>
        </ul>
    </step>
    <tip>Make sure to create an entry for your <b>Default Material</b> as well.</tip>
</procedure>

## Rifle Design

Rifles can be configured as **single-shot**, **burst-fire**, or **fully automatic** weapons. You can also extend the 
**Firearm Component** to switch between fire modes dynamically.

In this example, we will configure a **fully automatic** rifle.

<procedure title="Create the Rifle Data Asset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_data_rifle.png" alt="Rifle Data Asset" border-effect="line" thumbnail="true"/>
    <step>In your Firearm Data folder, create a new <b>Firearm Data Asset</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Combat &rarr; Firearm Definition.</step>
    <step>
        <p>Configure the main properties for the rifle.</p>
        <ul>
            <li>Set the <b>Implementation</b> to <code>Hit Scan</code>.</li>
            <li>Set the <b>Fire Mode</b> to <code>Automatic</code>.</li>
            <li>Set the <b>Hit Scan Channel</b> to <code>Projectile</code>.</li>
            <li>Set the <b>Fire Rate</b> to a fast value, such as <code>7</code>.</li>
            <li>Set the <b>Precision</b> to <code>0.85</code>.</li>
            <li>Set the <b>Base Pellet Damage</b> to <code>20</code>. This value is applied to the <b>Firearm Damage Effect</b>.</li>
        </ul>
    </step>
    <step>
        <p>Configure the <b>Ammo Query</b> to match the proper ammo in the <b>Ammo Storage Component</b>.</p>
        <img src="cbt_guide_firearm_data_rifle_ammo.png" alt="Rifle Ammo" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set both <b>Ammo Limit</b> and <b>Initial Ammo</b> to <code>30</code>.</step>
    <step>Configure the <b>Muzzle Socket Name</b> if it is different from the default value.</step>
    <step>Add the muzzle particles and sound used when the weapon fires.</step>
    <step>Add the previously configured <b>Impact Table</b>.</step>
</procedure>

<procedure title="Configure the Shoot Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_animation_fire_rifle.png" alt="Rifle Shoot Montage" border-effect="line" thumbnail="true"/>
    <step>Create or open the <b>Shoot Animation Montage</b> used by the rifle.</step>
    <step>
        <p>Add a section named <code>Shoot</code>. This section is used when the firearm plays its shooting animation.</p>
        <p>Keep this section short, only including the actual shooting part of the animation.</p>
    </step>
    <step>
        <p>Add the firing animation to the montage slots.</p>
        <ul>
            <li>Use an <b>Upper Body</b> slot for shooting while the character is moving.</li>
            <li>Use a <b>Full Body</b> slot for shooting while the character is standing still.</li>
        </ul>
    </step>
    <step>Configure a short <b>Blend-In Time</b>, such as <code>0.05</code>.</step>
    <note>Firearm montages are usually configured with <b>two slots</b>: one played on the upper body while the character is moving, and one played on the full body while the character is standing.</note>
</procedure>

<procedure title="Configure the Reload Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_animation_reload_rifle.png" alt="Rifle Reload Montage" border-effect="line" thumbnail="true"/>
    <step>Create or open the <b>Reload Animation Montage</b> used by the rifle.</step>
    <step>Add a section named <code>Reload</code>. This section is used when the firearm plays its reload animation.</step>
    <step>
        <p>Add the reload animation to the montage slots.</p>
        <ul>
            <li>Use an <b>Upper Body</b> slot for reloading while the character is moving.</li>
            <li>Use a <b>Full Body</b> slot for reloading while the character is standing still.</li>
        </ul>
    </step>
    <step>Add the <code>Reload Ammo</code> Animation Notify at the point where ammo should be restored.</step>
    <note>Firearm montages are usually configured with <b>two slots</b>: one played on the upper body while the character is moving, and one played on the full body while the character is standing.</note>
</procedure>

## Shotgun Design

A shotgun is also a **hitscan-based** weapon. It is configured as a **single-shot** firearm that fires multiple pellets 
per shot and uses a reload mode that adds **one shell per animation loop**.

<procedure title="Create the Shotgun Data Asset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_data_shotgun.png" alt="Shotgun Data Asset" border-effect="line" thumbnail="true"/>
    <step>In your Firearm Data folder, create a new <b>Firearm Data Asset</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Combat &rarr; Firearm Definition.</step>
    <step>
        <p>Configure the main properties for the shotgun.</p>
        <ul>
            <li>Set the <b>Implementation</b> to <code>Hit Scan</code>.</li>
            <li>Set the <b>Fire Mode</b> to <code>Single Shot</code>.</li>
            <li>Set the <b>Hit Scan Channel</b> to <code>Projectile</code>.</li>
            <li>Set the <b>Fire Rate</b> to <code>1</code>.</li>
            <li>Set the <b>Pellets Per Shot</b> to <code>8</code>.</li>
            <li>Set the <b>Base Pellet Damage</b> to <code>10</code>. This value is applied to the <b>Firearm Damage Effect</b>.</li>
        </ul>
    </step>
    <step>
        <p>Configure the <b>Ammo Query</b> to match the proper shotgun ammo in the <b>Ammo Storage Component</b>.</p>
        <img src="cbt_guide_firearm_data_shotgun_ammo.png" alt="Shotgun Ammo" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set both <b>Ammo Limit</b> and <b>Initial Ammo</b> to <code>8</code>.</step>
    <step>
        <p>Configure the reload settings.</p>
        <ul>
            <li>Set the <b>Reload Mode</b> to <code>Single</code>.</li>
            <li>Set <b>Ammo Added</b> to <code>1</code>.</li>
            <li>Set the <b>Reload Loop Section</b> to <code>Loop</code>.</li>
            <li>Set the <b>Reload End Section</b> to <code>End</code>.</li>
        </ul>
    </step>
    <step>
        <p>Configure the shotgun spread.</p>
        <ul>
            <li>Set the <b>Precision</b> to <code>0.65</code>.</li>
            <li>Set the <b>Spread Angle</b> to <code>8</code>.</li>
        </ul>
    </step>
    <step>Configure the <b>Muzzle Socket Name</b> if it is different from the default value.</step>
    <step>Add the muzzle particles and sound used when the weapon fires.</step>
    <step>Add the previously configured <b>Impact Table</b>.</step>
</procedure>

<procedure title="Configure the Shoot Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_animation_fire_shotgun.png" alt="Shotgun Shoot Montage" border-effect="line" thumbnail="true"/>
    <step>Create or open the <b>Shoot Animation Montage</b> used by the shotgun.</step>
    <step>Add a section named <code>Shot</code>. This section is used when the firearm plays its shooting animation.</step>
    <step>Add a section named <code>Exit</code>. This section allows the montage to finish cleanly after the shot is fired.</step>
    <step>
        <p>Add the firing animation to the montage slots.</p>
        <ul>
            <li>Use an <b>Upper Body</b> slot for shooting while the character is moving.</li>
            <li>Use a <b>Full Body</b> slot for shooting while the character is standing still.</li>
        </ul>
    </step>
    <step>Configure a short <b>Blend-In Time</b>, such as <code>0.05</code>.</step>
    <note>Firearm montages are usually configured with <b>two slots</b>: one played on the upper body while the character is moving, and one played on the full body while the character is standing.</note>
</procedure>

<procedure title="Configure the Reload Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_animation_reload_shotgun.png" alt="Shotgun Reload Montage" border-effect="line" thumbnail="true"/>
    <step>Create or open the <b>Reload Animation Montage</b> used by the shotgun.</step>
    <step>Add a section named <code>Reload</code>. This section starts the reload animation.</step>
    <step>Add a section named <code>Loop</code>. This section is repeated while shells are being added to the firearm.</step>
    <step>Add a section named <code>End</code>. This section is played when the reload finishes.</step>
    <step>
        <p>Add the reload animations to the montage slots.</p>
        <ul>
            <li>Use an <b>Upper Body</b> slot for reloading while the character is moving.</li>
            <li>Use a <b>Full Body</b> slot for reloading while the character is standing still.</li>
        </ul>
    </step>
    <step>
        <p>Add the <code>Reload Ammo</code> Animation Notify in the <code>Loop</code> section, at the point where one shell should be added.</p>
        <p>Since this shotgun uses a single-shell reload, this notify is triggered once per reload loop.</p>
    </step>
    <note>Firearm montages are usually configured with <b>two slots</b>: one played on the upper body while the character is moving, and one played on the full body while the character is standing.</note>
</procedure>

## Firearm Operation

Firearm operation is split between two parts: **Gameplay Abilities** that execute weapon actions and **Firearm Components** 
that manage and update weapon data.

Ammo storage can also be integrated with [**Ninja Inventory**](inv_overview.md). For more information, check the related 
**Inventory Integration Guide**.

<procedure title="Create the Shoot Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_ability_shoot.png" alt="Firearm Shoot Ability" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_Shoot</code>.</step>
    <step>Set the <b>Animation Trigger</b> to <code>Blended In</code>.</step>
    <step>
        <p>Review the animation settings.</p>
        <ul>
            <li>Set the <b>Animation Provider</b> to <code>Firearm: Shoot</code>. This provider retrieves the correct animation from the Firearm Component.</li>
            <li>Set the <b>Default Section Name</b> to <code>Shoot</code> to match the montage section.</li>
        </ul>
    </step>
    <tip>
        <p><b>Activation Tags</b></p>
        <p>This ability is activated by a <b>Gameplay Event</b> sent by the <b>Firearm Component</b>, so you do not need to configure activation tags.</p>
    </tip>
</procedure>

<procedure title="Create the Reload Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_ability_reload.png" alt="Firearm Reload Ability" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_Reload</code>.</step>
    <step>
        <p>Configure the reload settings.</p>
        <ul>
            <li>Set the <b>Reload Policy</b> to <code>Gameplay Event</code>.</li>
            <li>Set the <b>Reloading Effect Class</b> to your reload effect, such as <code>CombatEffect_Reloading</code>.</li>
            <li>Configure the <b>Weapon Query</b> to find the equipped firearm.</li>
        </ul>
    </step>
    <step>
        <p>Review the animation settings.</p>
        <ul>
            <li>Set the <b>Animation Provider</b> to <code>Firearm: Reload</code>. This provider retrieves the correct animation from the Firearm Component.</li>
            <li>Set the <b>Default Section Name</b> to <code>Reload</code> to match the montage section.</li>
        </ul>
    </step>
    <step>Add <code>Ability.Activation.Reload</code> so your input handling or AI can activate this ability by tag.</step>
</procedure>

<procedure title="Add the Firearm Component" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_component.png" alt="Firearm Component" border-effect="line" thumbnail="true"/>
    <step>Open your <b>Base Firearm Actor</b> and browse to its <b>Firearm Component</b>.</step>
    <step>Assign the correct <b>Aim</b> based on your project's needs.</step>
    <step>
        <p>Optionally, configure <b>Aim Assist</b> using the <b>Gamepad Aim Assist</b> implementation provided by the system.</p>
        <p>You need to provide a <b>Targeting Preset</b> that collects nearby targets for aim assist.</p>
        <img src="cbt_guide_firearm_preset_aim_assist.png" alt="Aim Assist Preset" border-effect="line" thumbnail="true"/>
    </step>
    <step>Open your <b>Firearm Actor</b>, such as the rifle or shotgun, and browse to its <b>Firearm Component</b>.</step>
    <step>Assign the correct <b>Firearm Data Asset</b> and <b>Firearm Animations</b> for shooting and reloading.</step>
</procedure>

<procedure title="Add the Ammo Storage Component" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_firearm_ammo.png" alt="Ammo Storage Component" border-effect="line" thumbnail="true"/>
    <step>Open your base character and add the <b>Ammo Storage Component</b>.</step>
    <step>Browse to the <b>Initial Ammo</b> section and configure your <b>Ammo Types</b> and current amounts.</step>
    <note>
        <p><b>Ammo Tags and Queries</b></p>
        <p>Ammo tags must be compatible with the ammo queries set for each Firearm Data Asset.</p>
    </note>
</procedure>

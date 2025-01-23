# Create Melee Attacks
<secondary-label ref="guide"/>

<video src="https://youtu.be/3LzloincIuc" preview-src="sc_thumbnail_p01g04.png" width="800" />

With the **melee weapons** configured, the next step is to create a **primary** and a **secondary** attack using the 
**Attack Ability**, add these abilities to the player character using **Ninja GAS** and configure their inputs using 
**Ninja Input**.

<procedure title="Add sockets for Melee Scans" collapsible="true">
    <step>
        <p>Open the <b>Static Mesh</b> for the <b>sword</b> and add <b>three sockets</b> along the blade.</p>
        <p>Make sure to prefix your sockets with <code>sScan</code>, this prefix will be used soon.</p>
        <img src="p01g04_weapon_sockets_sword.png" alt="Sword Sockets" border-effect="line" thumbnail="true" width="600"/>
    </step>
    <step>
        <p>Open the <b>Static Mesh</b> for the <b>shield</b> and add <b>one socket</b> at the center.</p>
        <p>Again, make sure to prefix your sockets with <code>sScan</code>.</p>
        <img src="p01g04_weapon_sockets_shield.png" alt="Shield Sockets" border-effect="line" thumbnail="true" width="600"/>
    </step>
</procedure>

<procedure title="Configure the primary attack animation" collapsible="true">
    <step>Create an <b>Animation Montage</b> from an appropriate <b>Animation Sequence</b> that represents the <b>primary attack</b>.</step>
    <step>In the Animation Montage, add the <b>Melee Scan Notify State</b> along the frames where the scan should happen.</step>
    <step>
        <p>In the Melee Scan Notify State Details:</p>
        <ul>
            <li>Set the <b>Source</b> to <code>Weapon</code> and your <b>Scan Channel</b> to <code>Weapon</code>.</li>
            <li>Leave the <b>Scan Socket Prefix</b> value unchanged, since it matches the names used in the sword mesh sockets.</li>
            <li>Leave the <b>Scan Mode</b> set to <b>Line Trace</b>.</li>
        </ul>
        <img src="p01g04_animation_attack_primary.png" alt="Primary Attack Animation" border-effect="line" thumbnail="true" width="600"/>
    </step>
    <step>
        <p>Configure the <b>Weapon query</b>, so it will obtain the <b>sword</b> from the <b>Weapon Manager</b>.</p>
        <img src="p01g04_weapon_query_sword.png" alt="Sword Melee Scan Notify Query" border-effect="line" thumbnail="true" width="600"/>
        <tip>This is the same Gameplay Tag that was added to the Weapon Actor created for the sword!</tip>
    </step>
</procedure>

<procedure title="Configure the secondary attack animation" collapsible="true">
    <step>Create an <b>Animation Montage</b> from an appropriate <b>Animation Sequence</b> that represents the <b>secondary attack</b>.</step>
    <step>In the Animation Montage, add the <b>Melee Scan Notify State</b> along the frames where the scan should happen.</step>
    <step>
        <p>In the Melee Scan Notify State Details:</p>
        <ul>
            <li>Set the <b>Source</b> to <code>Weapon</code> and your <b>Scan Channel</b> to <code>Weapon</code>.</li>
            <li>Leave the <b>Scan Socket Prefix</b> value unchanged, since it matches the name used in the shield mesh socket.</li>
            <li>Set the <b>Scan Mode</b> set to <b>Box Sweep</b> and set dimensions that roughly match the shield's dimensions.</li>
        </ul>
        <img src="p01g04_animation_attack_secondary.png" alt="Secondary Attack Animation" border-effect="line" thumbnail="true" width="600"/>
    </step>
    <step>
        <p>Configure the <b>Weapon query</b>, so it will obtain the <b>shield</b> from the <b>Weapon Manager</b>.</p>
        <img src="p01g04_weapon_query_shield.png" alt="Shield Melee Scan Notify Query" border-effect="line" thumbnail="true" width="600"/>
        <tip>This is the same Gameplay Tag that was added to the Weapon Actor created for the shield!</tip>
    </step>
</procedure>

<procedure title="Configure the primary attack ability" collapsible="true">
    <step>Create a new <b>Gameplay Ability</b> for your <b>primary attack</b>, using <code>CombatAbility_Attack</code> as the base class.</step>
    <step>Set the <b>Animation Montage</b> for the <b>primary attack</b> in the <b>Default Animation Montage</b>.</step>
    <step>Disable <b>Motion Warping</b>.</step>
    <step>Enable <b>debugging</b>.</step>
    <step>Add <code>Ability.Attack.Primary</code> to the <b>Ability Tags</b>, so it can be used for the activation.</step>
    <step>Add <code>Ability.Attack.Secondary</code> to the list of <b>Block Abilities with Tag</b>, to ensure your attacks won't interrupt each other.</step>
    <img src="p01g04_primary_gameplay_ability.png" alt="Primary Attack Ability" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Configure a damage Gameplay Effect" collapsible="true">
    <step>Create a new <b>Gameplay Effect</b> using <code>CombatEffect_MeleeHit</code> as the base class. It will be used by the secondary attack.</step>
    <step>Add <code>Combat.Effect.Damage.Knockback</code> to the list of Gameplay Tags <b>Added to the Effect</b>.</step>
    <step>In the <b>Execution list</b>, add a <b>Calculation Modifier</b> using <code>Combat.Data.Damage.Multiplier</code> and set a <b>Scalable Float</b> with a <b>Magnitude</b> of <code>1.5</code>.</step>
    <img src="p01g04_knockback_gameplay_effect.png" alt="Knockback Gameplay Effect" border-effect="line" thumbnail="true" width="600"/>
    <tip>Make sure to read about the <b><a href="cbt_effects.md#damage-modifier">Damage Modifier</a></b>, if you need a recap on why we are setting this value in this Gameplay Effect.</tip>
</procedure>

<procedure title="Configure a cost Gameplay Effect" collapsible="true">
    <step>Create a new <b>Gameplay Effect</b> using <code>GameplayEffect</code> as the base class. It will be used for by secondary attack.</step>
    <step>Add the <b>Additional Effects Gameplay Effect Component</b> and include <b>Cancel Stamina Regeneration</b> in the <b>On Application Gameplay Effects</b> list.</step>
    <step>Add a <b>Modifier</b> to reduce stamina by <code>5</code>.</step>
    <img src="p01g04_cost_gameplay_effect.png" alt="Cost Gameplay Effect" border-effect="line" thumbnail="true" width="600"/>
    <tip>Make sure to read about the <b><a href="cbt_effects.md#cancel-regeneration">Regeneration Cancellation</a></b>, if you need a recap on why we are adding the additional Gameplay Effect.</tip>
</procedure>

<procedure title="Configure the secondary attack ability" collapsible="true">
    <step>Create a new <b>Gameplay Ability</b> for your <b>secondary attack</b>, using <code>CombatAbility_Attack</code> as the base class.</step>
    <step>Set the new <b>Damage Gameplay Effect</b>, configured on the previous step, as the <b>Melee Damage Effect Class</b>.</step>
    <step>Set the <b>Animation Montage</b> for the <b>secondary attack</b> in the <b>Default Animation Montage</b>.</step>
    <step>Disable <b>Motion Warping</b>.</step>
    <step>Enable <b>debugging</b>.</step>
    <step>Set the new <b>Cost Gameplay Effect</b>, configured on the previous step, as the <b>Cost Effect Class</b>.</step>
    <step>Add <code>Ability.Attack.Secondary</code> to the <b>Ability Tags</b>, so it can be used for the activation.</step>
    <step>Add <code>Ability.Attack.Primary</code> to the list of <b>Block Abilities with Tag</b>, to ensure your attacks won't interrupt each other.</step>
    <img src="p01g04_secondary_gameplay_ability.png" alt="Secondary Attack Ability" border-effect="line" thumbnail="true" width="600"/>
</procedure>

<procedure title="Add abilities to the Player" collapsible="true">
    <step>
        <p>Open the <b>Ability Data Asset</b> created for the Player, and add the new abilities.</p>
        <img src="p01g04_ability_data.png" alt="Ability Bundle Ability" border-effect="line" thumbnail="true" width="600"/>
    </step>
</procedure>

<procedure title="Configure Player Inputs" collapsible="true">
    <step>Create an <b>Input Action</b> for the <b>Primary Attack</b>. Add a <b>Pressed</b> trigger. Map this <b>Input Action</b> to your <b>Input Mapping Context</b>, assigning the <b>Left Mouse Button</b> as the key. If you have a Gamepad, also map it to the <b>Face Button Left</b>.</step>
    <step>Create an <b>Input Action</b> for the <b>Secondary Attack</b>. Add a <b>Pressed</b> trigger. Map this <b>Input Action</b> to your <b>Input Mapping Context</b>, assigning the <b>Right Mouse Button</b> as the key. If you have a Gamepad, also map it to the <b>Face Button Top</b>.</step>
    <step>Add two <b>Input Handlers</b> to your <b>Input Setup Data Asset</b>, using the <b>Activate Ability by Tags</b> (<code>InputHandler_AbilityTag</code>) as the base.</step>
    <step>Set the correct <b>Input Actions</b> for each attack, and the correct Ability Tags defined earlier: <code>Ability.Attack.Primary</code> and <code>Ability.Attack.Secondary</code>.</step>
    <step>
        <p>When you are done, your <b>Input Setup Data Asset</b> should be similar to the following image.</p>  
        <img src="p01g04_attack_inputs.png" alt="Melee Attack Inputs" border-effect="line" thumbnail="true" width="600"/>
    </step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Click the <b>Play</b> button and execute your <b>primary</b> and <b>secondary</b> attacks, pressing the appropriate buttons.</step>
    <step>
        <p>Both your attacks should execute correctly, and you should see scan lines for the <b>debug</b>.</p>
        <img src="p01g04_results.gif" alt="Attacks" border-effect="line"/>
    </step>
    <tip>Since the <b>melee scans</b> are confirmed to be working correctly, you can <b>disable debug</b> in the <b>attack abilities</b>.</tip>
</procedure>
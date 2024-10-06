# Create Melee Attacks
<primary-label ref="combat"/>
<secondary-label ref="how-to"/>

This how-to will show you how to create your first **Attacks**, using a **Melee Weapon**.

<procedure title="Add the Melee Scan Sockets" collapsible="true">
    <step>
        <p>Open the <b>Static Mesh</b> for the Sword and add three <b>sockets</b> along the blade.</p>
        <p>Make sure to prefix your sockets with <code>sScan</code>. The prefix will be used shortly.</p>
        <img src="cbt_create_weapon_sockets_sword.png" alt="Sword Sockets" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Create the Animation Montage for a light attack" collapsible="true">
    <step>Create an <b>Animation Montage</b> based on an appropriate <b>Animation Sequence</b> that represents the <b>Light Attack</b>.</step>
    <step>In the Animation Montage, add the <b>Melee Scan Notify State</b> along the frames where the scan should happen.</step>
    <step>
        <p>In the Notify State <b>Details</b>, set the <b>Source</b> to <code>Weapon</code> and your <b>Scan Channel</b> to <code>Weapon</code>.</p>
        <img src="cbt_create_melee_anim_montage.png" alt="Melee Scan Notify State" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Configure the <b>Weapon query</b>, so it will obtain the sword from the <b>Weapon Manager</b>.</p>
        <img src="cbt_create_melee_anim_query.png" alt="Melee Scan Notify Query" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Create the Animation Montage for a heavy attack" collapsible="true">
    <step>Repeat the same steps from the previous procedure, this time for a <b>heavy attack</b>.</step>
</procedure>

<procedure title="Create the Light Attack Ability" collapsible="true">
    <step>Create a new <b>Gameplay Ability</b> for your <b>Light Attack</b>, using the <code>CombatAbility_Attack</code> as the base.</step>
    <step>In the <b>Details Tab</b>, enable the <b>Is Melee Attack</b> and disable <b>Is Ranged Attack</b> flags.</step>
    <step>Set the first <b>Animation Montage</b> for the <b>Light Attack</b> to the <b>Default Animation Montage</b>.</step>
    <step>Disable the <b>Motion Warping</b> functionality.</step>
    <step>
        <p>Add <code>Ability.Attack.Primary</code> to the <b>Ability Tags</b>, so it can be used for the activation.</p>
        <p>Add <code>Ability.Attack.Secondary</code> to the list of <b>Block Abilities with Tag</b>, to ensure your attacks won't interrupt each other.</p>
    </step>
    <step>
        <p>When you are done, your <b>Light Attack Ability</b> should be similar to the following image.</p>
        <img src="cbt_melee_attack_light.png" alt="Light Attack Ability" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Create the Heavy Attack Ability" collapsible="true">
    <step>Create a new <b>Gameplay Ability</b> for your <b>Heavy Attack</b>, using the <code>CombatAbility_Attack</code> as the base.</step>
    <step>In the <b>Details Tab</b>, enable the <b>Is Melee Attack</b> and disable <b>Is Ranged Attack</b> flags.</step>
    <step>Set the first <b>Animation Montage</b> for the <b>Heavy Attack</b> to the <b>Default Animation Montage</b>.</step>
    <step>Disable the <b>Motion Warping</b> functionality.</step>
    <step>
        <p>Add <code>Ability.Attack.Secondary</code> to the <b>Ability Tags</b>, so it can be used for the activation.</p>
        <p>Add <code>Ability.Attack.Primary</code> to the list of <b>Block Abilities with Tag</b>, to ensure your attacks won't interrupt each other.</p>
    </step>
    <step>
        <p>When you are done, your <b>Heavy Attack Ability</b> should be similar to the following image.</p>
        <img src="cbt_melee_attack_heavy.png" alt="Heavy Attack Ability" border-effect="line" thumbnail="true"/>
    </step>    
</procedure>

<procedure title="Add your Abilities to your character" collapsible="true">
    <tip>
        <p><b>GAS Frameworks</b></p>
        <p>You can add <b>Abilities</b> with any GAS framework. In this step, <b>Ninja GAS</b> will be used.</p>
    </tip>
    <step>
        <p>Create an <b>Ability Bundle</b> for the player and add the new abilities to it.</p>
        <img src="cbt_add_melee_attacks_with_ninja_gas.png" alt="Ability Bundle Ability" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Add the <b>Ability Bundle</b> to the <b>Ability System</b> in the <b>Player State</b>.</p>
        <img src="cbt_add_melee_attacks_register_bundle.png" alt="Ability Bundle Ability" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Configure your Player Inputs" collapsible="true">
    <tip>
        <p><b>Input Handling</b></p>
        <p>You can handle inputs with the <b>Enhanced Input</b> or a dedicated framework. In this step, <b>Ninja Input</b> will be used.</p>
    </tip>
    <step>Create an <b>Input Action</b> for the <b>Light Attack</b>. Add a <b>Pressed</b> trigger. Map this <b>Input Action</b> to your <b>Input Mapping Context</b>, assigning the <b>Left Mouse Button</b> as the key.</step>
    <step>Create an <b>Input Action</b> for the <b>Heavy Attack</b>. Add a <b>Pressed</b> trigger. Map this <b>Input Action</b> to your <b>Input Mapping Context</b>, assigning the <b>Right Mouse Button</b> as the key.</step>
    <step>Add two <b>Input Handlers</b> to your <b>Input Setup Data Asset</b>, using the <b>Activate Ability by Tags</b> as the base.</step>
    <step>Set the correct <b>Input Actions</b> for each attack, and the correct Ability Tags defined earlier: <code>Ability.Attack.Primary</code> and <code>Ability.Attack.Secondary</code>.</step>
    <step>
        <p>When you are done, your <b>Input Setup Data Asset</b> should be similar to the following image.</p>  
        <img src="p01g04_attack_inputs.png" alt="Melee Attack Inputs" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Execute your melee attacks" collapsible="true">
    <step>Click the <b>Play</b> button.</step>
    <step>
        <p>Press the buttons assigned to your attacks, <b>Left and Right Mouse buttons</b>. Your attacks should execute.</p>
        <img src="cbt_melee_attacks_no_debug.gif" alt="Light and Heavy Attacks" border-effect="line"/>
    </step>
</procedure>

<procedure title="Enable the Attack Debug" collapsible="true">
    <step>Open your <b>Attack Abilities</b> and check <b>Enable Debug</b> property.</step>
    <step>Click the <b>Play</b> button.</step>
    <step>
        <p>Press the buttons assigned to your attacks, <b>Left and Right Mouse buttons</b>, you should see the melee traces. When you are done, uncheck the <b>Enable Debug</b> property from the <b>Attack Abilities</b>.</p>
        <img src="cbt_melee_attacks_with_debug.gif" alt="Light and Heavy Attacks with Debug" border-effect="line"/>
    </step>
</procedure>

<seealso style="cards">
   <category ref="related">
        <a href="cbt_setup.md" summary="Configure the Combat System, including collision channels.">Setup</a>
        <a href="cbt_melee_combat.md" summary="Overview of the all participants for the Melee Combat functionality.">Melee Combat</a>
        <a href="gas_overview.md" summary="Base configuration and utility for the Gameplay Ability System (GAS).">Ninja G.A.S.</a>
        <a href="ipt_overview.md" summary="Dedicated and reusable Handlers for the Enhanced Input. Integrated with the Gameplay Ability System.">Ninja Input</a>
    </category>
</seealso>
# React to Fatal Damage
<secondary-label ref="guide"/>

<video src="https://youtu.be/koGpsk_2F-s" preview-src="sc_thumbnail_p01g06.png" width="800" />

Continuing the damage handling, we will handle fatal damage, which starts the death flow and activates the
**Death Ability**.

<procedure title="Configure the default death animation" collapsible="true">
    <step>For the default death reaction, we will use <b>directional animations</b>. Create an <b>Animation Montage</b> and organize all the sequences.</step>
    <step>Create <b>Montage Sections</b> for each sequence, with appropriate names, based on their directions.</step>
    <step>Add a looping section where the ability is in a <b>static pose</b>, it will ensure that the character never resets to the wrong stance.</step>
    <step>Organize all montage sections so main sections go into their static parts, which will then loop into themselves.</step>
    <step>Add the <b>Ragdoll</b> and the <b>Death</b> notifies in the appropriate frames..</step>
    <img src="p01g06_death_animation.png" alt="Default Death Animation Montage" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the strong death animation" collapsible="true">
    <step>For the strong death reaction, repeat the same steps as before.</step>
    <img src="p01g06_death_animation_strong.png" alt="Strong Death Animation Montage" thumbnail="true" border-effect="line" width="600"/>
    <tip>This is optional, and you do not need to use directional reactions if they are not available.</tip>
</procedure>

<procedure title="Configure the Death Gameplay Ability" collapsible="true">
    <step>Create a new Gameplay Ability extending on <code>CombatAbility_Death</code>.</step>
    <step>Change the Animation Provider to <b>Directional Hits</b>.</step>
    <step>Adjust the <b>Hit Location Weight</b> and <b>Attacker Location Weight</b> if necessary.</step>
    <step>Map the <b>direction ranges</b> to the correct animation sections, you can add, remove or completely change the ranges as needed.</step>
    <step>Set the default Animation Montage and default Montage Section.</step>
    <step>The <b>Cancel Abilities With Tag</b> should be correct, but feel free to adjust these Gameplay Tags if you need. This container is used to indicate abilities that should be cancelled when the death ability activates.</step>
    <step>Add <code>Combat.State.Opportunity.Victim</code> to your list of <b>Activation Blocked Tags</b>. This should avoid conflicts between the Death Animation and the Opportunity System.</step>
    <step>Add the new Gameplay Ability to the <b>Ability Data Asset</b> created for the enemy character, so it is added by default.</step>
    <img src="p01g06_death_ability.png" alt="Death Gameplay Ability" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Update the Damage Data Asset" collapsible="true">
    <step>Navigate to the <b>Damage Data Asset</b> created and assigned to the enemy in the previous guide.</step>
    <step>Set the <b>Death Time Limit</b> to <code>5.0</code>. This will ensure that the character is destroyed even if something goes wrong in the Death Ability or Animation Notify.</step>
    <step>Add the <b>Dissolve Handler</b> which will update the defined material parameters, <b>in all character meshes</b>, based on the provided curves</step>
    <tabs>
        <tab title="Damage Data Asset">
            <p>The material used has two parameters: <b>Dissolve</b> and <b>Dissolve Emissive</b>, each one with their own <b>float curve</b>.</p>
            <img src="p01g06_damage_data.png" alt="Damage Data Asset" thumbnail="true" border-effect="line" width="600"/>
        </tab>
        <tab title="Dissolve Curve">
            <p>Curves are <b>value over time</b> and may start at zero or have a <b>delay</b></p>
            <img src="p01g06_dissolve_curve.png" alt="Dissolve Curve Example" thumbnail="true" border-effect="line" width="600"/>
        </tab>
    </tabs>
    <tip>
        <p>The Dissolve Handler requires adjustments in your Materials, so they can actually adjust the <b>emissivity</b> and <b>opacity</b> based on certain parameter values.</p>
        <p>You will need to create that <b>Material Function</b> or use one of the many dissolve materials available in the Fab Store!</p>
    </tip>
</procedure>

<procedure title="Test everything" collapsible="true">
    <note>Change the <b>Base Damage</b> attribute in your <b>Player Attribute Table</b> to a higher value, so you can defeat the enemy with fewer hits!</note>
    <step>Press <b>play</b> and attack the enemy.</step>
    <step>You should see the <b>Hit Reactions</b> from the previous guide.</step>
    <step>On <b>fatal damage</b>, the enemy should play the appropriate death animation, considering the <b>damage direction</b>.</step>
    <step>If fatal damage is applied from a <b>heavy attack</b>, the appropriate animation for <b>strong attacks</b> should be used.</step>
    <img src="p01g06_results_b.gif" alt="Results" border-effect="line"/>
</procedure>
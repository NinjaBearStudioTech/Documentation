# Track Enemy Attributes
<secondary-label ref="guide"/>
<secondary-label ref="advanced"/>

Now that we created the first **Combat Widget**, let's create a more advanced one, the **Overhead Info**. It will be
used with the enemy character, to show **attributes** and **status effects**.

This is an <b>advanced topic</b>, in a sense that will be leveraging many ways to use UMG Viewmodels, not just binding
them directly to widget components, but creating functions to implement more interesting features.

<procedure title="Review your Enemy Attributes" collapsible="true">
    <step>Open your <b>Combat Attribute Data Table</b> for the Enemy.</step>
    <step>Check the <b>Health</b> attribute, to ensure it has valid values.</step>
</procedure>

<procedure title="Create the Enemy Overhead Widget" collapsible="true">
    <step>Create a new widget, based on <code>NinjaCombatBaseWidget</code>.</step>
    <step>
        <p>In the <b>Designer</b> tab, add a <b>Vertical Box</b> with a <b>Text Block</b> for the Damage, a <b>Progress Bar</b> for Health, another <b>Progress Bar</b> for the Stagger meter and a <b>Uniform Grid Panel</b> for Status Effects.</p>
        <img src="p02g04_enemy_widget_designer.png" alt="Enemy Widget Design" thumbnail="true" border-effect="line" width="600"/>
        <tip>Feel free to create any design that is appropriate for your game, but make sure to use the necessary components listed above.</tip>  
    </step>
    <step>
        <p>In the <b>Widget Graph</b>, create the following <b>Variables</b>:</p>
        <ul>
            <li><code>LockedOnTarget</code>: Boolean</li>
            <li><code>AccumulatedDamage</code>: Float</li>
            <li><code>DamageTextTimerHandle</code>: Timer Handle</li>
            <li><code>AutoDisplayTimerHandle</code>: Timer Handle</li>
        </ul>
    </step>
    <step>
        <p>Implement the <code>Construct</code> and <code>Destruct</code> functions, used to set initial visibility and clean-up timer handles.</p>
        <img src="p02g04_widget_lifecycle.png" alt="Widget Lifecycle" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Create two <b>Custom Events</b>, that will be implemented later: <code>AddDamage</code> and <code>ResetDamage</code>.</step>
    <step>
        <p>Create a <b>Custom Event</b>, <code>HideOverhead</code>, that <b>resets the damage</b> and <b>collapses the widget</b>.</p>
        <img src="p02g04_hide_overhead.png" alt="Hide Overhead Event" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>ShowWidgetFromIncomingDamage</code>, that will show the widget when damage is received.</p>
        <img src="p02g04_show_widget_from_incoming_damage.png" alt="Show Widget From Incoming Damage" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>ResetState</code>, that resets this widget when a new actor is selected.</p>
        <img src="p02g04_reset_state.png" alt="Reset State" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>UpdateStatusEffects</code>, that adds an icon from an active Gameplay Effect, with a valid Combat UI Data.</p>
        <img src="p02g04_update_status_effects.png" alt="Reset State" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>SetTargetLock</code>, that shows or hides the widget when the player is locking on this target.</p>
        <img src="p02g04_set_target_lock.png" alt="Set Target Lock" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>SetCriticalDamage</code>, that will set a different color for the damage block, when a critical hit occurs.</p>
        <img src="p02g04_set_critical_damage.png" alt="Set Critical Damage" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>SetDeathState</code>, that will hide the widget when the enemy dies.</p>
        <img src="p02g04_set_death_state.png" alt="Set Death State" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>SetPoiseValue</code>, that shows the Stagger Progress Bar when there's any ongoing value.</p>
        <img src="p02g04_set_poise_value.png" alt="Set Poise Value" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Create a <b>Function</b>, <code>SetStaggerValue</code>, that modifies the Poise Progress Bar when the enemy is staggered.</p>
        <img src="p02g04_set_stagger_value.png" alt="Set Stagger Value" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>With all the support functions done, implement the <code>AddDamage</code> and <code>ResetDamage</code> to accumulate and reset damage.</p>
        <img src="p02g04_add_reset_damage.png" alt="Add and Reset Damage" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>In the <b>Viewmodels</b> tab, add the following <b>Combat Viewmodels</b>, setting their <b>Creation Type</b> to <b>Create Instance</b>.</p>
        <ul>
            <li><code>CombatVitals</code>: Exposes the main combat attributes.</li>
            <li><code>PoiseAndStagger</code>: Exposes the poise state and stagger progress.</li>
            <li><code>Damage</code>: Exposes information about the last damage received.</li>
            <li><code>StatusEffects</code>: Exposes all active status effects, applied from Gameplay Effects.</li>
            <li><code>TargetLock</code>: Exposes the Current Target Lock state on this character.</li>
        </ul>
        <tip>
            <p>If you cannot see the Viewmodel or View Bindings tab, enable them in the <b>Window</b> menu.</p>
            <p>You can find more information about all Viewmodels provided by the Combat Framework in the <b><a href="cbt_user_interface.md"/></b> page.</p>
        </tip>
    </step>
    <step>
        <p>Bind the Combat Viewmodels to the correct properties and functions.</p>
        <img src="p02g04_viewmodel_bindings.png" alt="Viewmodel Bindings" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Update the Enemy Blueprint" collapsible="true">
    <step>
        <p>Open your <b>Enemy Blueprint</b> and add a <code>NinjaCombatWidgetComponent</code> to it.</p>
        <tip>You should add this to your base Blueprint or base C++ class, whichever is the most appropriate location in your character hierarchy.</tip>
    </step>
    <step>Adjust the proper location for this widget, probably placing it above the character's head.</step>
    <step>Set the <b>Space</b> to <b>Screen</b>.</step>
    <step>Set the <b>Widget Class</b> crated in the previous step.</step>
    <img src="p02g04_widget_component.png" alt="Viewmodel Bindings" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>Play</b> and attack your enemy, the overhead widget should show up and reflect incoming damage.</step>
    <step>Lock on your target and the overhead widget should also appear. Unlock and the widget should disappear.</step>
    <step>Notice how critical damage, poise damage, stagger state and status effects (if you have them) are displayed.</step>
    <step>The widget will also disappear when the enemy dies.</step>
</procedure>
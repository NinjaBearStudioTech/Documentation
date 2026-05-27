# Orchestrating Combos
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to build a basic combo flow where Gameplay Abilities advance from one attack to the next using the 
**Combo Ability**, **Combo Manager**, and **Combo Windows**.

For a deeper explanation of the systems and settings used by these examples, see the [**related concepts**](cbt_concepts_combos.md).

## Prerequisites

### Activatable Abilities

A combo requires abilities that can be activated. These are usually **Attack** or **Cast** Gameplay Abilities, but you 
can activate any type of ability required by your scenario.

### Input Handling

Make sure your input setup can activate the Combo Ability and advance the combo by sending the appropriate Gameplay Events. 
For more information, see [**Combat and Input Integration**](integration_combat_input.md).

Integration with Ninja Input is optional, but input handling for ability activation should already be configured.

## Combo Manager

Combos are orchestrated by the **Combo Manager**, an Actor Component that implements `CombatComboManagerInterface`. The
default implementation uses the **State Tree Component**, and combos are authored as **State Tree assets**.

To start using the Combo System, add a **Combo Manager Component** to your character and implement the appropriate getter
function from the **Combat System Interface**.

<procedure title="Add the Combo Manager Component" collapsible="true" default-state="collapsed">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatComboManagerComponent</code>.</step>
    <step>Implement <code>GetComboManagerComponent</code> from the <code>CombatSystemInterface</code>, returning your <b>Combo Manager Component</b>.</step>
</procedure>

## Combo Windows

The first step in authoring a combo is configuring the **Animation Montages** used by the combo abilities to include a
**Combo Window Animation Notify State**, which marks the frames during which transitions to the next combo state are allowed.

<procedure title="Add Combo Windows" collapsible="true" default-state="collapsed">
    <step>Open the <b>Animation Montage</b> used by your first <b>Gameplay Ability</b> in the combo (e.g. a melee attack).</step>
    <step>
        <p>Add a <b>Combo Window</b> Notify State to the Animation Montage. It should cover the range of frames during which the next combo input can be triggered.</p>
        <img src="cbt_guide_combo_animation_notify_state.png" alt="Combo Window Animation Notify State" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Repeat this step for all <b>Animation Montages</b> used in the combo.</p>
        <tip>
            <p><b>Last Animation and Looping</b></p>
            <p>If you want the combo to <b>loop</b>, add a Combo Window Notify to the final montage. Otherwise, leave it out to let the combo end naturally.</p>
        </tip>
    </step>
    <step>
        <p>Optionally, with <b>Ninja Input</b>, you can add the <b>Input Buffer</b> Notify State to the same Animation Montage.</p>
        <p>This buffer should start at some point before the Combo Window and end a few frames <b>after the Combo Window opens</b>.</p>
        <img src="cbt_guide_combo_animation_notify_buffer.png" alt="Input Buffer Animation Notify State" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

## Linear Combo

Combos are defined using a **State Tree** that uses the **Combat Combo Tree Schema**. The simplest type of combo is the
linear combo, which uses one transition path where each successful combo input advances to the next attack in sequence.

<procedure title="Create a Linear Combo Tree" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_combo_tree_linear_combo.png" alt="Linear Combo State Tree" border-effect="line" thumbnail="true"/>
    <step>
        <p>In your <b>Content Browser</b>, create a new <b>State Tree</b> and set its <b>Schema</b> to <b>Combat Combo</b>.</p>
    </step>
    <step>
        <p>Add a new <b>Evaluator</b>, select <b>Combo State</b>, and bind the <b>Combo State</b> to the one available from the <b>Context</b>.</p>
        <tip>
            <p><b>Combo Trees in Unreal Engine 5.3</b></p>
            <p>If you're using <b>Unreal Engine 5.3</b>, also add the <b>Combo Manager</b> Evaluator to retrieve the component from the <b>Actor</b> context. This is not required in later versions.</p>
        </tip>
    </step>
    <step>
        <p>From the <b>Root Node</b>, add a new <b>Child State</b> for the <b>Light Attacks</b>.</p>
    </step>
    <step>
        <p>From the <b>Light Attacks</b> node, add a new <b>Child State</b> for the first attack.</p>
        <p>Add an <b>Activate Combo Ability Task</b>, bind the <b>Combo Manager</b>, and set the correct <code>Ability Tags</code> (e.g., <code>Combat.Ability.Attack.Light.01</code>).</p>
        <p>This tag matches the <b>Activation Tag</b> from the <b>Gameplay Ability</b> that represents this attack.</p>
    </step>
    <step>
        <p>Add a <b>Sibling State</b> for the second attack and configure it with the next <code>Ability Tag</code> (e.g., <code>Combat.Ability.Attack.Light.02</code>).</p>
        <p>Add an <b>Enter Condition</b> checking if <code>ComboState.ComboCount</code> equals <code>1</code>.</p>
    </step>
    <step>
        <p>Create additional states as needed for your combo sequence. Make sure each state uses the correct <code>Ability Tag</code> and increments its <b>Enter Condition</b> appropriately.</p>
    </step>
    <step>
        <p>Return to the <b>first attack state</b> and add two <b>Transitions</b>.</p>
        <p>For the first one, set the <b>Trigger</b> to <b>Event</b>, use <code>Combat.Event.Combo.Attack.Primary</code> as the <b>Event Tag</b>, and point it to the second state.</p>
        <p>For the second one, set the <b>Trigger</b> to <b>On State Complete</b> and configure the transition to <b>Tree Succeeded</b>.</p>
    </step>
    <step>
        <p>Repeat this for all attack states, using the same <b>Event Tag</b>, but pointing each transition to the next state in the sequence.</p>
        <tip>
            <p><b>Non-Looping Combo</b></p>
            <p>Ending in <b>Tree Succeeded</b> prevents the combo from looping. To support looping combos, add a transition back to the first state and set the first task to <b>Reset Count</b>.</p>
        </tip>
    </step>
</procedure>

## Branching Combo

A branching combo allows different inputs or events to transition into different follow-up attacks from the same state.

<procedure title="Create a Branching Combo Tree" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_combo_tree_branching_combo.png" alt="Branching Combo State Tree" border-effect="line" thumbnail="true"/>
    <step>
        <p>Duplicate your <b>Linear Combo Tree</b>.</p>
    </step>
    <step>
        <p>From the <b>Root Node</b>, add a new <b>Child State</b> for the <b>Heavy Attacks</b>.</p>
    </step>
    <step>
        <p>From the <b>Heavy Attacks</b> node, add a new <b>Child State</b> for the first attack.</p>
        <p>Add an <b>Activate Combo Ability Task</b>, bind the <b>Combo Manager</b>, and set the correct <code>Ability Tags</code> (e.g., <code>Combat.Ability.Attack.Heavy.01</code>).</p>
        <p>Add an <b>Enter Condition</b> checking if <code>ComboState.ComboCount</code> equals <code>2</code>, or any other number that represents this attack's index in your own combo.</p>
    </step>
    <step>
        <p>Create additional states as needed for your combo sequence. Make sure each state uses the correct <code>Ability Tag</code> and increments its <b>Enter Condition</b> appropriately.</p>
    </step>
    <step>
        <p>Return to the <b>Light Attack 02</b> state and add a new <b>Transition</b>.</p>
        <p>Set the <b>Trigger</b> to <b>Event</b>, use <code>Combat.Event.Combo.Attack.Secondary</code> as the <b>Event Tag</b>, and point it to <b>Heavy Attack 01</b>.</p>
    </step>
    <step>
        <p>Add <b>Event</b> transitions between heavy attack states as needed, using <code>Combat.Event.Combo.Attack.Secondary</code> as the <b>Event Tag</b>.</p>
        <p>For each heavy attack state, also add an <b>On State Complete</b> transition to <b>Tree Succeeded</b>.</p>
    </step>
</procedure>

## Multiple Starting Points

A combo can also support multiple entry states, allowing different abilities or inputs to begin different combo paths.

To accomplish this, two things must be configured:

1. The **Combo Ability** must activate automatically. This can be done by adding the `Ability.Passive` tag to the list of **Ability Tags**.
2. The **Combo State Tree** must start in a waiting state that keeps the **Combo Window** open and listens for **Combo Events**.

<procedure title="Create a Combo Tree with Multiple Starting Points" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_combo_tree_multiple_starting_points.png" alt="Multiple Starting Points Combo State Tree" border-effect="line" thumbnail="true"/>
    <step>
        <p>Duplicate your <b>Branching Combo Tree</b>.</p>
    </step>
    <step>
        <p>From the <b>Root Node</b>, add a new <b>Child State</b> named <b>Waiting for Event</b> that will wait for any supported <b>Combo Events</b>.</p>
    </step>
    <step>
        <p>Add a <b>Set Combo Window</b> task and set the <b>New Combo Window State</b> to <b>Open</b>.</p>
    </step>
    <step>
        <p>Add a <b>Delay</b> task and set it to <b>Run Forever</b>.</p>
    </step>
    <step>
        <p>Add transitions for each <b>Combo Event</b> supported by the Combo Tree.</p>
        <p>For events tagged with <code>Combat.Event.Combo.Attack.Primary</code>, add a transition to the <b>Light Attacks</b> node.</p>
        <p>For events tagged with <code>Combat.Event.Combo.Attack.Secondary</code>, add a transition to the <b>Heavy Attacks</b> node.</p>
    </step>
</procedure>

## Combo Gameplay Ability

The **Combo Ability** references the Combo Tree and grants the Gameplay Abilities that can be triggered by the combo. 
Once configured, it acts as the orchestration ability that starts and drives the Combo Manager.

<procedure title="Configure the Combo Gameplay Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_combo_ability.png" alt="Combo Gameplay Ability" border-effect="line" thumbnail="true"/>
    <step>
        <p>In your Combo Ability folder, create a new <b>Gameplay Ability Blueprint</b> using <code>CombatAbility_Combo</code> as the base class.</p>
    </step>
    <step>
        <p>Set the appropriate <b>Combo State Tree</b> asset as the ability's <b>Combo Tree</b>.</p>
    </step>
    <step>
        <p>Add all Gameplay Abilities orchestrated by this combo to the list of <b>Ability Classes</b>.</p>
        <tip>
            <p><b>Ability Management</b></p>
            <p>These abilities are granted and removed together with the Combo Ability, so they do not require separate management.</p>
        </tip>
    </step>
    <step>
        <p>Configure the <b>Ability Tags</b> used to activate this Combo Ability.</p>
        <tip>
            <p><b>Passive Ability</b></p>
            <p>If this combo handles multiple starting points, also add <code>Ability.Passive</code> to the list of <b>Ability Tags</b>. With this tag, the ability activates automatically once its avatar is set.</p>
        </tip>
    </step>
</procedure>

Once the Combo Ability is granted, activating it will start the configured Combo Tree. From there, Combo Windows and 
Gameplay Events determine which ability is triggered next.
# Combo Branching
<primary-label ref="combat"/>

By default, combos are represented by a **State Machine**, which means they naturally support **branching logic**. This 
allows players to transition from one attack into multiple potential follow-ups, depending on input or context.

A common use case is giving players the choice between a _light_ and a _heavy_ attack, or between _ground_ and _aerial_ 
follow-ups. Branching opens the door to more **dynamic and expressive combat sequences**.

## Branching Combo States

Branching is handled through transitions triggered by different **State Tree Event Tags**.

In the previous chapter, we used a single event tag, `Combat.Event.Combo.Attack.Primary`, for a linear combo. Now, we'll 
introduce branching by adding an alternate event, such as `Combat.Event.Combo.Attack.Secondary`.

<procedure title="Configuring Branching" collapsible="true" default-state="expanded">
    <step>Open your existing <b>State Tree</b> and group the current primary attacks under a new <b>Parent State</b> (e.g., <b>Primary Attacks</b>).</step>
    <step>Add a <b>Sibling State</b> named <b>Secondary Attacks</b>.</step>
    <step>Within <b>Secondary Attacks</b>, create a <b>Child State</b> for the first secondary attack. Set the <b>Enter Condition</b> to <code>ComboState.ComboCount == 2</code>.</step>
    <step>Add an <b>Activate Combo Ability</b> task and set the activation tag to <code>Combat.Ability.Attack.Combo01E</code>.</step>
    <step>Since this is a final attack, add an <b>On State Complete</b> transition to <b>Tree Succeeded</b>.</step>
    <img src="cbt_wpatk_combo_state_tree_07.png" alt="State Tree Branching" border-effect="line" thumbnail="true"/>
</procedure>

Next, add another branching option and set up transitions from the Primary Attack states to the new Secondary ones.

<procedure title="Finishing the Branching Setup" collapsible="true" default-state="expanded">
    <step>
        <p>Duplicate <b>Secondary Attack 01</b>, update its <b>Enter Condition</b> to require <code>ComboCount == 3</code>, and change the activation tag to <code>Combat.Ability.Attack.Combo01F</code>.</p>
        <img src="cbt_wpatk_combo_state_tree_08.png" alt="State Tree Branching" border-effect="line" thumbnail="true"/>    
    </step>
    <step>
        <p>In <b>Primary Attack 02</b>, add a new <b>Transition</b> to <b>Secondary Attack 01</b>, using the event tag <code>Combat.Event.Combo.Attack.Secondary</code>.</p>
        <img src="cbt_wpatk_combo_state_tree_09.png" alt="State Tree Branching" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Repeat the same step for <b>Primary Attack 03</b>, adding a transition to <b>Secondary Attack 02</b>.</p>
        <img src="cbt_wpatk_combo_state_tree_09.png" alt="State Tree Branching" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

This Combo State Tree is now fully configured with branching:

- It includes **four Primary Attacks** and **two Secondary Attacks**.
- **Primary Attacks 2 and 3** can either **continue linearly** or **branch** into their respective Secondary Attacks.
- **Primary Attack 4** and both Secondary Attacks are **final nodes** that end the combo.

## Input Handling
Updating your inputs to support branching is straightforward, but the exact approach depends on how your **Combo Ability** 
is configured to handle events.

- **Gameplay Tag Mode**: Your input logic must send distinct events for each branch—typically `Combat.Event.Combo.Attack.Primary` (already covered) and `Combat.Event.Combo.Attack.Secondary` for the branching path.
- **Input Action Mode**: Ensure your secondary input (e.g., a different attack button) is mapped to trigger `Combat.Event.Combo.Attack.Secondary`. The Combo Ability will internally map this to the correct transition.

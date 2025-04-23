# Combos
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The Combo System orchestrates <b>Gameplay Abilities</b> triggered by <b>player input</b> or <b>AI events</b>.</li>
        <li>Combos are authored using <b>State Trees</b>, offering flexible support for <b>attack sequences</b>, <b>branching logic</b>, and <b>dynamic substitutions</b>.</li>
        <li>Any Gameplay Ability can be used in a combo, including <b>Attack Abilities</b>, <b>Cast Abilities</b>, and custom abilities.</li>
    </ul>
</tldr>

A **combo** is a sequence of **attacks** (or other abilities) triggered by the player or an AI agent by inputting specific 
commands within a time-limited **combo window**.

The Combo System is designed to leverage core Unreal Engine features, allowing you to author combos in a **visual and 
modular** way—with little to no code and no need for custom tooling or UI extensions.

## Combo Manager
Combos are orchestrated by the **Combo Manager**, an Actor Component that implements `CombatComboManagerInterface`. The 
default implementation uses the **State Tree Component**, and combos are authored as **State Tree assets**.

To start using the Combo System, add a **Combo Manager Component** to your character and implement the appropriate getter
function from the **Combat System Interface**.

<procedure title="Adding the Combo Manager Component" collapsible="true" default-state="expanded">
    <step>In your Character Blueprint or base class, add <code>NinjaCombatComboManagerComponent</code>.</step>
    <step>Implement <code>GetComboManagerComponent</code> from the <code>CombatSystemInterface</code>, returning your <b>Combo Manager Component</b>.</step>
</procedure>

## Combo States
Each ability in a combo is represented by a **state** in the **State Tree**, at least in the default Combo Manager implementation.
**State transitions** are driven by **State Tree Events**, which must be explicitly triggered, typically via **player input** 
or **AI logic**, during a designated **combo window**.

The first step in authoring a combo is configuring the **Animation Montages** used by the combo abilities to include a
**Combo Window Animation Notify State**, which marks the frames during which transitions to the next combo state are allowed.

<procedure title="Configuring Combo Windows" collapsible="true" default-state="expanded">
    <step>Open the <b>Animation Montage</b> used by your first <b>Gameplay Ability</b> in the combo (e.g. a melee attack).</step>
    <step>
        <p>Add a <b>Combo Window</b> Animation Notify State to the montage. It should cover the range of frames during which the next combo input can be triggered.</p>
        <img src="cbt_wpatk_combo_anim_notify.png" alt="Combo Anim Notify" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Repeat this step for all Animation Montages used in the combo.</p>
        <tip>
            <p><b>Last Animation and Looping</b></p>
            <p>If you want the combo to <b>loop</b>, add a Combo Window Notify to the final montage. Otherwise, leave it out to let the combo end naturally.</p>
        </tip>
    </step>
</procedure>

At this stage, you can create your **Gameplay Abilities**. These can be [](cbt_melee_attacks.md), [](cbt_ranged_attacks.md), 
[](cbt_casts.md), or any other ability, even those not directly related to Ninja Combat.

> **Ability Tags**
>
> When creating your combo-related abilities, make sure to assign them meaningful **Gameplay Tags**. These tags are
> used by the **Combo State Tree** to activate the correct abilities during the combo sequence.
{style=note}

> **Tag Clashes**
>
> The primary **Combo Ability** uses the `Combat.Ability.Combo` tag. Avoid using this tag or its prefix in your
> actual attack abilities. Doing so can cause the Combo Ability to re-activate itself and unintentionally reset the combo.
{style=warning}

## State Tree
With all Gameplay Abilities prepared, it’s time to create the **State Tree** that defines how the combo flows, including
attack order, branching paths, and looping options.

<procedure title="Creating a Combo Tree" collapsible="true" default-state="expanded">
    <step>In your <b>Content Browser</b>, create a new <b>State Tree</b> and set its <b>schema</b> to <b>Combat Combo</b>.</step>
    <step>
        <p>Add a new <b>Evaluator</b>, select <b>Combo State</b>, and bind the <b>Combo State</b> to the one available from the <b>Context</b>.</p>
        <img src="cbt_wpatk_combo_state_tree_01.png" alt="State Tree Combo State Context" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>Combo Trees in Unreal Engine 5.3</b></p>
            <p>If you're using <b>Unreal Engine 5.3</b>, also add the <b>Combo Manager</b> Evaluator to retrieve the component from the <b>Actor</b> context. This is not required in later versions.</p>
        </tip>
    </step>
    <step>
        <p>From the <b>Root Node</b>, add a new <b>Child State</b>. In this state, add an <b>Activate Combo Ability Task</b>, bind the <b>Combo Manager</b>, and set the correct <code>Ability Tags</code> (e.g., <code>Combat.Ability.Attack.Combo01A</code>).</p>
        <img src="cbt_wpatk_combo_state_tree_02.png" alt="State Tree Combo State Attack 02" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Add a <b>Sibling State</b>, configure it with the next <code>Ability Tag</code> (e.g., <code>Combat.Ability.Attack.Combo01B</code>), and add an <b>Enter Condition</b> checking if <code>ComboState.ComboCount</code> equals <code>1</code>.</p>
        <img src="cbt_wpatk_combo_state_tree_03.png" alt="State Tree Combo State Attack 03" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Create additional states as needed for your combo sequence. Ensure each state's <b>Enter Condition</b> is incremented appropriately, and each uses the correct tag.</p>
        <img src="cbt_wpatk_combo_state_tree_04.png" alt="State Tree Combo State Attack 04" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>Linear Combo</b></p>
            <p>This example creates a linear attack sequence. Branching and conditional combos will be covered later.</p>
        </tip>
    </step>
    <step>
        <p>Return to the <b>first attack state</b> and add a <b>Transition</b>. Set the <b>Trigger</b> to <b>Event</b>, use <code>Combat.Event.Combo.Attack.Primary</code> as the <b>Event Tag</b>, and point it to the second state.</p>
        <img src="cbt_wpatk_combo_state_tree_05.png" alt="State Tree Combo State Attack 05" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Repeat for all states, using the same <b>Event Tag</b>, but adjusting the <b>Next State</b> each time. For the <b>last attack</b>, add an <b>On State Complete</b> transition to <b>Tree Succeeded</b>.</p>
        <img src="cbt_wpatk_combo_state_tree_06.png" alt="State Tree Combo State Attack 06" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>Non-Looping Combo</b></p>
            <p>Ending in <b>Tree Succeeded</b> prevents the combo from looping. To support looping combos, add a transition back to the first state and set the first task to <b>Reset Count</b>.</p>
        </tip>
    </step>
</procedure>

We’ll revisit this State Tree later to explore more advanced features like branching, conditions, and loopable sequences.
For now, you have a **linear combo** that flows cleanly from one attack to the next and **ends the combo** after the final hit.

## Combo Ability
The **Combo Ability** is responsible for **orchestrating** abilities based on its own **activation** and follow-up **gameplay events**.  
Any `GameplayAbility` - including melee attacks, spells, or custom logic - can be used in a combo.

The Combo Ability can also **automatically grant and remove** any supporting abilities needed by the combo.

<img src="cbt_combo_ability.png" alt="Combo Ability" thumbnail="true" border-effect="line"/>

| Property                  | Description                                                                                                                                |
|---------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| Combo Tree                | The **State Tree Asset** that defines the combo flow and transitions.                                                                      |
| Ability Classes           | **Supporting Abilities** required by the combo. These are automatically granted along with the Combo Ability.                              |
| Event Mode                | How combo **events** are interpreted. You can use direct **gameplay tags** or **input action mappings**.                                   |
| Event Mappings            | A map of Input Actions and Event Tags that should be sent to the Combo State Tree. Only used if the Event Mode is set to **Input Action**. | 
| Combo Window Effect Class | Optional Gameplay Effect applied to the character during the active **combo window**. Useful for visuals or reactions.                     |

The Combo Ability expects two types of input:

- First, the standard **activation input**, which usually triggers the initial combo attack;
- Then, a sequence of **gameplay events**, which advance the combo during the **combo window** defined in each ability's animation.

The exact gameplay event used depends on the configured **Event Mode**:

- **Gameplay Tag**: The received gameplay event’s tag is forwarded directly to the State Tree. This tag must match one of the **transition tags** defined in the State Tree (e.g. `Combat.Event.Combo.Attack.Primary`).
- **Input Action**: The received gameplay event should use the tag `Combat.Event.Combo.Attack`. The **payload** must include the `InputAction` that triggered it. This input is then mapped to a specific **event tag** used by the State Tree.

If you're using **Ninja Input**, or any other input system, the next chapter covers how to set up input actions and 
gameplay events accordingly. Otherwise, if your input setup is already complete, you're ready to use the Combo Ability 
with your State Tree.

# Combo System
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>Combo Manager</b> is the <b>backbone</b> of the Combo System.</li>
        <li>Combos are defined by a <b>State Tree</b> and a <b>Gameplay Ability</b>.</li>
        <li>Each <b>Attack</b> is defined by its own <b>Attack Ability</b>.</li>
        <li>The <b>Combo Window</b> is defined by the <b>Combo Window Anim Notify State</b>.</li>
        <li>Details like the <b>Combo Window State</b> and <b>Combo Count</b> are exposed to the UI by the <b>Combo Viewmodel</b>.</li>
    </ul>
</tldr>

The **Combo System** is designed to create fluid and dynamic **combat sequences** by chaining attacks together, based on 
**player input**. It supports **branching** into different attacks, based on certain pre-defined **conditions**.

<code-block lang="mermaid">
sequenceDiagram
    PlayerInput->>ComboAbility: input received
    activate ComboAbility
        ComboAbility->>ComboManager: start combo
        activate ComboManager
            ComboManager->>ComboSetupData: get FSM
            ComboManager-->>ComboAbility: combo FSM
        deactivate ComboManager
        loop In Combo
            ComboAbility->>ComboManager: in combo window?
            ComboManager-->>ComboAbility: yes
            ComboAbility->>ComboManager: advance combo
            activate ComboManager
                ComboManager->>ComboManager: increment combo
                ComboManager->>ComboFSM: trigger transition event
                activate ComboFSM
                    ComboFSM->CombatAbility: activate
                    activate CombatAbility
                        CombatAbility->>CombatAbility: do stuff
                        CombatAbility-->>ComboFSM: finish state
                    deactivate CombatAbility
                deactivate ComboFSM    
            deactivate ComboManager
        end
        activate ComboFSM
            ComboFSM-->>ComboManager: finish execution
        deactivate ComboFSM
        activate ComboManager
            ComboManager-->>ComboAbility: end ability
        deactivate ComboManager
    deactivate ComboAbility
</code-block>

## Combo Manager

The **Combo Manager** Component is responsible for controlling the **Combo Window** state, the **Combo Count** and
routing **Player Input** to **Ability Activations**, at certain combo states.

The Combat System interacts with this component indirectly through the `CombatComboManagerInterface`. The default 
implementation, `NinjaCombatComboManagerComponent`, is based on the **State Tree** module.

### Combo Manager Interface

This interface is used by the Combat System to execute fundamental tasks in the _combo domain_:

- **Start the Combo**, from the provided **Combo Stat Tree**.
- Manage the **Combo Window** state, allowing inputs to be processed so the combo can progress.
- Keep track of the **Combo Count**, so the State Tree can correctly point to the next attack.
- **Reset the Combo** if the player fails to provide the appropriate input.

### Default Combo Manager

The default implementation is based on the **[State Tree][1]** module. Combos are defined using **State Machines**,
which are a very fitting representation for a combo, including branching to multiple different attacks.

Once set, this component works as the **backbone** of the Combo System, accessed primarily by other parts of the system,
such as the **Combo Window Notify State**.

## Combo State Tree

The Combo State Tree has each **attack** represented as a **state**, using **transitions** to trigger the next viable
attack or complete the combo.

The following objects are usually involved in the construction of your Combo's State Tree.

| Object                  | Description                                               |
|-------------------------|-----------------------------------------------------------|
| Combo Component Schema  | Schema used when creating the **State Tree**.             |
| Combo Manager Evaluator | Exposes a Combo Manager from the **Context Actor**.       |
| Combo State Evaluator   | Exposes the Combo State: **window** and **count**.        |
| Activate Ability Task   | Activates a **Gameplay Ability** by its **Gameplay Tag**. |
| Integer Compare         | Useful condition to check the **combo count**.            |

> **Combo Manager Evaluator**
> 
> This Evaluator is mostly useful in **Unreal Engine 5.3**, where the Combo Manager cannot be directly obtained from
> the **State Tree Context**. 
> 
> So you can use this Evaluator to retrieve the Combo Manager from the Actor, and then bind it to the variable in the
> **Combo State Evaluator**.
{style="note"}

Using the image below as an example, here are the steps necessary to **create a combo**. A deep-dive is also available
in the **how-to** session, where this same Combo is built with detailed descriptions.

<img src="cbt_combo_state_tree.png" alt="Combo State Tree" border-effect="line" thumbnail="true"/>

1. The **State Tree** asset must be created using `UNinjaCombatComboComponentSchema`.
2. In the **Evaluator** section, add a **Combo Manager** evaluator if you are using **Unreal Engine 5.3**. Bind its **Actor** to the one from the **Context**.
3. Add a **Combo State** evaluator. Bind its **Combo Manager** to the one from the **Combo Manager**, or from the **Context** if you are using **Unreal Engine 5.4** or above.
4. Create your **States** for each Gameplay Ability triggered in the combo. Use the **Activate Ability Task** to populate the state.
5. You can use the **Integer Compare** condition to make sure that conditions will only be available on certain **Combo Counts**.
6. Finally, create **Transitions** based on the appropriate **Event Tags** to move to the next state. Also make sure to create a **Completed** transition for final attacks.

It is recommended to have your **Abilities** using the `Ability.Attack.[Combo].[Sequence]` format. In this example we have 
`Ability.Attack.Primary.A`, `Ability.Attack.Primary.B` and so on.

As for the **Events** used in the Transitions**, it's recommended to use the `Combat.Event.Combo.Attack.[EventType]`. In
this example we have `Combat.Event.Combo.Attack.Primary` and `Combat.Event.Combo.Attack.Secondary`.

## Combo Ability

The **Combo Ability** orchestrates the **Combo Window Effect** and forwards **Input Events** to the correct **Combo Events**.
It can also add other Gameplay Abilities required by the Combo to execute correctly.

<img src="cbt_combo_ability.png" alt="Combo Ability" border-effect="line" thumbnail="true"/>

It is recommended to use your **Ability Tags** for activation. In which case, consider using the `Ability.Combo`, at 
least as a _prefix_ to your tag.

In the Combo Section, you will find the following properties:

| Property                  | Description                                                                                                                  |
|---------------------------|------------------------------------------------------------------------------------------------------------------------------|
| Combo Tree                | The **State Tree Asset** containing all attacks and their transitions.                                                       |
| Ability Classes           | **Additional Abilities** required by the combo. They are **automatically added and removed**, with the Combo Ability itself. |
| Event Mode                | How events are transferred to the combo. You can choose between a direct transfer, or a mapping of inputs.                   |
| Combo Window Effect Class | Gameplay Effect applied to the owner, when the Combo Window is open.                                                         |

### Gameplay Tag Event Mode

When using this **Event Mode**, any incoming Gameplay Events starting with `Combat.Event.Combo` will be forwarded to the
**State Tree Component**, so it can trigger state transitions for certain events, such as `Combat.Event.Combo.Attack.02`.

This is the **recommended** event mode for most scenarios.

### Input Action Event Mode

<img src="cbt_combo_ability_input.png" alt="Combo Ability Input" border-effect="line" thumbnail="true"/>

When using this **event Mode**, the **Input Action** in the **Event Payload**, obtained from either Optional Object, is
mapped to a certain Gameplay Tag that will be sent to the **State Tree Component**.

This method is useful for complex combo transitions, where Gameplay Tags are not enough to identify the transitions.

### Combo Inputs

The Combo System always expects two inputs: One to activate the ability and one to send gameplay events to advance the
combo. Depending on how your Combo Ability's Event Mode is configured, you will need to send the Input Action in the
**event payload** as well.

To learn more about the expected inputs, please check the [Combo Ability reference](cbt_ability_combo.md).

## Combo Window

An important aspect of a combo is its **Combo Window**. This is the moment in an attack, where inputs are allowed and,
if received, will trigger the next Combo's state.

Combo Windows are defined in each **Animation Montage** used by **Attack Abilities**, by the **Combo Window Notify State**.
Add the state across all frames that are considered the **Combo Window**. No additional parameters are required.

<img src="cbt_combo_window_notify.png" alt="Combo Notify State" border-effect="line" thumbnail="true"/>


## Combo Viewmodel

Showing the details about the Combo in the User Interface is a very common requirement. To that end, the **Combo Viewmodel**
can be used, so widgets can react to changes in the **Combo Manager** and update themselves. 

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/state-machines-in-unreal-engine

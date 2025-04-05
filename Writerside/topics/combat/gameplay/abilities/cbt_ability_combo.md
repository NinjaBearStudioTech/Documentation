# Combo Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Uses <b>State Trees</b> to manage <b>combo states</b>.</li>        
        <li>Orchestrates <b>Attack</b> or <b>Cast</b> abilities that can be chained together.</li>
        <li>Keeps track of <b>actors hit</b> by the current attack, which can be used to allow the combo to continue.</li>
    </ul>
</tldr>

The **Combo Ability** is responsible for **orchestrating** abilities based on its own **activation** and also **gameplay
events**. Any Gameplay Ability can be added to a combo.

You can find information about all participants of the **Combo System** in its [design page](cbt_combo_system.md). As 
for the **Combo Ability**, including the required **[State Tree](cbt_combo_system.md#combo-state-tree)**.

## Ability Properties

The following attributes adjust the behavior of the Combo Ability.

<img src="cbt_combo_ability.png" alt="Combo Input" thumbnail="true" border-effect="line"/>

| Property                  | Description                                                                                                                  |
|---------------------------|------------------------------------------------------------------------------------------------------------------------------|
| Combo Tree                | The **State Tree Asset** containing all attacks and their transitions.                                                       |
| Ability Classes           | **Additional Abilities** required by the combo. They are **automatically added and removed**, with the Combo Ability itself. |
| Event Mode                | How events are transferred to the combo. You can choose between a direct transfer, or a mapping of inputs.                   |
| Combo Window Effect Class | Gameplay Effect applied to the owner, when the Combo Window is open.                                                         |

## Input

This ability expects two types of input: the usual **activation action** and a **gameplay event** to advance the combo.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_combo_input_blueprint.png" alt="Combo Input" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="cbt_combo_input.cpp" />
    </tab>
</tabs>

In the image you will find the following:

1. The input checks if the combo window is open, via the appropriate **Gameplay Tag**.
2. If it is, then it has to advance the combo, by sending a **Gameplay Event** with the appropriate Event Tag.
3. The **Event Payload** sends the **Input Action** as an **optional object**.
4. If the combo window is not open, then it **activates** the Combo Ability as usual.

The Event Tag has to map one of two things, depending on your design. If your Combo Ability is set to use **Gameplay Tags**
as the **Event Mode**, then the event has to match the Gameplay Tags in your **State Tree**. In this case, you do not
need to send the Input Action in the Event Payload.

If your Combo Ability is set to use **Input Actions** as the **Event Mode**, then your Gameplay Event should always be
set to `Combat.Event.Combo.Attack` and you need to provide the Input Action to map to specific triggers in the State Tree.
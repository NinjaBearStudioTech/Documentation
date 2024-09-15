# AI Agents
<primary-label ref="factions"/>

The Faction System works in conjunction with the Unreal Engine's AI **Perception System**, allowing you to define the 
alignment between AI agents and their sensed targets.

Having access to the Faction Information about a sensed target can be useful to the AI decision process. Unreal Engine
has two systems for that: **Behavior Trees** and **State Trees**. The Faction System supports both of them.

## Behavior Trees

The **Faction Service** exposes Faction information from an Actor in the **Blackboard**.

<img src="fct_bt_service.png" alt="Faction BT Service" thumbnail="true" border-effect="line"/>

| Property             | Description                                                       |
|----------------------|-------------------------------------------------------------------|
| Faction Member Key   | Input. This is the Faction Member that will be evaluated.         |
| Team ID Key          | Output. The Team ID obtained from the Membership.                 |
| Faction Tag Key      | Output. Gameplay Tag representing the Membership's faction.       |
| Attitude Towards Key | Output. The attitude between the AI Owner and the Faction Member. |

The **Attitude Check Decorator** evaluates an attitude from the **Blackboard**. It is able to abort its own execution or 
nodes with lower priority.

<img src="fct_bt_decorator.png" alt="Faction BT Decorator" thumbnail="true" border-effect="line"/>

| Property      | Description                                                       |
|---------------|-------------------------------------------------------------------|
| Attitude Key  | Input. A blackboard entry containing an attitude to be evaluated. |
| Attitude Test | Parameter. Value used to compare the attitudes.                   |

## State Trees

The **Faction Evaluator** exposes Faction information from an Actor added as an input.

<img src="fct_st_evaluator.png" alt="Faction ST Evaluator" thumbnail="true" border-effect="line"/>

| Property         | Description                                                       |
|------------------|-------------------------------------------------------------------|
| Faction Member   | Input. This is the Faction Member that will be evaluated.         |
| Team ID          | Output. The Team ID obtained from the Membership.                 |
| Faction Tag      | Output. Gameplay Tag representing the Membership's faction.       |
| Attitude Towards | Output. The attitude between the AI Owner and the Faction Member. |

The **Attitude Check Condition** evaluates an attitude from an input.

<img src="fct_st_evaluator.png" alt="Faction ST Evaluator" thumbnail="true" border-effect="line"/>

## Attitude Check Condition
This Condition evaluates the attitude between an attitude entry and a given value.

| Property      | Description                                     |
|---------------|-------------------------------------------------|
| Attitude Key  | Input. An attitude to be evaluated.             |
| Attitude Test | Parameter. Value used to compare the attitudes. |

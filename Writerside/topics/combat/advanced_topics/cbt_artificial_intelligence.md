# Artificial Intelligence
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

The Combat System contains utility elements for AI Agents. These elements are built for both Artificial Intelligence
frameworks in Unreal Engine - **Behavior Trees** and **State Trees**.

## Behavior Trees

| Node           | Type      | Description                                                                             |
|----------------|-----------|-----------------------------------------------------------------------------------------|
| Combatant Dead | Decorator | Checks if a combat actor is dead, based on **Damage Manager** condition.                |
| Advance Combo  | Service   | Advances the combo either via Input or Gameplay Tag. Can be extended for dynamic logic. |

## State Trees

| Node           | Type      | Description                                                                             |
|----------------|-----------|-----------------------------------------------------------------------------------------|
| Combatant Dead | Condition | Checks if a combat actor is dead, based on **Damage Manager** condition.                |
| Advance Combo  | Task      | Advances the combo either via Input or Gameplay Tag. Can be extended for dynamic logic. |

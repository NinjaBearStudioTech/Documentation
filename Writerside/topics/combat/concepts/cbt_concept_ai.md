# Artificial Intelligence
<primary-label ref="combat"/>

Ninja Combat includes a small set of AI helpers that allow **Behavior Trees** and **State Trees** to interact with 
Combat System state.

These nodes are focused on common combat decisions, such as checking whether a combatant is dead or advancing a combo 
from AI logic. They are optional, but useful when AI Agents need to react to damage state or drive combo attacks without 
relying on player input.

## Behavior Trees

Behavior Tree nodes are useful for AI Agents built around Unreal Engine's Behavior Tree framework.

| Node           | Type      | Description                                                                                               |
|----------------|-----------|-----------------------------------------------------------------------------------------------------------|
| Combatant Dead | Decorator | Checks if a combat actor is dead, using the state provided by the **Damage Manager**.                     |
| Advance Combo  | Service   | Advances the active combo using either an Input Action or Gameplay Tag. Can be extended for custom logic. |

## State Trees

State Tree nodes provide equivalent functionality for AI Agents built around Unreal Engine's State Tree framework.

| Node           | Type      | Description                                                                                               |
|----------------|-----------|-----------------------------------------------------------------------------------------------------------|
| Combatant Dead | Condition | Checks if a combat actor is dead, using the state provided by the **Damage Manager**.                     |
| Advance Combo  | Task      | Advances the active combo using either an Input Action or Gameplay Tag. Can be extended for custom logic. |
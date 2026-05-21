# Artificial Intelligence
<primary-label ref="gas"/>

Ninja G.A.S. provides features to integrate the Unreal Engine's **Artificial Intelligence** modules with the **Gameplay 
Ability System**. 

## Behavior Trees

| Node                      | Type    | Description                                                                            |
|---------------------------|---------|----------------------------------------------------------------------------------------|
| Update Attributes         | Service | Binds to pre-defined Gameplay Attributes and store their values in Blackboard entries. |
| Select Gameplay Ability   | Service | Selects a Gameplay Ability from a list of pre-defined ability classes.                 |
| Activate Gameplay Ability | Task    | Activates a Gameplay Ability by Gameplay Tag, Class reference or Blackboard entry.     |
| Cancel Gameplay Ability   | Task    | Cancels a Gameplay Ability by Gameplay Tag, Class reference or Blackboard entry.       |

## State Trees

| Node                      | Type          | Description                                                                     |
|---------------------------|---------------|---------------------------------------------------------------------------------|
| Ability Cooldown          | Consideration | Provides the utility value based on the ability cooldown.                       |
| Ability Tracker           | Evaluator     | Tracks how many times a gameplay ability has been completed in a row.           |
| Activate Gameplay Ability | Task          | Activates a Gameplay Ability and completes the state when the ability finishes. |
| Cancel Gameplay Ability   | Task          | Cancels a Gameplay Ability and completes the state when done.                   |
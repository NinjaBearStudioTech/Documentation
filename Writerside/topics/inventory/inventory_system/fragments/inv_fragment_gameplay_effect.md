# Gameplay Effect Fragment
<primary-label ref="inventory"/>

The **Gameplay Effect** fragment allows an inventory item to apply a Gameplay Effect to its owner under **specific conditions**.
It integrates with GAS and supports multiple strategies for evaluating the effect's level.

This fragment enables flexible activation conditions and level evaluation logic. It is especially useful for items that 
grant **temporary or passive attribute modifications**, buffs, or debuffs based on context.

Once the item is removed, or conditions are no longer met, the Gameplay Effect will be removed.

> **Ability Granting and Activation**
> 
> For more complex functionality, you can also use a Gameplay Effect granting **passive abilities** that auto-activate 
> when the item is added to an inventory and its conditions are met.
> 
> [**Ninja GAS**](gas_overview.md) can provide a default implementation for **passive abilities**.
{style=note}

## Fragment Tags
This fragment does not add any traits to the item, but Gameplay Effects can add multiple tags to its owner.

## Properties
This fragment has the following properties.

| Name                    | Description                                                                                   |
|-------------------------|-----------------------------------------------------------------------------------------------|
| `AlwaysApplyEffect`     | If `true`, always applies the effect during activation. When false, conditions are evaluated. |
| `UseContainerCondition` | If `true`, checks a container tag query before applying the effect.                           |
| `ContainerQuery`        | The tag query used to validate the container.                                                 |
| `UseItemCondition`      | If `true`, checks an item tag query before applying the effect.                               |
| `ItemQuery`             | The tag query used to validate the item.                                                      |
| `UseOwnerCondition`     | If `true`, checks the owner's ability system component against a tag query.                   |
| `OwnerQuery`            | The tag query used to validate the owner.                                                     |
| `LevelMode`             | Determines how the effect level is calculated.                                                |
| `DirectLevelValue`      | Direct float value used when `LevelMode` is set to `DirectValue`.                             |
| `LevelCurve`            | Curve used to evaluate level from the Level Fragment when `LevelMode` is `Curve`.             |

## Operations
This fragment exposes the following operations.

| Function                | Description                                                                                |
|-------------------------|--------------------------------------------------------------------------------------------|
| `ActivateItem`          | Applies the effect if conditions pass during activation.                                   |
| `DeactivateItem`        | Removes the effect during deactivation.                                                    |
| `CanApplyEffect`        | Evaluates conditions to determine if the effect should apply.                              |
| `GetEffectLevel`        | Returns the effect level based on the selected `LevelMode`.                                |
| `ReapplyGameplayEffect` | Removes and reapplies the effect in response to relevant events.                           |
| `HandleItemEvent`       | Listens to item events such as container change or level change.                           |
| `GetLevelFromFragment`  | Retrieves the level from the Level Fragment, or returns a fallback value.                  |
| `GetLevelFromCurve`     | Retrieves the effect level from the `LevelCurve`, using the level from the Level Fragment. |

## Integrations
This fragment integrates with the following fragments:

- **Level Fragment**: Required when `LevelMode` is set to `LevelFragment` or `Curve`.
- **Container Placement Fragment**: Used to validate **container conditions**, if enabled.
- **Any Fragment**: Item tag queries can evaluate any other fragment that contributes tags to the item.

## Memory
The Gameplay Effect fragment does not have a memory. However, if the effect is successfully applied, the resulting 
Gameplay Effect Handle is stored in the list of active handles within the item instance.

## Event Payload
This fragment does not define its own event or payload structure. However, events may be triggered indirectly through:

- **Gameplay Effects** activation events.
- Modified **Gameplay Tags** as a result from the Gameplay Effect being applied.
- **Ability Activations**, due to passive abilities being granted and activated.
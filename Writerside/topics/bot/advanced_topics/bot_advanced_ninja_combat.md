# Combat Integration
<primary-label ref="bot"/>
<secondary-label ref="advanced"/>

Ninja Bot integrates with **combat systems** through the **Gameplay Ability System**, allowing AI perception and target 
selection to drive combat-related behavior.

When the AI Controller selects a sensed actor as the current target, it broadcasts a **Gameplay Event** to the owning 
Ability System. A corresponding event is also broadcast when that target is lost.

These events **allow combat abilities to react immediately to AI targeting decisions** without tightly coupling combat 
logic to AI perception.

## Target Lock Integration

A common integration point is the [**Target Lock ability**](cbt_ability_target_lock.md) provided by [**Ninja Combat**](cbt_overview.md). 
When configured, target selection events can automatically:

- activate the Target Lock ability when a target is acquired
- deactivate the ability when the target is dismissed

This enables coordinated combat behavior on both the AI agent and its current target, such as **applying Gameplay Effects**, 
or **triggering combat state changes**.

To integrate Ninja Bot target selection with the Target Lock ability, ensure the following Gameplay Tags match between 
the AI Controller and the Target Lock Ability assigned to the agent:

| Purpose          | Source                                             | Gameplay Tag                    |
|------------------|----------------------------------------------------|---------------------------------|
| Target Acquired  | AI Controller, `PerceptionTargetAcquiredEventTag`  | `Combat.Event.Target.Acquired`  |
| Target Dismissed | AI Controller, `PerceptionTargetDismissedEventTag` | `Combat.Event.Target.Dismissed` |

The **Gameplay Event payload** emitted by Ninja Bot follows the format expected by Ninja Combat. The selected perception 
target is provided as part of the event data, allowing abilities to react without additional setup or translation.
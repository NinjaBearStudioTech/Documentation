# Batch Activation
<primary-label ref="gas"/>

For a predicted ability that starts and ends during the same action, the Ninja component exposes `TryBatchActivateAbility`. It takes the handle of one granted ability and can group that ability's network calls. A custom ability can implement `IBatchGameplayAbilityInterface::EndAbilityFromBatch` to handle the immediate end. `NinjaGASGameplayAbility` supplies this implementation.

For a character's first active or passive ability, start with [Grant Starting Attributes and Abilities](gas_guide_starting_abilities.md).

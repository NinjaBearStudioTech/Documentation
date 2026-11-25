# Combatants, Abilities, and Attributes
<primary-label ref="combat"/>

A combatant needs a way to perform a move and a way to receive its result. On the attacker, the Ability System Component owns the granted attack ability. On the defender, the Combat Manager uses the defender's settings to resolve the hit. Both characters can use the same base Blueprint.

| Part of the character | What it supplies |
| --- | --- |
| Ability System Component | Grants moves, checks their costs and cooldowns, and tracks active effects and tags. Granting an ability makes it available. Input, AI, or a gameplay event activates it. |
| Combat Attribute Set | Stores values such as health, stamina, base damage, and poise. Use the [initialization example](cbt_first_steps.md#initialization-data) for starting values. |
| Combat Manager | Connects the character to damage, defense, and targeting. Provide it through `GetCombatManager` on the Combat System Interface. |
| Mesh and animation instance | Supply hit locations, sockets, and the montage that times the move. Return them from `GetCombatMesh` and `GetCombatAnimInstance`. |

## Give a Character a Move

Create a Blueprint from the Combat ability that matches the move, assign the montage or other assets it needs, and grant the class to the character's ability system. A player can activate a move by its ability tags. A reaction can wait for a gameplay event. For example, grant the [hit reaction ability](cbt_guide_damage_pipeline.md) to the character that receives the hit.

## Resources and Regeneration

For a character that recovers stamina between moves, initialize its stamina regeneration attributes and apply `CombatEffect_ReplenishStamina`. A move can apply `CombatEffect_CancelStaminaRegeneration` with its cost to pause replenishment. Mana has matching replenish and cancel effects.

## Combat Movement Component

For movement that changes during lock-on, blocking, or knockdown, use `NinjaCombatCharacterMovementComponent` as the character's movement component and configure the movement settings for the states your game uses. Keep your existing movement component if it already handles these states.

Add components when the move needs them. A [combo](cbt_guide_combos.md) uses a Combo Manager, a [warped attack](cbt_guide_target_lock.md) uses a Motion Warping Component, and a weapon query needs a [weapon manager](cbt_concept_weapon_management.md). For a custom component, return it from the matching Combat System Interface getter. Implement the interface event in Blueprint or its `_Implementation` override in C++.

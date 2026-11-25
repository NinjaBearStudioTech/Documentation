# Ninja Combat
<primary-label ref="combat"/>

![Ninja Combat](cbt_feature.png "Ninja Combat")

Give a player or an AI character a move, decide when it makes contact, and show what happened to the target. A sword swing, a traveling spell, and a targeted cast can all use the same health, defense, and reaction settings.

## Where to Start

[Set up Ninja Combat](cbt_setup.md), then [create a combatant](cbt_first_steps.md). Use two instances in a test level so you can see both sides of an attack.

| What you want the player to do | Start here |
| --- | --- |
| Swing a weapon, then chain a follow-up | [Land a melee hit](cbt_guide_melee_attacks.md) and [build a branching combo](cbt_guide_combos.md) |
| Send a spell through the air | [Launch a projectile](cbt_guide_ranged_attacks.md) |
| Hit everyone nearby or leave a hazard behind | [Cast a shockwave](cbt_guide_cast_preset.md) or [create a frost field](cbt_guide_cast_actor.md) |
| Choose where a spell lands | [Aim and confirm a spell](cbt_guide_cast_flows.md) |
| Aim, lock on, or use a firearm | [Align an attack](cbt_guide_target_lock.md) and [configure firing and reloading](cbt_guide_firearms.md) |
| Survive a hit or punish a missed attack | [Block, evade, and parry](cbt_guide_block.md), [recover from knockdown](cbt_guide_knockdown.md), or [play a paired finisher](cbt_guide_opportunity_attacks.md) |
| Show the result to the player | [Set up damage and reactions](cbt_guide_damage_pipeline.md) and [display combatant vitals](cbt_guide_widgets.md) |
| Give an opponent the same moves | [Drive combat from AI](cbt_guide_ai.md) |

## Integrations

See [Combat and Input](integration_combat_input.md) for input handlers, [Combat and Inventory](integration_combat_inventory.md) for equipped weapons, [Combat and Factions](integration_combat_factions.md) for team rules, and [Bot and Combat](integration_bot_combat.md) for perception-driven targeting. To set up starting health with an ability bundle, follow [Initialize Plugin Attributes](gas_guide_attributes.md#give-a-combatant-starting-health).

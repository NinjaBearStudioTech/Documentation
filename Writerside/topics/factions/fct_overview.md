# Ninja Factions
<primary-label ref="factions"/>

![Ninja Factions](fct_feature.png "Ninja Factions")

A guard can welcome a fellow guard, ignore a stranger, or turn on someone who betrayed the town. Ninja Factions lets your game ask how the guard sees a particular character.

## What It Does

Give each actor a **main faction** to identify its team. When you ask for an **attitude**, the answer is **Friendly**, **Neutral**, or **Hostile**. You choose whether that answer comes from the two teams or from the target's reputation with the observer's faction.

## Main Features

- Give a character a starting team and let them [join or leave other factions](fct_manage_memberships.md) during play.
- [Award reputation for a quest](fct_add_reputation.md) and let a guard react when the player earns its trust.
- [Choose an AI behavior](fct_bots.md) based on how the observer sees its target.
- [Save memberships and reputation](fct_save_load.md) so the world remembers the player's choices.

## How a Guard Recognizes the Player

The guard's Faction Component identifies it as a member of the Town Watch. When a quest awards the player Watch reputation, the player's Watch membership records the new score. The next time the guard checks the player, the reputation solver reads that membership and returns the Watch's attitude. A dialogue or AI tree can use the result to open the gate.

[Set up Ninja Factions](fct_setup.md), then [give two actors opposing factions](fct_first_steps.md) and check the result in both directions.

## Integrations

Use faction attitudes to [filter what a Ninja Bot guard detects](integration_bot_factions.md) or [control friendly fire in Ninja Combat](integration_combat_factions.md).

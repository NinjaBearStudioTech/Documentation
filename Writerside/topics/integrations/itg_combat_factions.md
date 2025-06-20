# Factions Integration
<primary-label ref="integrations"/>

Integrating **Ninja Combat** and **Ninja Factions** allows you to control **friendly fire** based on the **Faction** and
**Alignment** between the Attacker and Target.

## Modifying the Game Mode

First, add the `NinjaCombatFactionDamageEvaluator` component to your **Game Mode** and add the `CombatDamageModifierInterface`.

Then, Implement the `ModifyDamage`, simply calling the same interface Function from the component you just added. You
can optionally enable or disable Friendly Damage, via the appropriate property, `bDisableFriendlyDamage`.

> **Default Game Mode**
>
> Consider using the `NinjaCombatGameMode` class as a base for your Game Mode, if you do not have a hierarchy of your
> own. This class already provides the integration for you.
{style=note}
# Combat and Factions: Configure Friendly Fire
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="factions-sec"/>

Make the same attack deal full damage to a rival and reduced damage to a teammate, or spare the teammate entirely. Begin with a [repeatable hit](cbt_guide_damage_pipeline.md) and [two known faction attitudes](fct_first_steps.md). Check the attacker's attitude toward each target. Faction relationships can be one-way.

<procedure title="Give the match a friendly-fire rule">
    <step><p>In the targets' Combat Mitigation Pipeline, include <b>Modifier Interface</b>. For a test level, use a Game Mode based on <code>NinjaCombatGameMode</code> and make it the active Game Mode for that level. It already forwards damage decisions to its <b>Damage Evaluator</b> component.</p></step>
    <step><p>In the Game Mode Blueprint, select that component and enable <b>Cancel Friendly Damage</b>. A hit on a friendly target now cancels the damage calculation.</p></step>
    <step><p>To allow reduced damage in another mode, turn cancellation off and set <b>Friendly Damage Mitigation</b> to <code>0.25</code>. The evaluator absorbs a quarter of the damage reaching this step. Leave the hostile target's defenses identical to the ally's for comparison.</p></step>
</procedure>

## Use Your Own Game Mode

Implement **Combat Damage Modifier Interface** on your Game Mode or Game State and give it a `NinjaCombatFactionDamageEvaluator` component. In Blueprint, forward **Should Cancel Damage** and **Modify Damage** to the evaluator with the incoming damage, instigator, target, and both tag containers. Return its Boolean or damage value, respectively. Forward the rule from one place so the same hit is scaled once.

For a C++ Game Mode derived from `ANinjaCombatGameMode`, override `ShouldCancelDamage_Implementation` for a rule such as protecting everyone during warm-up. Return true during warm-up and call the parent for normal play. Override `ModifyDamage_Implementation` when the rule changes the amount of a hit that goes through. A custom pipeline step can override `GatherModifierCandidates` to consult an additional rules object that implements the same interface.

## Try It in Play

Use an attack worth 20 damage with critical hits, armor, and blocking out of the test. Hit a teammate and a rival. With cancellation on, expect health losses of 0 and 20. With cancellation off and mitigation at 0.25, expect 15 and 20. If both take 20, check **Get Attitude** from attacker to target, the level's active Game Mode, and the target's mitigation pipeline.

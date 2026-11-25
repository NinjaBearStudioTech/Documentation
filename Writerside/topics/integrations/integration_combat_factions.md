# Combat and Factions: Control Friendly Fire
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="factions-sec"/>

Use the attacker's attitude toward the target to cancel friendly fire or let allies take reduced damage. Start with a [working damage setup](cbt_concept_damage_and_mitigation.md) and [two characters with factions](fct_first_steps.md). With both plugins enabled, Ninja Combat supplies a faction damage evaluator.

<procedure title="Apply faction rules to incoming damage">
    <step><p>Include <b>Modifier Interface</b> in the <a href="cbt_guide_damage_pipeline.md">Combat Mitigation Pipeline</a> used by the targets.</p></step>
    <step><p>If your Game Mode derives from <code>NinjaCombatGameMode</code>, use its built-in damage evaluator. For a custom Game Mode or Game State, implement <code>CombatDamageModifierInterface</code> and give that object a <code>NinjaCombatFactionDamageEvaluator</code>. Forward <b>Should Cancel Damage</b> and <b>Modify Damage</b> to the evaluator, returning its results.</p></step>
    <step><p>On the evaluator, enable <b>Cancel Friendly Damage</b> to discard friendly hits. To let friendly hits deal reduced damage, turn cancellation off and set <b>Friendly Damage Mitigation</b> to the fraction to absorb. For example, <code>0.25</code> absorbs a quarter of the incoming damage.</p></step>
</procedure>

## Try It in Play

Give the attacker one Friendly target and one Hostile target. With cancellation on, hit both with the same attack. The ally should lose no health, and the hostile target should take damage as usual. Turn cancellation off and repeat with 0.25 mitigation. A hit worth 20 damage should now reach the ally as 15 before other mitigation. If the results differ, check **Get Attitude** from the attacker toward each target, then check which mitigation pipeline each target uses.

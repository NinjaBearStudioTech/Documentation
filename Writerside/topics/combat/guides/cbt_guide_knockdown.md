# Handle Knockdown and Recovery
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Let a teammate revive a downed character before a timer expires. Start with the target from [Apply Damage, Hit Reactions, and Death](cbt_guide_damage_pipeline.md).

<procedure title="Turn a fatal hit into a downed state">
    <step><p>Enable <b>Can Enter Knocked Down State</b> on the target's Combat Manager. In its Damage Data, put the <b>Knock Down</b> outcome before <b>Death</b>. Keep Death available for fatal hits that bypass knockdown. An incoming effect tagged <code>Combat.Effect.Damage.BypassKnockdown</code> can take this path.</p></step>
    <step><p>Set <b>Knock Down Duration</b> to a positive time, such as ten seconds, and <b>Knock Down Health Percent</b> to a positive fraction, such as 0.25 for a quarter of maximum health. Grant <code>CombatAbility_KnockDown</code> and <code>CombatAbility_KnockDownRecovery</code> along with the death ability.</p></step>
    <step><p>Assign a fall montage to Knock Down and a stand-up montage to Recovery. Keep the built-in knocked-down, recovery, and dead effects for this test. In a <code>NinjaCombatAnimInstance</code> Animation Blueprint, use <b>Knocked Down</b> to hold a grounded pose between the two montages.</p></step>
</procedure>

<procedure title="Revive the downed character">
    <step><p>For a simple revive zone, handle its overlap on the server. Check that the overlapping combatant is knocked down and send <code>Combat.Event.RecoverFromKnockDown</code> to that combatant's ability system. A teammate's completed revive action can send the same event.</p></step>
    <step><p>To give up early, send <code>Combat.Event.GiveUp</code> to the downed character. Otherwise the knockdown ability can enter the death flow when the time runs out.</p></step>
</procedure>

For a revive prompt, use `BindToKnockedDownStateChangedDelegate` on the damage manager and hide the prompt when the state clears. If a subclass needs custom expiry feedback, override `HandleKnockDownDurationEnded` in Blueprint or `HandleKnockDownDurationEnded_Implementation` in C++. Call the parent to retain the normal expiry behavior.

## Try It in Play

Take fatal damage and check the fall and grounded pose. Revive before expiry and check that the character stands with the configured fraction of health. Repeat on fresh targets, first waiting for expiry and then using Give Up. Both should enter the death flow.

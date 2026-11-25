# Block, Evade, and Parry
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Use the same incoming swing to test three defensive moves. Start with two [melee combatants](cbt_guide_melee_attacks.md) facing one another and enough stamina for repeated attempts.

<procedure title="Hold a block">
    <step><p>Grant the defender <code>CombatAbility_Block</code>. On guard pressed, activate it. On release, cancel the active block ability so its blocking effect ends. Enable <b>Block</b> mitigation in the defender's Defense Data.</p></step>
    <step><p>For a predictable first test, set <b>Block Chance</b> to 1 and <b>Block Mitigation</b> to 0.5. Use an ordinary blockable hit from the front with sufficient stamina and no other reductions. The held block should prevent half the damage unless a configured block limit caps it.</p></step>
</procedure>

<procedure title="Protect only part of a dodge">
    <step><p>Grant <code>CombatAbility_Evade</code> and assign a dodge montage through its animation provider. Add an <b>Invulnerability</b> notify state over the protected frames. Include <b>Invulnerability</b> in Defense Data before Block. Keep the test hit on target so you can tell a protected hit from a swing that misses.</p></step>
    <step><p>Use <code>BindToBlockingStateChangedDelegate</code> and <code>BindToInvulnerabilityStateChangedDelegate</code> on the defense manager for a training indicator that shows when each protection is active.</p></step>
</procedure>

<procedure title="Create an opening for a counter">
    <step><p>Put a <b>Parry Window</b> notify state on the attacking opponent's swing, covering the frames when the swing can be parried. On the defender, grant <code>CombatAbility_Parry</code> with a parry montage. Put a <b>Parry Scan</b> notify state on the defender's contact frames. Set its mesh source, socket, shape, and weapon query as for the working melee scan. Keep the default parry window tag for the first test.</p></step>
    <step><p>Keep the parry hit effect on the Parry ability. Have the combatants face each other and ensure the scan reaches the attacker. For a riposte, include the <b>Stagger</b> outcome on the opponent and grant its Stagger ability. Give the opponent positive <b>Poise</b> and make the parry build enough poise damage to reach that threshold, or add <code>Combat.Damage.Modifier.ForceStagger</code> to the parry hit effect for this test. Give the defender a positive <b>Riposte Window Duration</b>. Grant the defender <code>CombatAbility_Riposte</code> with a follow-up melee montage and scan. Activate it while the defender has <code>Combat.Opportunity.Riposte</code>.</p></step>
</procedure>

Bind `BindToRiposteWindowChangedDelegate` on the parry manager to show the counter prompt only while the opportunity lasts. The stock manager opens the riposte opportunity when the parry produces a staggering hit. Use `IsParryScanAvailable` on the melee source to allow a specific weapon or stance to perform a custom parry scan. To add feedback when the parry lands, override `HandleMeleeGameplayEffectApplied` on the Parry ability in Blueprint or C++, keeping the parent call.

## Try It in Play

Take one unguarded hit for comparison. Hold guard for the next, then release it. Dodge so the hit lands inside the invulnerability window, then repeat just after it closes. Finally, parry inside the opponent's vulnerable frames, use the riposte while the opportunity is active, and try again after it expires.

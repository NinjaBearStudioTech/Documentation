# Apply Damage, Hit Reactions, and Death
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Make a practice opponent flinch when a hit leaves it standing and play a different animation when its health runs out. Start with a [melee hit](cbt_guide_melee_attacks.md) or [projectile](cbt_guide_ranged_attacks.md) that already reaches the target.

<procedure title="Set up one repeatable hit">
    <step><p>On the attack, use a Gameplay Effect based on <code>CombatEffect_MeleeHit</code> or <code>CombatEffect_RangedHit</code>. These use the damage execution. For a predictable first test, give the attacker positive Base Damage, turn off critical-hit chance, and give the target enough health to survive the first hit.</p></step>
    <step><p>Use the provided Defense Data and Damage Data as starting points. Duplicate them into your project before editing. Assign both on the target's Combat Manager. Keep the <b>Death</b> outcome enabled. For this test, omit survival and knockdown outcomes so reaching zero health follows the death path.</p></step>
</procedure>

<procedure title="Give the target two reactions">
    <step><p>Grant the target an ability based on <code>CombatAbility_HitReaction</code>. Assign a hit reaction montage and make sure its Slot exists in the target's Animation Blueprint. To distinguish front and back hits, add separate montage sections, unlink them from one another, and map the directions in the hit reaction animation provider.</p></step>
    <step><p>Grant <code>CombatAbility_Death</code> with a death montage on the same full-body Slot. Add the <b>Death</b> notify at the frame where the dying sequence should finish. Keep the test target idle so another ability does not block a routine hit reaction.</p></step>
</procedure>

For a localized impact, add `NinjaCombatPhysicalAnimationComponent` and return it from `GetPhysicalAnimationComponent`. Give the target's Physics Asset an **ImpactReaction** physical animation profile with the bodies that should respond, and include the physical-animation damage cosmetic in Damage Data.

For a custom shield rule, override `ApplyMitigation` in a **Ninja Combat Damage Mitigation** subclass and insert it in Defense Data. To add a consequence after damage resolves, override `HandleDamage` in a **Ninja Combat Damage Outcome** subclass and put it in Damage Data. In C++ the corresponding overrides are `ApplyMitigation_Implementation` and `HandleDamage_Implementation`. For a score or cleanup event, bind to the target's **Owner Died** or **Owner Finished Dying** delegate.

To show a damage number, bind `DynamicOnDamageReceived` on the Combat Manager and break the damage entry to read the result. A custom damage manager can expose the same notification through `BindToDamageReceivedDelegate`. Unbind when a widget stops watching that combatant.

<img src="cbt_guide_damage_gameplay_effect.png" alt="Hit Gameplay Effect with the damage execution configured" width="650" border-effect="line"/>

## Try It in Play

Land one hit and check that health falls and the target plays the surviving reaction. Repeat until the hit is fatal. Check that death begins once and that the finish notification arrives at the intended frame. If health falls but nothing plays, check the granted reaction ability, its animation provider, and the Slot.

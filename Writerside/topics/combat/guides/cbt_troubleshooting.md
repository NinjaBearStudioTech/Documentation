# Diagnose a Failed Attack
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Use a known attack and a stationary combatant to find where a move stops. Work from the ability grant to the contact frame and then to the target's health.

<procedure title="Make the move observable">
    <step><p>Turn on debug on the attack ability Blueprint. Run the test with the Output Log open and filter it to <b>LogNinjaCombat</b>. To see detailed messages, enter <b>Log LogNinjaCombat Verbose</b> in the console.</p></step>
    <step><p>Use <b>showdebug abilitysystem</b> to inspect the attacker and target separately. Activate one move at a time and watch the montage, debug shape, and health value.</p></step>
</procedure>

| Symptom                                      | What to check                                                                                                           | How to isolate it                                                                                                                   |
|----------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| Pressing attack does nothing                 | Grant on the correct avatar, activation tag, cost, cooldown, and blocking tags                                          | Activate by class on the same Ability System Component. If it plays, inspect the input or event route.                              |
| Ability runs but no contact is detected      | Montage Slot, **Gameplay Event** trigger, scan notify window, source mesh, socket, weapon query, and collision response | Enable the melee scan debug drawing. Check that the shape crosses the target mesh during the active frames.                         |
| Contact is visible but health stays the same | Hit effect class, damage execution, positive source damage, target attributes, and active mitigation                    | Test an idle target with known health and defense values. Compare the resolved damage and health before adding block or armor back. |
| Health changes but the target never reacts   | Granted reaction ability, activation blockers, ignored damage tags, animation provider, and montage Slot                | Listen for the damage notification on the target, then check whether the reaction ability activated.                                |

On a custom melee ability, `HandleMeleeScanTargetsReceived` lets you inspect detected targets. `HandleMeleeGameplayEffectApplied` lets you inspect the effect results for each hit. Both are available in Blueprint and C++. Call the parent implementations when adding diagnostics so the normal attack still runs.

## Try It in Play

Restore the corrected setting and repeat the same move in range and out of range. Check that you see one expected hit, a corresponding health change, and no damage on the miss. Return the log category to its previous verbosity when finished.

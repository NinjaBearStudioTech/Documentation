# Build a Branching Combo
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give one opening swing two possible follow-ups. A second light press continues the chain, a heavy press branches, and waiting ends the combo. Start with a working [melee ability](cbt_guide_melee_attacks.md).

<procedure title="Prepare the three moves">
    <step><p>Make opening, light follow-up, and heavy follow-up versions of your attack ability. Give each a different identifying ability tag and montage. Put a <b>Combo Window</b> notify state late in the opening montage. Leave the two final montages without a follow-up window.</p></step>
    <step><p>Add <code>NinjaCombatComboManagerComponent</code> to the character. Implement <code>GetComboManagerComponent</code> on the Combat System Interface and return that component.</p></step>
</procedure>

<procedure title="Wire the choice in the Combo Tree">
    <step><p>Create a State Tree with the <b>Combat Combo</b> schema. Add the <b>Combo State</b> evaluator and bind its state to the context. Add an opening state with the <b>Activate Combo Ability</b> task. Bind the Combo Manager and supply the opening move's ability tag.</p></step>
    <step><p>Create two sibling follow-up states with the same task and their respective ability tags. On the opening state, add an event transition for <code>Combat.Event.Combo.Attack.Primary</code> to the light follow-up and another for <code>Combat.Event.Combo.Attack.Secondary</code> to the heavy one. Add <b>On State Completed → Tree Succeeded</b> for an uncontinued move and for each ending.</p></step>
    <step><p>Make a <code>CombatAbility_Combo</code> Blueprint. Assign the tree and add all three attacks to <b>Ability Classes</b>. Grant the Combo Ability to the character. Activate it on the first press. During an open window, send the primary or secondary gameplay event to the character's ability system.</p></step>
</procedure>

<img src="cbt_guide_combo_ability.png" alt="Combo ability holding the State Tree and the abilities used by its states" width="650" border-effect="line"/>

For an on-screen timing prompt, use `BindToComboWindowChangedDelegate` on the combo manager. Hide the prompt when the window closes. Use `BindToComboFinishedDelegate` to observe completion. On the stock manager, the native `OnComboWindowChanged` delegate lets C++ listeners react to each opening and closing window. [Combat and Input](integration_combat_input.md) covers input-action mapping and buffering.

## Try It in Play

Try the opening move three times with input buffering off. An early follow-up should not advance the chain. A light press in the window should play the light follow-up, and a heavy press in the same window should play the other montage. Let the opening move finish once and verify the next press starts a fresh chain.

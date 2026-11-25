# Drive Combat from AI
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Have an AI character start an attack and choose a follow-up when the animation allows it. Use a possessed combatant with the [branching Combo Ability](cbt_guide_combos.md) already working.

<procedure title="Start the move and observe completion">
    <step><p>Give the AI a reachable target. In its Behavior Tree or State Tree, check for a live combatant and an appropriate distance, then activate the granted Combo Ability on the pawn's ability system. The built-in <b>Combatant Dead</b> decorator or condition can exclude a defeated actor.</p></step>
    <step><p>Keep the attack branch active while the combo runs. Bind <code>BindToComboFinishedDelegate</code> before activation, handle a failed activation immediately, and finish the attack branch when the callback arrives. Remove the binding when the branch exits.</p></step>
</procedure>

<procedure title="Send a follow-up when the window opens">
    <step><p>In a Behavior Tree, attach the <b>Advance Combo</b> service to the active combat branch. Choose <b>Gameplay Tag</b> as its event mode and set the default tag to the primary event in your combo. Keep the service active before the opening move reaches its window.</p></step>
    <step><p>In a State Tree, activate the ability from a parent state and run <b>Advance Combo</b> in its child. Bind the AI controller and set the same default transition tag. The task uses the stock Combo Manager or a subclass. Use the <b>Combo Advances</b> output to see whether a follow-up was requested.</p></step>
</procedure>

For a Behavior Tree that branches based on distance or stamina, override `GetComboGameplayTag` on the service in Blueprint. If the combo maps Input Actions, override `GetComboInputAction` instead. In C++, the State Tree task exposes the corresponding virtual functions on `FStateTreeAdvanceComboTask`. [Bot and Combat](integration_bot_combat.md) connects perception to acquiring and releasing a target.

## Try It in Play

Watch the AI perform the opening and light follow-up without a player button press. Change the service or task to the secondary event and check that the heavy animation plays. After the combo finishes, the AI should be able to return to its movement or decision branch.

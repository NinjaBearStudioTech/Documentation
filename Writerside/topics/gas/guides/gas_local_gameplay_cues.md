# Play a Local Gameplay Cue
<primary-label ref="gas"/>
<secondary-label ref="guide"/>

Show a glow on the aiming player's hand while they hold a charge button. The glow should disappear on release or cancellation and stay invisible to the other player. This example uses a [character-owned ability system](gas_first_steps.md).

<procedure title="Give the glow a start and a stop">
    <step><p>Register the gameplay tag <code>GameplayCue.Training.Charge</code>. In the Gameplay Cue Editor, create an actor-based Gameplay Cue Notify for that tag in a cue folder scanned by your project.</p></step>
    <step><p>Add a particle component with <b>Auto Activate</b> off. In the cue Blueprint's <b>On Become Relevant</b> override (<code>WhileActive</code>), attach the effect to the target character's hand socket and activate it. In <b>On Cease Relevant</b> (<code>OnRemove</code>), stop it. The Ninja component sends both the activation and while-active events when adding a cue, so start the loop in one event.</p></step>
</procedure>

<procedure title="Play it for the aiming player">
    <step><p>On the character's charge input, check <b>Is Locally Controlled</b>. On press, get its Ninja Ability System Component and call <b>Add Gameplay Cue Locally</b> with the charge tag. On release or cancellation, call <b>Remove Gameplay Cue Locally</b> with the same component and tag. Also remove an active glow if the character leaves aiming early.</p></step>
    <step><p>If the Player State owns the component, the cue receives the Player State as its target. Put the visible pawn in the cue parameters' <b>Effect Causer</b> on add and remove, and attach the glow to that pawn's mesh.</p></step>
</procedure>

The actor-based Ninja G.A.S. function library nodes can also look up the component for you. In C++, the matching component methods are `AddGameplayCueLocally` and `RemoveGameplayCueLocally`. For a single flash on release, use `ExecuteGameplayCueLocal` with a separate cue tag and put the flash in the cue's **On Execute** event. A one-shot cue needs just that one call.

## Try It in Play

Start two players in separate play windows. Hold the button in the first window. Its player should see the glow, and the second player's view of the same character should stay clear. Release, start again, and cancel. Each finish should clear the effect before the next charge. If the second player also sees it, check where the add call runs and whether a replicated effect is playing the same cue.

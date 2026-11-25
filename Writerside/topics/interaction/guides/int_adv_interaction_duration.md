# Time an Interaction in the State Tree
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Make a terminal search take two seconds **after the player starts it**. The slot is claimed while the search runs. Use this setup when the terminal controls the duration, or when the player should be able to walk up to it before the timer starts. Begin with the [working switch](int_first_steps.md).

<procedure title="Wait before triggering the terminal">
    <step><p>Duplicate the switch's Smart Object and generic tree. Assign the copies to the terminal and its slot. Set the slot's behavior type and matching runtime tag to <code>Interaction.Type.Search</code>, its text to <b>Search</b>, and its <b>Duration</b> to <code>2.0</code> seconds. On press, request that type.</p></step>
    <step><p>In the tree, use the <b>Interaction State</b> evaluator. Create or reuse a wait state before the state that runs <b>Trigger Target Behavior</b>. Add <b>Wait Interaction</b> to the wait state and bind <b>Summary Id</b> to the evaluator's <b>Summary Id</b>. On success, transition to the trigger state. Bind its target actor and claim handle from the same evaluator. End in success after the trigger, and in failure if either step fails.</p></step>
    <step><p>For a search that starts timing on press, leave <b>Time Accumulation Mode</b> on the pawn's Interaction Manager set to <b>Automatic</b>. If the timer should begin after reaching the terminal, use <b>Triggered</b> on that manager and insert <b>Start Interaction Time Accumulation</b> in its own state after the approach and before the wait. Give every timed tree that uses this manager a start point.</p></step>
    <step><p>On the terminal, bind <b>On Interaction Finished</b> to reveal the search result. Use <a href="int_ui_mvvm.md">the active interaction summary</a> to display progress during the wait.</p></step>
</procedure>

<img src="int_adv_target_so_duration.png" alt="Duration on a Smart Object slot's Execute Interaction configuration" width="740" border-effect="line"/>

## Let the Player Interrupt the Search

For a press-and-wait search, release can do nothing. If the player must keep the button down, use a Boolean action with no explicit trigger. On **Started**, request Search. On **Completed** (release), call **Try Cancel Current Interaction** with `Interaction.Event.CancelledButtonPress` if the same search is still in its cancellable waiting phase. Clear the stored search on finish or cancellation. The tree owns the two-second timer in both versions.

## Try It in Play

Start the search. The result should appear once, after two seconds. With release-to-cancel enabled, release after one second. The result should stay hidden and the next search should start from zero. If the bar stays at zero in Triggered mode, check that the tree reaches **Start Interaction Time Accumulation** before **Wait Interaction**.

# Set Movement Speeds for Roaming and Chasing
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Start with the Character from [First Steps](bot_first_steps.md). Give it a slow walk while it roams and a faster run when it spots the player.

<procedure title="Choose two speeds">
    <step><p>In the Content Browser, choose <b>Ninja Bear Studio → Ninja Bot → Bot Movement Adapter</b>. Pick <b>CMC Bot Movement Adapter</b> for a Character that uses Unreal's Character Movement Component.</p></step>
    <step><p>In <b>Profile Settings</b>, add entries for <b>AI.Movement.Walking</b> and <b>AI.Movement.Running</b>. Set each entry's <b>Movement Speed</b> to match its animation. Make the two values visibly different for the test.</p></step>
    <step><p>In the character's <b>Bot Setup</b>, set <b>Movement Mode Adapter Class</b> to the new adapter.</p></step>
</procedure>

<img src="bot_guide_movement_adapter_walking.png" alt="Walking settings on the movement adapter" width="780" border-effect="line"/>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<procedure title="Set the mode before each move">
    <step><p>In the Chase sequence, insert <b>Set Movement</b> before Move To. Choose <b>AI.Movement.Running</b>.</p></step>
    <step><p>In Roam, insert <b>Set Movement</b> before the EQS query and choose <b>AI.Movement.Walking</b>.</p></step>
</procedure>

</tab>
<tab title="State Tree" group-key="st">

<procedure title="Set the mode on entry">
    <step><p>Add <b>Set Movement</b> at the start of Chase and choose <b>AI.Movement.Running</b>.</p></step>
    <step><p>At the start of Roam, apply <b>AI.Movement.Walking</b>. If you use a separate child state to set the mode, transition to the movement state when it completes.</p></step>
</procedure>

</tab>
</tabs>

## Try It in Play

Let the guard roam, step into view, then move out of range. Look for a walk, a run, and a return to walking. If the speed stays the same, check that each task's tag matches its adapter entry.

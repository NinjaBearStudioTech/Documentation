# Tune Detection and Awareness
<primary-label ref="bot"/>
<secondary-label ref="guide"/>

Give the [First Steps guard](bot_first_steps.md) time to notice the player. Use one guard and one player so you can see what changes when you adjust a single setting.

<procedure title="Give sight time to build suspicion">
    <step><p>Open the guard's <b>Sense Profile</b>. Expand Sight and choose <b>Continuous</b> for <b>Awareness Mode</b>. Leave <b>Awareness Weight</b> positive so sight contributes while the player is visible.</p></step>
    <step><p>Create <b>Ninja Bear Studio → Ninja Bot → Awareness Profile</b> in the Content Browser. Start with the defaults: <b>Gain Rate</b> 0.05, <b>Decay Rate</b> 0.03, and thresholds of 0.15 for Suspicious, 0.6 for Alerted and 0.9 for Aware.</p></step>
    <step><p>Open the guard's <b>Bot Setup</b>. Assign both <b>Perception Sense Profile</b> and <b>Perception Awareness Profile</b>. Save.</p></step>
</procedure>

<tabs group="brain_type">
<tab title="Behavior Tree" group-key="bt">

<procedure title="Watch the Blackboard">
    <step><p>Check the <b>AccumulatedAwareness</b> and <b>AwarenessLevel</b> keys you mapped in the <b>Update Perception</b> service. Select the running guard in the Behavior Tree debugger.</p></step>
    <step><p>To delay pursuit, add an <b>AwarenessLevel equals Aware</b> Blackboard decorator to Chase. Set Observer Aborts to <b>Both</b>. Keep the SensedActor check.</p></step>
</procedure>

</tab>
<tab title="State Tree" group-key="st">

<procedure title="Watch the evaluator">
    <step><p>Inspect <b>Accumulated Awareness</b> and <b>Awareness Level</b> on the running guard's <b>Update Perception</b> evaluator.</p></step>
    <step><p>To delay pursuit, require <b>Awareness Level equals Aware</b> on the transition into Chase and its enter condition. Keep the valid-target check.</p></step>
</procedure>

</tab>
</tabs>

## Try It in Play

Start outside the guard's view. Walk into sight and stay there until the level reaches Aware. Repeat with a brief glimpse, then break sight. With no other active sense, stored suspicion fades. The tree's current-target fields can clear as soon as the guard loses its selected target. Step back into sight after a short break and compare the reading with a longer break.

If the guard reacts too quickly, lower **Gain Rate**. If it forgets too quickly, lower **Decay Rate**. Change one value per run. If awareness never rises, check the two profiles assigned to the Bot Setup and confirm the player actually becomes its sensed actor.

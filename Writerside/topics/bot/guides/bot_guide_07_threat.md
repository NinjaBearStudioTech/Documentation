# Make a Guard Respond to Threat
<primary-label ref="bot"/>
<secondary-label ref="guide"/>
<secondary-label ref="experimental"/>

Give a fighter and a healer threat with the same guard, then watch which actor the guard senses. Start with the guard from [First Steps](bot_first_steps.md). This example uses explicit Blueprint calls so you can try it before you have working combat or healing abilities.

<procedure title="Give the guard a Threat Manager and a Threat Sense">
    <step><p>Create a Blueprint child of the guard's Ninja Bot AI Controller and add a <b>Ninja Bot Threat Manager Component</b>. Set the guard's <b>AI Controller Class</b> to that Blueprint.</p></step>
    <step><p>Duplicate the guard's Bot Setup and Sense Profile for this test. In the copy of the profile, use <b>AI Threat Sense Configuration</b> as the only sense and set Threat as the <b>Dominant Sense</b>. Give it a short <b>Max Age</b>, such as 3 seconds, so you can see each test signal expire.</p></step>
    <step><p>Assign the copied profile to <b>Perception Sense Profile</b> on the copied setup, and have the test guard return that setup. Use the First Steps chase condition that checks <b>Sensed Actor</b>.</p></step>
</procedure>

<procedure title="Give two actors competing scores">
    <step><p>Place two characters near the guard and label them <b>Fighter</b> and <b>Healer</b> in the Outliner. In the Level Blueprint, create references to the guard and both characters.</p></step>
    <step><p>For a single-player test, add three keyboard events to the Level Blueprint. On each press, get the guard's <b>Controller</b>, then <b>Get Component by Class</b> for the Threat Manager. Call <b>Register Threat Source</b> on that component.</p></step>
    <step><p>Wire the first key to register Fighter with 10 threat. Wire the second and third keys to register Healer with 6 threat each. Use one press per key. For a networked game, make these calls from the server.</p></step>
</procedure>

## Try It in Play

Select the running guard in the tree debugger and watch **Sensed Actor**. Press the first key. Fighter should appear as the guard's target. Press the second key. Healer has 6 threat, so Fighter still leads and the manager sends no new signal. Let the first stimulus expire and the target clear, then press the third key. Healer now has 12 threat and should appear as the new target. The first signal expiring did not erase Fighter's 10 threat.

If neither actor appears, check that the placed guard uses your controller and the copied Sense Profile. Once the test works, restore Sight to the profile and repeat. Sight and threat can now favor different actors. Adjust the sense weights and target-switch settings to get the behavior your encounter needs. See [Threat and Target Priority](bot_threat_manager.md) for damage-driven threat and per-actor modifiers.

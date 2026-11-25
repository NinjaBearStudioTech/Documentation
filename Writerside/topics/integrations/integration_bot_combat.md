# Bot and Combat: Lock On to a Sensed Target
<primary-label ref="integrations"/>
<secondary-label ref="bot-sec"/>
<secondary-label ref="combat-sec"/>

Make a guard lock on to the player it selects through perception. When the guard forgets the player, it should release the lock and return to its search or patrol. Start with a [guard that sees the player](bot_first_steps.md) and a [combatant with a Target Manager](cbt_first_steps.md).

<procedure title="Pass the guard's selected target to Combat">
    <step><p>Grant the guard a <code>CombatAbility_TargetLock</code> ability and set up the player as a viable target using <a href="cbt_guide_target_lock.md">Lock On and Align an Attack</a>. Check that the guard's tree selects a perception candidate when it sees the player.</p></step>
    <step><p>Open the guard's <code>NinjaBotAIController</code> Blueprint. Set <b>Perception Target Acquired Event Tag</b> to <code>Combat.Event.Target.Acquired</code> and <b>Perception Target Dismissed Event Tag</b> to <code>Combat.Event.Target.Dismissed</code>. Compile and assign it as the guard's <b>AI Controller Class</b>.</p></step>
</procedure>

The controller sends the acquired event to the **guard's** ability system. The guard is the instigator and the selected player goes in both **Target** and **Optional Object**. Target Lock reads **Optional Object** and checks `IsViableTarget`. A guard that only locks on through perception can leave the ability's targeting preset empty. If your own AI sends this event, put the selected actor there too.

To play an alert bark, override `HandlePerceptionCandidateSelected` on the controller Blueprint. Call the parent so it still sends Combat's event. Use `HandlePerceptionCandidateCleared` to stop the alert. In a C++ controller, override the corresponding `_Implementation` methods and call `Super`. For a marker that should appear only after Combat accepts the target, bind to `BindToCombatTargetChangedDelegate` on the Target Manager.

## Try It in Play

Walk into sight and compare the actor selected in the AI debugger with the guard's combat target. They should be the same player. Break sight and wait for the guard's configured memory to expire. The lock should clear when the candidate is dismissed. If the AI selects the player but Combat never locks, check the ability grant, the acquired event tag, and the actor in **Optional Object**.

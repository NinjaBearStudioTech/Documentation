# Bot and Combat
<primary-label ref="integrations"/>
<secondary-label ref="bot-sec"/>
<secondary-label ref="combat-sec"/>

Make a guard lock on to the player it sees and release the lock when it loses its target. Start with a guard that can [detect the player](bot_first_steps.md). Set it up as a [combatant](cbt_first_steps.md) with a Target Manager and grant it the [Target Lock ability](cbt_guide_target_lock.md).

<procedure title="Connect perception to Target Lock">
    <step><p>Create a Blueprint based on <code>NinjaBotAIController</code>. In its Class Defaults, find <b>Perception Target Acquired Event Tag</b> and set it to <code>Combat.Event.Target.Acquired</code>.</p></step>
    <step><p>Set <b>Perception Target Dismissed Event Tag</b> to <code>Combat.Event.Target.Dismissed</code>. Compile the controller and assign it as the guard's <b>AI Controller Class</b>.</p></step>
</procedure>

When the guard selects a target, the controller sends that actor to the ability on the guard. When perception clears the target, the second event releases the lock.

## Try It in Play

Walk a valid combat target into view. Check that the guard's Target Manager selects the same actor as its AI tree. Move the target out of sight and check that the lock clears when perception dismisses it. If perception works but the lock never starts, check the guard's ability grant and the acquired event tag on its assigned controller.

# Animate an Interaction
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Make a character reach for a lever and use it when their hand touches the handle. Start with a working [immediate interaction](int_guide_immediate.md) and a montage compatible with the character's animation Blueprint.

<procedure title="Play a montage from the interaction tree">
    <step><p>Grant <code>InteractionAbility_PlayAnimation</code> to the source. Copy the supplied <code>ST_Interaction_Animation</code> and assign the copy to the lever's slot.</p></step>
    <step><p>If the character needs to line up, place the slot transform at the desired standing position. Use <b>Reach Target</b> for a short adjustment before playing the montage.</p></step>
    <step><p>Use the <b>Play Animation</b> task with <b>Override Animation Montage</b> enabled and select the montage. The task sends an animation request. To use the lever at hand contact, place the <b>Commit Interaction</b> animation notify on that frame and transition on <code>Interaction.Event.CommitInteraction</code> to the state that runs <b>Trigger Target Behavior</b>. Route <code>Interaction.Event.AnimationInterrupted</code> before contact to failure.</p></step>
</procedure>

<img src="int_adv_animation_state_tree_task.png" alt="Play Animation task with a montage override" width="720" border-effect="line"/>

## Choose a Montage by Slot

For levers at different heights, add a runtime tag to each slot, such as a project tag for a low handle. Create a **Generic Chooser** with **Animation Montage** as the result class. Add `NinjaInteractionAnimationCriteria` as an input class parameter. Choose rows by **Interaction Tags**, **Slot Tags**, or **Ability Tags**, and give each row a montage. Assign the table as **Animation Chooser Table** on your play-animation ability and turn off the task's montage override.

<img src="int_adv_animation_chooser_table.png" alt="Animation montage Chooser using interaction criteria" width="720" border-effect="line"/>

Override `GetPlayRate` or `GetSectionName` to adjust playback per interaction. For additional sound or effects, extend `HandleMontageStarted`, `HandleMontageFinished`, or `HandleMontageInterrupted` and call the parent implementation so the tree still receives animation events. Use **Interaction Effect Class** on the ability for tags or cues that last while the montage plays.

## Try It in Play

Use the lever and watch the moment its state changes. Interrupt the character before contact. The lever should stay put, and a second character should be able to use it. If it moves as soon as the montage begins, check that the trigger state waits for the commit event.

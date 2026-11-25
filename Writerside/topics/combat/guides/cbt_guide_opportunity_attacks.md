# Create a Paired Finisher
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give the player a finisher that becomes available near a staggered enemy. A Contextual Animation Scene keeps the two actors in step while the ability handles the hit.

<procedure title="Align the attacker and victim">
    <step><p>Add a <b>Contextual Animation Scene Actor Component</b> and a <b>Ninja Combat Motion Warping Component</b> to both characters. Return the latter from <code>GetMotionWarpingComponent</code>. Create a Contextual Animation Roles asset with <b>Attacker</b> and <b>Victim</b> roles matching the characters' capsule sizes.</p></step>
    <step><p>Create a full-body montage for each role. Enable root motion on source animations that move the character. Add a Motion Warping notify state on the attacker named <b>ExecutionWarp</b>. For a fatal finisher, add <b>Opportunity Damage</b> with a fatal effect at contact on the attacker montage, and the <b>Death</b> notify at the appropriate finish frame on the victim montage.</p></step>
    <step><p>Create a Contextual Anim Scene, assign the roles asset, update roles, and set <b>Victim</b> as primary. Assign the matching montage to each track. Adjust the relative positions in the preview. Add a warp point named <b>ExecutionWarp</b> targeting the primary actor and update the warp points.</p></step>
</procedure>

<img src="cbt_guide_opportunity_scene_asset.png" alt="Attacker and Victim tracks aligned in the contextual animation scene" width="650" border-effect="line"/>

<procedure title="Offer the finisher only to eligible targets">
    <step><p>Create a targeting preset that selects a nearby opponent, excludes dead actors, and requires the target's staggered state. Give the target a stagger duration long enough to try the move. Grant the attacker a <code>CombatAbility_OpportunityAttack</code> Blueprint and assign the preset and contextual animation. Activate the ability from the finisher action.</p></step>
    <step><p>If the same button also performs an ordinary attack, configure the ability's fallback ability tags and grant that fallback. Otherwise leave fallback disabled so an ineligible target simply gets no finisher.</p></step>
</procedure>

Use `HandleOpportunityAttackStarting` for a cue when a pair has been selected. For a scene with another role, override `CollectAdditionalSceneActors` to supply its named actor. Both are Blueprint events with C++ overrides. For an optional cinematic camera, assign a camera animation and anchor class and use `NinjaCombatPlayerCameraManager` or implement `PlayCombatCameraAnimation` and `StopCombatCameraAnimation` on your own manager.

## Try It in Play

Try the finisher before the target staggers and check the fallback, if configured. Then stagger it and activate again. The pair should align at contact, damage should occur once, and both actors should leave their opportunity states at the end. Check that a fatal victim completes its death presentation.

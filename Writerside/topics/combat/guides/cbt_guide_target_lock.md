# Lock On and Align an Attack
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Put a marker over a selected opponent, then make the character step toward that opponent during the opening of a melee attack.

<procedure title="Acquire and release an opponent">
    <step><p>Create a <b>Targeting Preset</b>. Add <b>Current Target Selection</b> and enable <b>Select Targets in Area</b> for the initial search. Use a capsule on the combat channel sized to cover both test targets. Follow it with <b>Dead Filter</b>, <b>Facing Filter</b>, and <b>Distance Sort</b>. Place two targets at visibly different distances.</p></step>
    <step><p>On each target add a Scene Component at the desired marker position and give it the component tag <code>Combat.Component.TargetLockAnchor</code>. Create a <code>NinjaCombatMarkerActor</code> Blueprint with a visible widget and set it as <b>Target Marker Actor Class</b> on the locking character's manager.</p></step>
    <step><p>Grant a <code>CombatAbility_TargetLock</code> Blueprint with this preset assigned. Activate it from your lock action. To unlock, send <code>Combat.Event.Target.Dismissed</code> to the character. Enable distance tracking and set the distance threshold if leaving range should break lock.</p></step>
</procedure>

<procedure title="Align the moving part of the attack">
    <step><p>Add <code>NinjaCombatMotionWarpingComponent</code> to the attacker and return it from <code>GetMotionWarpingComponent</code>. Use a root-motion attack and enable root motion in the animation setup.</p></step>
    <step><p>On the montage, place <b>Track Motion Warp Target</b> across the approach. Assign the same targeting preset so its Current Target Selection task finds the locked opponent. Give it a warp name, such as <b>Combat Warp</b>. Add a <b>Motion Warping</b> notify state over the root motion to adjust. Choose <b>Skew Warp</b> and enter the identical warp target name.</p></step>
</procedure>

<img src="cbt_guide_melee_animation_motion_warping.png" alt="Motion Warping notify aligned to a named target in the montage" width="650" border-effect="line"/>

For a custom lock HUD, bind `BindToCombatTargetChangedDelegate` and update it from the new target, including an empty target on release. For a scripted approach, the **Combat Motion Warping Interface** exposes `SetCombatWarpTarget`, `StopTrackingWarpTarget`, and `ClearCombatWarpTarget`. Use the same warp name throughout.

## Try It in Play

Lock on with both opponents ahead. Check which one receives the marker, then start the attack from slightly off-center and watch the approach. Release lock or walk beyond the configured threshold. The marker should clear. If the marker is correct but the step misses, check the two warp names and the root-motion frames.

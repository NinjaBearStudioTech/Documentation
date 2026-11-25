# Aim and Confirm a Spell with a GAS Target Actor
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Let the player aim a blast with a ground marker, then confirm or cancel it. A Gameplay Ability System (GAS) Target Actor controls the preview and returns the selection. The cast ability applies damage when the player confirms.

<procedure title="Build the aiming marker">
    <step><p>Create a Blueprint based on <code>NinjaCombatAbilityTargetingActor</code>, Ninja Combat's subclass of <code>AGameplayAbilityTargetActor</code>. Add a circle decal sized to match the blast radius.</p></step>
    <step><p>While aiming, trace from the player's camera along its forward direction on a channel the floor blocks. On a floor hit, move the targeting actor to the impact point so the circle and the blast share a center. If you update the trace on Tick, enable ticking on the Blueprint.</p></step>
    <step><p>Set the actor's <b>Targeting Type</b> to <b>Targeting Preset</b>. Assign an area preset like the one in <a href="cbt_guide_cast_preset.md">Cast a Shockwave with a Targeting Preset</a>. On confirmation it collects actors around the marker and excludes the instigator.</p></step>
</procedure>

In the marker Blueprint, use <code>HandleTargetActorActivated</code> and <code>HandleTargetActorDeactivated</code> to show and clear aiming visuals. Call the parent implementations to keep the built-in visibility and tick handling. If you already have a C++ subclass of <code>AGameplayAbilityTargetActor</code>, you can assign it directly. Its <code>ConfirmTargetingAndContinue</code> implementation should send the selected actors or their hit results through <code>TargetDataReadyDelegate</code>.

<procedure title="Wait for the player's choice">
    <step><p>Create a <code>CombatAbility_Cast</code> Blueprint. Set <b>Cast Trigger</b> to <b>Ability Activation</b>, <b>Targeting</b> to <b>Wait for Confirmation</b>, and <b>Confirmation Type</b> to <b>User Confirmed</b>. Assign the marker as <b>Targeting Actor Class</b> and a damage effect based on <code>CombatEffect_Damage</code> as <b>Cast Effect Class</b>. Give the caster positive <b>Base Damage</b>.</p></step>
    <step><p>Assign a casting montage. Have its opening lead into a <b>Loop</b> section that repeats while aiming. Add a <b>Confirmed</b> section for the release. Set <b>Commit Time</b> to <b>Targets Acquired</b> if canceling should leave mana and cooldown available.</p></step>
    <step><p>Grant the ability and bind your spell action to activate it. While aiming, send the player's confirm and cancel actions to the owning Ability System Component's <code>LocalInputConfirm</code> and <code>LocalInputCancel</code>. If you use Ninja Input, see <a href="integration_combat_input.md">Combat and Input</a>.</p></step>
</procedure>

<img src="cbt_guide_cast_ability_confirm_targets.png" alt="Cast ability configured to wait for the player to confirm targets" width="650" border-effect="line"/>

## Place a Lingering Effect at the Marker

To place the [frost field](cbt_guide_cast_actor.md) at the chosen point, switch the marker's **Targeting Type** to **Location Only**. On the ability, choose **Wait for Confirmation and Spawn Actor** and assign the frost field as **Cast Actor Class**. Confirmation now supplies the position. The field applies its own effect as combatants enter it.

## Try It in Play

Aim the blast at one combatant with a second outside the circle. Both should keep their health while you aim. Confirm and check that only the first loses health. Cast again and cancel. The marker should clear, and neither combatant should take another hit.

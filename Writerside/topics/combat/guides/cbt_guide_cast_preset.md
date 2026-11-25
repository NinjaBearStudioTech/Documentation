# Cast a Shockwave with a Targeting Preset
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give the caster a shockwave that hits nearby combatants when their hand strikes the ground. The Targeting Preset finds everyone in range at that moment. The cast ability applies damage to those targets.

<procedure title="Choose who the shockwave can hit">
    <step><p>Create a Data Asset of type <b>Targeting Preset</b>. Add <b>Targeting Selection Task AOE</b> to its tasks. Choose <b>Sphere</b> and set <b>Radius</b> to 600 Unreal units.</p></step>
    <step><p>Choose the channel your combatants respond to, such as <code>CombatObject</code> from the <a href="collision_settings.md">collision setup</a>. Enable <b>Ignore Source Actor</b> and <b>Ignore Instigator Actor</b> so the caster is safe.</p></step>
    <step><p>After the selection task, add <b>Targeting Filter Task Dead</b>. The first task gathers actors in the sphere, then the filter removes defeated combatants.</p></step>
</procedure>

<img src="cbt_guide_cast_targeting_preset.png" alt="A sphere selection followed by a filter for defeated targets" width="650" border-effect="line"/>

<procedure title="Release the shockwave">
    <step><p>Give the caster positive <b>Base Damage</b> and create a Gameplay Effect based on <code>CombatEffect_Damage</code>. Use a practice target with health and a Combat Manager.</p></step>
    <step><p>Create a Blueprint based on <code>CombatAbility_Cast</code>. Set <b>Targeting</b> to <b>Targeting System</b>, assign your <b>Targeting Preset</b>, and set <b>Cast Effect Class</b> to the damage effect.</p></step>
    <step><p>Set <b>Cast Trigger</b> to <b>Gameplay Event</b>. Assign a casting montage and place the <b>Trigger Cast</b> notify on the ground-strike frame. Grant the ability to the caster and bind it to your spell action.</p></step>
</procedure>

For a wider shockwave after an upgrade, override <code>GetTargetingPreset</code> in the ability Blueprint, or <code>GetTargetingPreset_Implementation</code> in C++. Return the larger preset when the caster has the upgrade. The same montage and effect serve both versions. Use <code>HandleCastStarted</code> for a sound at release, even if the sphere is empty.

If your damage effect reads a custom Set By Caller value, a C++ ability can override <code>ApplyCastMagnitudesToSpec</code>. Call the parent first, then add the value your effect reads, such as a bonus for a charged shockwave.

## Try It in Play

Place two living targets inside the radius and one outside. Cast once. Both nearby targets should lose health on the ground strike. The caster and the distant target should keep their health. Move the distant target into range after the strike. It should take damage only on the next cast.

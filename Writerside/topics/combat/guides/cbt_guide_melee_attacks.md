# Register a Weapon and Land a Melee Hit
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Give the player a sword that hits a practice target only during the swing. Start with two [combatants](cbt_first_steps.md) and a swing montage that plays on the character.

<procedure title="Register the sword">
    <step><p>Create a Blueprint based on <code>NinjaCombatWeaponActor</code>. Give it a mesh and add a socket named <code>sScan</code> near the middle of the blade. Return this mesh from <code>GetMeleeMesh</code>. Give the weapon an identifying gameplay tag such as <code>Combat.Weapon.Sword</code>.</p></step>
    <step><p>Add <code>NinjaCombatWeaponManagerComponent</code> to the character and return it from <code>GetWeaponManagerComponent</code>. Add the sword Blueprint to <b>Default Weapon Classes</b>. In <b>Weapon Socket Mapping</b>, map that class to a hand socket that exists on the character mesh.</p></step>
</procedure>

<procedure title="Time the hit to the swing">
    <step><p>On the swing montage, add a <b>Melee Scan</b> notify state covering the contact frames. In the notify's <b>Request Data</b>, select <b>Weapon</b> as the source and give <b>Weapon Query</b> a rule matching the sword tag. Select <b>Box Sweep</b>, enter <code>sScan</code> as the scan socket, and size the box to cover the blade. Use the combat trace channel from your collision setup.</p></step>
    <step><p>Create an ability based on <code>CombatAbility_MeleeAttack</code>. Keep the melee attack trigger on <b>Gameplay Event</b>, assign the swing montage, and set its melee damage effect to a child of <code>CombatEffect_MeleeHit</code>. Give the attacker positive Base Damage.</p></step>
    <step><p>Grant the ability to the player. For a first test, call <b>Try Activate Ability by Class</b> on the player's Ability System Component from a button press. Enable debug on the attack ability so you can see the sweep.</p></step>
</procedure>

<img src="cbt_guide_melee_animation_scan_weapon.png" alt="Melee Scan configured to sweep a socket on the selected weapon" width="650" border-effect="line"/>

## Use the Same Move for an Unarmed Strike

For a punch, implement `ICombatMeleeInterface` on the character and return its mesh from `GetMeleeMesh`. Select **Owner** on the notify and use a sphere sweep at a hand socket. If the character already has a dedicated hit shape, return it from `GetMeleeOverlap` and select the overlap scan mode.

For a weapon with its own hit effect, implement `GetHitEffectClass` on the melee source. To react after an effect was applied, override `HandleMeleeGameplayEffectApplied` on the ability in Blueprint or `HandleMeleeGameplayEffectApplied_Implementation` in C++. The hit result identifies the target and contact point.

## Try It in Play

Swing once in range and check that the target loses health during the scan. Swing again just out of reach. The montage should still play and the target should keep its health. If the box appears at the wrong location, inspect the socket on the mesh returned by the melee source.

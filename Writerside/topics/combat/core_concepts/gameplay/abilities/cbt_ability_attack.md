# Attack Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>The <b>Attack Ability</b> is used to create <b>melee</b> and <b>ranged</b> attacks.</li>
        <li>They can be granted by default, or from certain weapons added to the <b>Weapon Manager</b>.</li>
        <li>Can be used as part of a <b>combo</b>.</li>
    </ul>
</tldr>

## Melee Attacks

The Attack Ability can be used for melee attacks. Please take a look at the [](cbt_melee_attacks.md) page for more info.

## Projectile Attacks

The Attack Ability can launch projectiles. Please take a look at the [](cbt_ranged_attacks.md) page for more info.

### Modifying the Gameplay Effect

The Projectile Actor is designed in a way so it will not rely on the owner's Ability System Component. That is important 
as the owner's ASC might not be available anymore to apply Gameplay Effects, when the Projectile Actor hits a target.

But if you need to modify the Gameplay Effect Spec set by the Gameplay Ability, then you can do so via Set By Caller
Magnitudes, Curve Modifiers and Dynamic Tags.

The following functions can be implemented for this purpose:

- `GetDynamicGameplayTags`: Determines dynamic Gameplay Tags applied to the spec, when a cast target is acquired.
- `GetAdditionalSetByCallerMagnitudes`: Adds/replaces magnitudes available in the GE with current values.

If you need more drastic changes to the Effect Handle, then you should look into the `ApplyGameplayEffectToData` function,
but that modification is only available in C++.
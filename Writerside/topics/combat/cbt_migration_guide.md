# Migration Guide
<primary-label ref="combat"/>

## Version 1.x to 2.x

Some Combat **Components** were merged: Target, Defense, Damage were all merged into the Combat Manager. Opportunity
Manager Component, and all related components were removed. All relevant interfaces are still there to enable "hot-swap"
of components in the future.

**Weapon Actors** have a default Scene Component and already implement Melee and Projectile interfaces. Properties were 
added to tweak those. You will need to review your class hierarchy to make sure no duplicates are being added.
 
The **Weapon Manager** Component was improved to be more usable at its original state. If you are using the default
Weapon Manager, ensure that the new features are working with your setup.

**Melee** and **Ranged** Impact Handler functions will now receive the Source and Target tags. If you override those
functions, make sure to add the new parameters as well.

Add the new `CombatWeapon` module to your `Build.cs` file. Main weapon classes were moved into this module.

The death flow was revamped to be more linear. If you had overrides, make sure to review those.

Damage effects have been remade to take care of the new poise settings.

The Dissolve handler is more flexible, supporting multiple parameters and curves.

The Forward Reference can be any Scene Component and can be created automatically.

The Movement Manager has been converted into a Character Movement Component.
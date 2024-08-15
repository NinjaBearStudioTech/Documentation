# Migration Guide
<primary-label ref="combat"/>

## Version 1.x to 2.x

**Weapon Actors** have a default Scene Component and already implement Melee and Projectile interfaces. Properties were 
added to tweak those. You will need to review your class hierarchy to make sure no duplicates are being added.
 
The **Weapon Manager** Component was improved to be more usable at its original state. If you are using the default
Weapon Manager, ensure that the new features are working with your setup.

**Melee** and **Ranged** Impact Handler functions will now receive the Source and Target tags. If you override those
functions, make sure to add the new parameters as well.

Add the new `CombatWeapon` module to your `Build.cs` file. Main weapon classes were moved into this module.


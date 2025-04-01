# Version Updates
<primary-label ref="combat"/>

> **Back up first!**
>
>Before migrating to a newer version, it is highly recommended that you back up your project first!  
{style="warning"}

## 3.0 to 4.0
1. Review your Ability Tags. Default Ability Tags now have the `combat` prefix, to ensure better organization of combat-related tags.
2. Check the [](cbt_collisions.md) page for the new **Collision Setup**. Review your Melee Scans, Projectiles and Opportunity tests.
3. The Warp Component interface and core implementation was changed to better incorporate maximum distance, offset and final scale. If you have changes in the component or warp providers, please review them. 
4. Added support to multiple physical surfaces per impact on weapons and projectiles. Since this was a common extension point in projects, evaluating the new solution is recommended.
5. The combat **ViewModels** are now to be used in conjunction with the **Combat ViewModel Resolver** and won't require any base combat widgets. The "Widget" damage handler has been removed.

## 2.0 to 3.0
Version 3.0 updated some delegates, to make them more compatible with stateless classes such as AI nodes. Your callbacks
(C++ and Blueprints) should be reviewed now that most delegates will have an extra value: the component that is broadcasting
the event.

## 1.0 to 2.0
Version 2.0 introduced many updates to the Combat System. It also drastically simplified the configuration. It’s easier
to have a separate copy for the migration, so you can paste some contents over.

1. The combat components "Damage", "Defense" and "Target" were **merged** into the unified `NinjaCombatManagerComponent`. To get started with the new system, you only need to add that component and a `NinjaCombatWeaponManagerComponent`.
2. The `CombatSystemInterface` will try to find all components by their interfaces. Right away, you can just implement the getters for the Combat Manager and Weapon Manager. Other functions can be implemented if/when necessary.
3. The **Weapon Manager** was improved to be usable out-of-the-box. Review extensions that you made to this component, as they may no longer be needed.
4. The **Opportunity Manager** and all related components were removed from the system. Please check the new Opportunity System to learn how to configure Opportunity Attacks.
5. **Weapon Actors** have a default Scene Component, and already implement Melee and Projectile interfaces. They have many properties available to adjust their behaviors.
6. Functions for **Weapon Cosmetics**, from Melee and Ranged interfaces, had their signature changed. If you have custom implementations for these interfaces, review them accordingly.
7. In a C++ project, make sure to review your modules in the `Build.cs` file.
8. The **death flow** was reviewed to be more uniform across different sources of fatal damage. If you made changes to the original functions, you might need to review them.
9. The Poise and Stagger system was changed and Poise now decreases. This addresses an issue where characters would not react to damage in version 1.0 since their poise was always zero. Be sure to review your **Combat Attributes** using the new JSON reference.
10. The **Dissolve Handler** is more flexible, supporting multiple parameters and curves.
11. The **Forward Reference** can be any Scene Component, and it can be created automatically by the Combat Manager.
12. The Movement Manager has been converted into an actual Character Movement Component, so you will need to add that to your character, if you want to use the movement capabilities.

# Changelog
<primary-label ref="combat"/>

## 5.7.6 - 21/10/2025
```
[added] New network prediction strategy for Combos (open/close window, advance combo).
[added] New ability task for Net Sync with pre-defined server timeouts.
[improvement] Added Combo State Tree validation for 5.6+.
[improvement] Combat Animation Montage will change sections using the ASC.
[improvement] Combo Manager will track combo window durations and fallback-close them, since notifies might not end correctly on dedicated servers.
[improvement] Updated declarations using raw pointers, replacing them with TObjectPtr.
[fix] Deferred ASC initialization in the base ViewModel will obtain world from the owning actor.
[fix] Combat ViewModel resolver was renamed to follow the correct naming convention.
```

## 5.4.1 - 10/09/2025
```
[added] New strafe-related functions, integrated with the Target Manager.
[improvement] Rewrote integration with Ninja Inventory, using reflection instead of compiler conditions. 
[improvement] Rewrote integration with Ninja Factions, using reflection instead of compiler conditions.
```

## 5.1.1 - 23/08/2025
```
[improvement] Updated integration with Ninja Inventory, to match version 2.0.0.
[improvement] Exposed binding/unbinding function in the base Anim BP, to support deferred initialization.
```

## 5.0.0 - 04/07/2025
> **Important Changes in this version**
>
> 1. Due to the changes in the Combo Ability Task, you will need to reconfigure your combo tasks.
> 2. The native Inventory Integration is disabled, and we'll be restored for Inventory 2.0.
> 3. The Shoot Ability and Camera Aiming are still work-in-progress.
```
[major] Rewrote the Combo Ability Task, using the native base class, to align with the recent changes in UE 5.6. 
[added] New Shoot ability that can handle Hit-Scans and Projectiles, in a "firearms" context (wip)
[added] New Magnitude Calculation that can consider the current combo count.
[added] New Static Gameplay Cue Notify for Parry Windows.
[added] New Gameplay Effect Requirement that checks for actual participants in the Combat System.
[added] Added a dedicated ViewModel for the Riposte State.
[added] Added the option to use Chooser Tables for Hit Reactions.
[improvement] Included guard conditions to avoid ticking in invalid component states.
[improvement] Updated Gameplay Targeting "Target Lock Filter Task" so it won't filter actors when there's no lock-on.
[improvement] Included option to perform an AOE selection in the Gameplay Targeting "Select Combat Target Task".
[improvement] Exposed floor distance setting for the Cast Actor.
[improvement] Tracking death/destroyed for warp targets to remove them from the component faster.
[improvement] Implemented the time-stretching guard conditions for all Anim Notify states.
[improvement] Included option to opt in/out of physical animations for recurring damage.
[improvement] Exposed the trace channel used by Cast Actors to detect Hit Results.
[improvement] Changed the Physical Reaction Damage Handler, so it's tag-based. 
[improvement] Introduced a fallback method for projectiles launched when an actor was not obtained by the targeting system. 
[bugfix] Fixed the calculation for the Motion Warping pushback.
[bugfix] Fixed the starting bone for the Physical Animation Component.
[bugfix] Fixed dangling warping targets that might be invalid.
[bugfix] Fixed crashes that might happen when closing the game while blocking.
[bugfix] Fixed scenarios where the effect context proxy would incorrectly discard zero damage. 
[bugfix] Fixed Target Lock event handling and source lock effect application. 
[bugfix] Fixed Invulnerability calculation, to actually reset the damage on the Defense Manager. 
```

## 4.1.3 - 25/04/2025
```
[added] Added `GetAdditionalCombatMagnitudes` to attacks and casts, allowing more flexibility regarding damage effect magnitudes.
[improvement] Introduced the `bAllowMeleePushback` property in the Motion Warping Component, to allow melee pushback from the optimal distance.
[bugfix] Added guard condition to avoid editor crashes in the `AnimNotify_Cast`.
[bugfix] Fixed the guard condition for the Targeting Subsystem in the Motion Warping component.
```

## 4.0.0 - 21/04/2025
> **Important Changes in this version**
> 
> 1. Ability tags now have a `combat` prefix, to ensure better organization of combat-related tags. Make sure to review the Gameplay Tags page for more details.
> 2. The Melee Scan Notify now supports an array of Object Channels, which simplifies the setup, but will require a review on your Anim Notify configurations.  
> 3. The Warp Component interface and core implementation was changed to improve setup and tracking of moving targets.
> 4. Added support to multiple physical surfaces per impact on weapons and projectiles. Since this was a common extension point in projects, evaluating the new solution is recommended.
> 5. The combat ViewModels are now to be used in conjunction with the Combat View Model Resolver and won't require any base combat widgets. The "Widget" damage handler has been removed.
```
[major] The Motion Target setup was changed to track ongoing targets with more control.
[major] A viewmodel Resolver that removes the need of using combat-related widgets. Widgets will be deprecated and removed in a future release.
[major] Melee Scans will support multiple trace channels. The Melee Scan class will now allow you to override Object and Trace parameters separately.
[added] Added a dedicated flow for Parries and Ripostes, based on the active frames of the Melee Scan, or a dedicated Parry Window Notify State.
[added] Non-dynamic multicast delegates added to the Combat Manager, so they can be used with lambdas (i.e. State Tree Tasks).
[added] Non-dynamic multicast delegates added to the Combo Manager, so they can be used with lambdas (i.e. State Tree Tasks).
[added] A direct call to the source of damage, to notify damage applied to a target. Useful for XP, specific attack notifies, etc.
[added] An extensible State Tree Task that can send Combo Events to an ongoing Combo Ability task.
[added] Support for impact data tables that can automatically override the default impact cosmetics, based on the surface that was hit.
[added] Handling scenarios where a projectiles hit non-combatant actors, such as the environment.
[added] Added "Ready" and "Started" events to the Combat Animation Ability Task. They will notify these new stages in a combat animation.
[added] Added dedicated attributes for base damage bonus and base damage reduction.
[improvement] Organized the Combat Ability Tags to allow other types of game-related categories, without clutter.
[improvement] Added support for multiple hits in the same melee scan.
[improvement] Marked Attribute Set functions "InitializeDamageCalculationInput" and "ApplyDamage" as virtual.
[improvement] Added a base cost attribute for Stamina and Magic.
[improvement] Added support functions to the base Weapon Manager.
[improvement] Covered Player States and Controllers in the GetCombatManagerComponent function, from the Combat Library.
[improvement] Exposed the combat forward reference in the Combat Manager and Function Library.
[improvement] Exposed setters for the speeds in the custom Movement Manager and getters for current states.
[improvement] Improved the way the Combat Manager is retrieved via library, supporting multiple types of owner: controller, player state, weapon.
[improvement] Exposed access to the current Gameplay Ability Target Actor, via the Target Manager interface/component.
[improvement] Simplified the Cast flow for GAS Targeting Actors in the Cast Ability.
[improvement] Allowed the base Animation Ability to dynamically determine if commits should be done before the animation plays.
[improvement] Lowered severity of the log, when a weapon is not found by normal means.
[improvement] Exposed the Root Motion Scale in the Animation Provider object.
[improvement] Added a logic path for game cues to play Camera Shakes for the local player, even if no target was hit (i.e. hit the ground).
[improvement] Improved the "AlignWithFloor" function, from the base Cast Actor, so it also aligns with the floor orientation.
[improvement] Exposed the last scans and positions obtained by a Melee Scan.
[improvement] Simplified the extension of melee trace cosmetic parameters.
[improvement] Added a test to the cosmetics component, in case the game ends before the callback is invoked.
[improvement] Added a "GetCastOwner" to the Cast Interface.
[improvement] Added a block tag for Hit Reactions.
[improvement] Added an option for Cast Actors to manage application and removal of infinite Gameplay Effects while actors are colliding with them.
[improvement] Added an option for Cast Abilities to commit after the cast has been completed.
[improvement] Reviewed and improved how the Physical Animation Component works for hit reactions.
[bugfix] Fixed the cancel regeneration tags being applied incorrectly.
[bugfix] Ensured that predicted rep-notifies in the combat manager won't broadcast twice (for prediction and replication).
[bugfix] Ensured warp targets are cleared when animation abilities end.
[bugfix] Fixed the armor mitigation calculation.
[bugfix] Fixed the name shown for the Combat Animation Ability Task, in the editor node.
[bugfix] Fixed a bug in the Combat Animation Ability Task, that would avoid the montage to be moved to another section.
[bugfix] Ensured that the Wait Target Data With Actor Callback Task properly correctly applies modifications.
[bugfix] Fixed a call to the "_implementation" version of "CastToTargets", in the Cast ability.
[bugfix] Handled "lifespan on death" when there's no damage setup provided during the death event. 
[bugfix] Fixed hard requirement for poolable actors in the Cast Ability.
[bugfix] Removed the duplicated damage calculation from the ranged damage effect.
[bugfix] Correctly handling stacks in the Status Effect ViewModel.
[bugfix] Added missing calls to super in Notifies and States.
[bugfix] Fixed the logic for "Actors Hit" in the projectile Targeting Filter Task.
```

## 3.1.6 - 31/01/2025
```
[added] Handling scenarios where a melee attack hits non-combatant actors, such as the environment.
[improvement] Vastly improved how the Combat Framework retrieves Combat Meshes and Anim Instances.
[improvement] Improved categories and function settings from the Actor Pool and its Function Library.
[bugfix] Ensured that combo delegates are broadcast correctly when the combo is reset, considering interruptions.
[bugfix] Ensured that melee cosmetic parameters are properly using the Niagara parameter names set.
[bugfix] Ensured that the play rate set by Animation Providers carries over to the Animation Montage task.
[bugfix] Fixed the Defend Damage calculation, so it calculates based on the final applied damage.
```

## 3.0.0 - 30/12/2024
```
[major] Combat Delegates were changed to provide the source component whenever applicable.
[added] An extensible Behavior Tree Service that can send Combo Events to an ongoing Combo Ability branch.
[added] Option to collect specific Melee Scan meshes, via Gameplay Tags.
[added] Added "Mac" to the list of Allowed Build Platforms.
[improvement] Support for additional roles in the Opportunity Attack ability.
[improvement] Exposed optional settings for Damage and Poise Consumption in weapons and projectiles.
[improvement] Added an extension point for opportunity attacks, before starting the paired animation.
[improvement] Added a more flexible way to select melee impact particles, sounds and shakes in the Base Weapon actor.
[improvement] Added a more flexible way to select melee impact particles and sounds in the Base Projectile actor.
[improvement] Exposed the default widget visibility in the base Combat Widget. 
[bugfix] Removed all warnings regarding Ability Tags, introduced in Unreal Engine 5.5. 
[bugfix] Fixed a crash that could happen while executing an animation ability, with Motion Warping, and closing the game before ability ends.
[bugfix] Fixed the ragdoll being invoked, even when no ragdoll settings were enabled.
[bugfix] Fixed cancel regen tag application for max health, stamina and magic.
```

## 2.18.42 - 22/11/2024
```
[added] Animation Provider for random animations.
[added] Viewmodel for Target Lock.
[improvement] Base combat widget has flexible flags to show/collapse based on a combatant actor being set or not.
[bugfix] Added missing include that could break some builds.
[bugfix] Fixed property visibility for State Tree nodes, so they can be used for property binding.
```

## 2.16.40 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[improvement] Introduced functions to dynamically modify projectile and cast damage.
[bugfix] Fixed the Combat Aware interface for widgets and widget components.
```

## 2.15.38 - 04/10/2024
```
[added] Camera Targeting Task for the Gameplay Targeting System.
[added] Added options to change Animation Sections in the Cast Ability.
[added] Added AI tests for "Is Dead" using the Damage Component.
[added] Exposed Play Rate to Montage Abilities, unified animation-related interfaces, removing the "WeaponAnimationProvider" one.
[improvement] Added an extension point to the Stagger Ability, that can be used for custom "on stagger" events.
[improvement] Improved lifecycle for poolable actors to be more flexible.
[improvement] Ensured that casts and projectiles will only ever be called once for each request.
[improvement] Added an option to recalculate the projectile's speed at any time.
[improvement] Refactored the Dissolve Component for better flexibility (i.e. "Appear").
[improvement] Exposed method to change Montage Sections (i.e. "Aiming/Firing on cast").
[improvement] Moved Melee Scan logic to the Combat Manager and ensured that it has a "duration" fallback so it won't rely on the "Notify End".
[improvement] Exposed Hit Results to the Damage Calculation.
[bugfix] Fixed the cast not triggering the first time for simulated clients.
[bugfix] Handled authority scenario for Status Effects Viewmodel.
[bugfix] Reinforced the Actor Pool initialization for blueprint subclasses.
[bugfix] Fixed damage AI event being called on dead actors.
[bugfix] Ensured that Melee Scans start/end correctly in dedicated servers.
[bugfix] Weapon Impact Cosmetics component name changed to "WeaponCosmetics".
```

## 2.11.27 - 19/10/2024
```
[added] Added the RefreshTargetWarp Animation Notify, to refresh the Combat Warp Target.
[added] Added Combo Task to manually set a Combo Count.
[added] Introduced a new, formal way to handle recurring damage, that's perceived by other systems.
[added] Status Effects view model.
[added] Magic Regeneration Gameplay Effect.
[added] Automatic AI perception for Damage Events.
[added] Ragdoll support via the Ragdoll Animation Notify.
[added] Added support for Linux.
[improvement] Added option to disable collision with warp targets in gameplay abilities.
[improvement] Combo Abilities can also have costs/cooldowns, regardless of the triggered abilities in the combo.
[improvement] Ensured that Marker Widgets are collapsed when not in use.
[improvement] Added an "Ignored Damage" filter to Hit Reactions.
[improvement] Added more logs to Melee Scans.
[improvement] Handled uninitialized states for the Widget Component.
[improvement] Added the correct melee/ranged damage for Attacks, instead of the "base" one.
[improvement] Added a directional offset angle for evades, to accommodate angled forward references.
[improvement] Added directional logic to death ability.
[improvement] Cast actors can obtain precise hits even for component collisions.
[improvement] Introduced new add/remove weapons to the default Weapon Manager.
[bugfix] Ensured that Opportunity Attacks will only dismiss a target if they were actually triggered.
[bugfix] Fixed calculation for left/right hit reactions.
[bugfix] Fixed the Magic Percent value in the Vitals viewmodel.
[bugfix] Reinforced tags as rollbacks in the Melee Scan.
[bugfix] Fixed ASC requirement from Cast Actors to apply damage.
```

## 2.7.16 - 24/09/2024
```
[added] Added a Weapon Animation Provider for abilities. This allows weapons to provide their own animations and reuse the same ability.
[added] Added the Weapon Trail notify option to the Melee Scan. This allows you to use trails with your weapons, in the same duration of the melee scan.
[improvement] Added the option to forward Gameplay Events directly to the Combo Manager, without needing the Input Action mappings.
[improvement] Added option to automatically rotate the player controller to face the target locked.
[improvement] Added a watch for the owner's death in the Weapon Manager.
[improvement] Added option to dissolve attached actors, such as weapons, along with the owner.
[improvement] Added blending of hit location and source location to Hit Reactions.
[improvement] Removed prioritization of current target in warp providers. That can be done with sorting in the Targeting Preset.
[improvement] Ensured that fallback abilities are only triggered after the opportunity attack ends, to avoid blocks.
[improvement] Created an Ability Task for contextual animations.
[improvement] Added an option for cast actors to add or remove casters from overlaps.
[improvement] Removed the combo data asset that was already unnecessary on v2.
[improvement] Removed the requirement from the Combo Gameplay Event to be triggered on both Server and Client. Local client is enough to advance it.
[bugfix] Fixed case for include directive in TargetProvider_TargetingSystem.
[bugfix] Fixed Niagara parameter name in NinjaCombatWeaponCosmeticsComponent.
[bugfix] Ensures that contextual animations always start with correct actor transforms, even when they are not automatically calculated.
[bugfix] Removed a temp log from NinjaCombatAttackSupport.
[bugfix] Fixed basic setup for the Damage Execution in damage effects.
[bugfix] Fixed the Gameplay Cue filter in the Cast Ability.
```

## 2.0.0 - 08/09/2024
```
[major] Reviewed setup and architecture, with the main goal of simplifying the system's usage.
[major] Rebuilt the Opportunity System.
[major] Rebuilt the UI module to fully leverage View Models.
[major] Updated the Combo System so it's easier to configure. The Data Asset does not exist anymore.
[major] Updated the Cast System so it's more flexible and supports Gameplay Ability Target Actors.
[added] Added directional Hit Reactions.
[added] Added a Weapon Cosmetics component that unifies how Gameplay Cues are implemented (particles, sounds, camera).
[added] Added a new (optional) Player Camera Manager that blends between cameras, used by the Opportunity System.
[improvement] Simplified the integration with Ninja Inventory.
[improvement] Updated the default Weapon Manager so it can be used as-is for simpler scenarios.
[improvement] Reviewed and expanded the Poise and Stagger functionality so it is easier to use.
[improvement] Added the option to override Gameplay Effects from Melee Scans and Projectile Launch requests.
[bugfix] Fixed projectiles not working when retrieved from the Actor Pool.
[bugfix] Fixed projectiles not transferring their original Hit Result to the Gameplay Cue.
[bugfix] Fixed combo State Trees not being cancelled along with the combo ability.
[bugfix] Removed FORCEINLINE macros that were breaking builds.
```

## 1.15.10 - 27/07/2024
```
[improvement] Added more checks for the Critical Damage Calculation, to avoid possible crashes.
[improvement] Added more verbose logs to damage and defense systems.
[improvement] Exposed damage details in the Damage Handler, for easier access in Blueprint implementations.
[bugfix] Fixed the calculation of Health, Stamina and Magic totals, ensuring that these are updated at the right time.
[bugfix] Reinforced components in the Damage Received fast array serializer, to avoid crashes in more complex actor hierarchies.
[deprecation] The Gameplay Effect used to initialize attributes have been removed.
```

## 1.15.4 - 17/07/2024
```
[added] Added more methods to the Default Weapon Manager, allowing adding and removing weapon actors.
[added] Added exclusive delegates to the Default Weapon Manager that will broadcast weapons that were added or removed.
[improvement] Added more logs to the Default Weapon Manager, to help troubleshooting the weapon initialization.
[improvement] Renamed the function LoadAttachedWeapons to FindAttachedWeapons to better convey its purpose.
[improvement] Added more logs to the Melee Scan Notify to help troubleshooting.
[bugfix] Fix the weapon check in the Melee Scan Notify, to ensure it's compatible with both C++ and Blueprint Weapons.
```

## 1.13.3 - 08/07/2024
```
[added] Added an integration with Ninja Factions, to allow members of the same faction to have friendly fire enabled or disabled.
[improvement] Improved the Actor Pool to provide more extension points to users needing to expand on it.
[bugfix] Ensure that the End Melee Scan event is not triggered if a Melee Start Scan was not triggered as well.
[bugfix] Fixed the edit condition for the weapon query in the Melee Scan.
```

## 1.12.9 - 27/06/2024
```
[added] Added an Animation Task interface and a base class for common Animation Montages. This simplifies creating tasks for other types of animations (i.e. Paper2D).
[improvement] Re-enabled all blueprint activations for combat abilities, with an option to disable them via properties.
[improvement] Renamed UNinjaCombatMontageAbility to UNinjaCombatAnimationAbility. A class redirect was added to avoid issues with Blueprints, but your C++ classes will have to be re-parented.
[improvement] Removed the requirement of a UAbilityTask_PlayMontageAndWait in the UNinjaCombatAnimationAbility.
[improvement] Marked the InitializeAnimationTask function from UNinjaCombatAnimationAbility as Blueprint Native.
[improvement] Marked the SetupAndPlayAnimation function from UNinjaCombatAnimationAbility as Blueprint Native.
[improvement] Reviewed the relationship between InitializeAnimationTask and SetupAndPlayAnimation to support other Animation Tasks.
[improvement] Ensured that the Ability System's Actor Info will collect the combatant's main Skeletal Mesh Component and Animation Instance.
[bugfix] Fixed the flag bStrafeWhileLockedOnTarget being ignored in the CombatMovementComponent.
[bugfix] Fixed the assigned Scan Class being ignored by the UAnimNotifyState_MeleeScan.
```

## 1.11.13 - 21/06/2024
```
[added] Added a configurable reusable Actor to indicate the Target Lock.
[added] A flexible Actor Pool, used for Projectiles and Cast actors.
[added] A Weapon Manager integrated with the Ninja Inventory/Equipment, usable if Ninja Inventory is detected in the project/engine.
[improvement] Improved the Actor destruction in the Damage Manager, allowing setting a lifespan instead of destroying actors immediately.
[improvement] Added velocity settings for strafing on the Movement Component.
[improvement] Created a schema for Combo Trees, validating the combo context and providing easier access to the Combo Manager (5.4 and above).
[deprecation] The Gameplay Effect used to initialize attributes will be removed in favor of the Datatable initialization.
```

## 1.8.12 - 30/04/2024
```
[added] Added a base Animation Instance class that contains the commonly expected movement values, plus bindings to the Combat System.
[added] Introduced the Model-View-View-Model (MVVM) pattern to Combat Widgets. You can learn more about this in the docs.
[added] Added a new Damage Handler for Camera Shakes.
[added] Added a new Damage Handler for Dissolving Materials.
[added] Added Opportunity Abilities (for attackers and victims). It can be used as a base for backstabs, stealth take-downs, ripostes, etc.
[added] Added the Parry Component and Backstab components for opportunity attacks.
[improvement] Enhanced the Block ability to simplify its usage.
[improvement] Enhanced the Evade ability to simplify its usage.
[improvement] Added lenient test functions for Actor Components that should implement Combat System interfaces.
[improvement] Improved multiple debug messages/ensure/assertions to hopefully facilitate troubleshooting.
[improvement] Added the Dead state tag as a blocker to any applicable Combat Ability and cancellation tags to the Death ability.
[improvement] Improved the Motion Warping System by allowing fine-tuning the target position via Scene Components.
[improvement] Upgraded to Unreal Engine 5.4.
[bugfix] Breaker hits won't have the "blocked" tag in their context anymore. This simplifies the setup of Hit Reactions.
[bugfix] Fixed the way rotations are set in Hit Reactions, so it can replicate properly.
[bugfix] Fixed a bug where the Death Ability could occasionally  raise a scope lock assertion.
[bugfix] Added the MinimalAPI class modifier that was missing in some interfaces.
[bugfix] Fixed the Damage Handler definition, to support generic Actor Components instead of the specific Damage Manager.
```

## 1.2.16 - 04/04/2024
```
[improvement] Improved flexibility to provide specific projectile classes to the Attack ability (weapon > owner > notify > ability).
[improvement] Modified access to many properties in the base projectile, they are now marked as BlueprintReadWrite.
[bugfix] Fixed the scenario where projectiles wouldn't launch correctly without a gameplay effect assigned to them.
```

## 1.2.13 - 01/04/2024
```
[added] Added Poise/Stagger mechanics. Hit Reactions can be "default" and "stagger" reactions.
[added] Added a Movement Manager Component. For now, it handles "walking while blocking" and "strafing while locked on target".
[improvement] The default Weapon Manager Component will load weapon actors attached to the owner.
[improvement] The default Weapon Manager Component allows subclasses to access the replicated weapon array.
[improvement] The Target Ability can be activated/deactivated from external events. Activation takes a target Actor in the payload.
[improvement] The Attack Ability provides functions that can be overridden to fine-tune Gameplay Effects and Levels.
[improvement] The Attack Ability automatically sets damage and poise to Gameplay Effects, if interfaces will provide them.
[improvement] Melee and Projectile interfaces can provide their respective Effect Levels.
[improvement] Melee and Projectile interfaces can provide damage and poise consumptions to Gameplay Effects, as "Set By Caller" magnitudes.
[improvement] Updated the Evade Ability to use the new Directional Evade Animation Provider.
[improvement] The Default Weapon Actor replicates its Gameplay Tags.
[improvement] Added a default setting to globally define the Motion Warping setting for Gameplay Abilities.
[improvement] Added a setting to determine the duration of Melee Scan debug information on screen.
[bugfix] The Damage Calculation will properly trigger conditional Gameplay Effects, if the damage output is greater than zero.
[bugfix] The Combo Manager is properly replicated to better support dedicated server scenarios.
```

## 1.0.0 - 15/03/2024
First release for Unreal Engine 5.3.

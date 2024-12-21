# Changelog
<primary-label ref="combat"/>

## 1.0.0 - 15/03/2024
First release for Unreal Engine 5.3.

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

## 1.2.16 - 04/04/2024
```
[improvement] Improved flexibility to provide specific projectile classes to the Attack ability (weapon > owner > notify > ability).
[improvement] Modified access to many properties in the base projectile, they are now marked as BlueprintReadWrite.
[bugfix] Fixed the scenario where projectiles wouldn't launch correctly without a gameplay effect assigned to them.
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

## 1.13.3 - 08/07/2024
```
[added] Added an integration with Ninja Factions, to allow members of the same faction to have friendly fire enabled or disabled.
[improvement] Improved the Actor Pool to provide more extension points to users needing to expand on it.
[bugfix] Ensure that the End Melee Scan event is not triggered if a Melee Start Scan was not triggered as well.
[bugfix] Fixed the edit condition for the weapon query in the Melee Scan.
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

## 1.15.10 - 27/07/2024
```
[improvement] Added more checks for the Critical Damage Calculation, to avoid possible crashes.
[improvement] Added more verbose logs to damage and defense systems.
[improvement] Exposed damage details in the Damage Handler, for easier access in Blueprint implementations.
[bugfix] Fixed the calculation of Health, Stamina and Magic totals, ensuring that these are updated at the right time.
[bugfix] Reinforced components in the Damage Received fast array serializer, to avoid crashes in more complex actor hierarchies.
[deprecation] The Gameplay Effect used to initialize attributes have been removed.
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

## 2.16.40 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[improvement] Introduced functions to dynamically modify projectile and cast damage.
[bugfix] Fixed the Combat Aware interface for widgets and widget components.
```

## 2.18.42 - 22/11/2024
```
[added] Animation Provider for random animations.
[added] Viewmodel for Target Lock.
[improvement] Base combat widget has flexible flags to show/collapse based on a combatant actor being set or not.
[bugfix] Added missing include that could break some builds.
[bugfix] Fixed property visibility for State Tree nodes, so they can be used for property binding.
```

## 3.0.0
<secondary-label ref="wip"/>
```
[major] Combat Delegates were changed to provide the source component whenever applicable.
[added] An extensible Behavior Tree Service that can send Combo Events to an ongoing Combo Ability branch.
[added] Option to collect specific Melee Scan meshes, via Gameplay Tags.
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
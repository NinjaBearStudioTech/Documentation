# Changelog
<primary-label ref="combat"/>

## 7.0.0
> **Important Changes in this version**
>
> 1. Magic attributes and effects were renamed to Mana.
> 2. Projectile Actors were rewritten to use Projectile Behaviors, hosted by the Projectile Behavior Component.
> 3. Cast Actors were rewritten to use Cast Behaviors, hosted by the Cast Behavior Component.
> 4. New Launch Projectile and Melee Attack abilities should be used. The old "one size fits all" attack ability is deprecated.
> 5. Launch Projectile and Melee Scan Nofities have a new configuration struct. Old settings are deprecated.
```
<secondary-label ref="wip"/>
```
[major] Projectile Actors were rewritten to use Projectile Behaviors, hosted by the Projectile Behavior Component.
[major] Cast Actors were rewritten to use Cast Behaviors, hosted by the Cast Behavior Component.
[major] Melee Scan exchanges internal data, between Object and Ability Task, via Instanced Structs.
[major] Renamed Magic attribute (and related effects) to Mana.
[major] Consolidated Projectile interfaces.
[added] Base Ability Targeting Actor, compatible with the Actor Pool.
[added] Dedicated Launch Projectile ability.
[added] Dedicated Melee Scan ability. 
[changed] Introduced extension point for when a Cast has effectively started in the Ability.
[changed] Organized method visibility in Melee/Parry scans.
[changed] Centralized Health Damage and Poise Damage from Melee and Projectile Interfaces into the Magnitude Interface.
[changed] Better integrated Parry Scans and Melee Attacks, exposing available Parry Scan Windows through the Melee Interface.
[fixed] Corrected check for "InParryAttackerWindow" in the Combat Manager.
[fixed] Considering socket rotation to debug draw functions in the Melee Scan.
[fixed] Added missing EditCondition to the Cast Ability.
[fixed] Corrected optimal distance logic for Melee Motion Warping.
[fixed] Corrected interface name: ICombatMitigationAttributeSetInterface.
[fixed] Added missing export macro to the Melee Scan Anim Notify State.
[fixed] Added support to Gameplay Cue Parameters not based on Hit Results.
[fixed] Added default initialization for mitigation GE, to avoid spamming "SetByCaller" messages. 
[deprecated] The generic Attack Ability will be removed in a future version. Please update to specialized Melee, Ranged and Opportunity attacks.
[deprecated] Launch Projectile Animation Notify has a new structure to set the same properties. Please review your settings.
```

## 6.6.20 - 30/04/2026
```
[changed] Additional logs to track reflection bridge between Combat and Inventory.
[fixed] Corrected knockdown condition in the dead effect requirement.
[fixed] Removed hard assertion for missing targets in the Combat Attribute Set.
[fixed] Corrected knockdown integration in the GAS layer.
```

## 6.6.17 - 17/04/2026
```
[added] Moved internal logic from the Combat Manager, into damage outcomes for Knockbacks, Last Stands and Death. 
[added] Option to delay Cast activations using the "Delayed" trigger.
[added] Mitigation classes have Tag Containers to indicate damage effects that should skip that mitigation.
[added] New Combo Task that deliberately opens or closes the Combo Window.
[added] Support for Passive and Initial Cooldown tags, analogous to Ninja GAS.
[added] Option do find adjacent targets (left/right) in the Target Lock ability.
[changed] Reviewed Cast Ability to unify all flows and avoid corner cases.
[changed] Created a separate Poolable Actor Component with primary logic.
[changed] Cast Ability will apply a "Waiting For Confirmation" effect state.
[changed] The Combat CMC has a new property, "StrafeWhileBlocking", which reinforces strafe while blocking.
[changed] The Combat CMC will perform retries when trying to connect to the Combat System.
[changed] The Combat Animation Instance will perform retries when trying to connect to the Combat System.
[changed] Introduced a catch-all tag for unblockable damage (Combat.Effect.Damage.Unblockable).
[changed] Combo Manager Component will reliably block duplicated events within the same scope.
[changed] Motion Warping Component has better tracking stability and will stop ticking more precisely.  
[fixed] Ensured that the Combat Manager validation it will add messages to the error window.
[fixed] Ensured that characters will not collide with the camera when they die.
[fixed] Ensured that the animation notify scheduler will always clean up on interruptions.
[fixed] Ensured that the animation notify scheduler will properly store meshes for notifies.
[fixed] Ensured that Cast Actors won't collide with themselves, including other instances of the same class type.
[fixed] Configured stacks for combat effects that cancel regeneration (stamina, poise and mana).
[fixed] Ensured that not setting a block angle correctly means "no angle check".
[fixed] Corrected target validation/binding/unbinding issues in the Target Lock Gameplay Ability and Target Lock ViewModel.
```

## 6.0.0 - 08/03/2026
> **Important Changes in this version**
>
> 1. Damage mitigation has been moved into dedicated objects, but its actual behavior hasn't changed. If you modified the mitigation pipeline, please review it to adhere to the new format.
> 2. To follow this new approach, the function name, in the Defense Interface, has been renamed from "DefendDamage" to "MitigateDamage". 
> 3. Damage Handlers were renamed to Damage Cosmetics. There are internal core redirectors to avoid configurations breaking and child Blueprints. You'll need to review C++ classes, if any.
> 4. Damage Outcomes are gameplay (auth/client) behaviors triggered from damage. Parts of the combat manager were migrated into them.
> 5. Both Damage Cosmetics and Damage Outcomes are added to the Damage Setup data asset.
```
[major] Damage mitigation is now a separated pipeline that can be modified, without extending the Combat Manager.
[major] Damage can now trigger Damage Outcomes (gameplay) Damage Cosmetics (vfx, sfx, etc.).
[major] A new data asset for damage mitigation has been introduced, analogous to the damage handling asset.
[added] Ammo tracking for the firearm component, and a ViewModel to display ammo count.
[added] Reload Gameplay Ability, along with Animation Provider and Reload Gameplay Event Animation Notify.
[added] Aim assist for firearm/shoot ability.
[added] Damage Absorption attributes (Absorption/MaxAbsorption) used during damage mitigation.
[changed] Added near blast settings for firearms and a pre-defined gameplay effect.
[changed] Pass on integration/reflection layer for Inventory and Factions.
[changed] Improved the Combat Status Effect UI data, added a new ViewModel for an individual Status Effect.
[changed] Reviewed the design of FNinjaCombatGameplayEffectContext to facilitate extensions.
[fixed] Fixed duplicated gameplay tag implementation.
```

## 5.11.20 - 12/01/2026
```
[added] Knockout state that can be triggered before death.
[added] Animation Provider compatible with Equipment Instances, where weapons are the "effect causer".
[added] Introduced an entirely new firearm system that pairs with the overhauled Shoot gameplay ability.
[added] New melee scan mode for component overlap.
[changed] Added flags to better control when attack animations should be canceled. This helps to avoid idle poses while net-synchronizing combos.
[changed] Integration with Ninja GAS new "Play Animation" features, which are better fitted for IK retargeting scenarios.
[changed] Organized/standardized all function categories.
[changed] Removed unused/duplicated weapon animation interface.
[changed] Added an output string that summarizes the combo state. Can be used with bindable texts in the Debug state tree task.
[changed] Added a hook in the Combo Ability, PrepareToActivateCombo, that can be used to perform tasks on granted abilities, before the combo starts.
[changed] Integrated Combat Data Asset with the editor, to simplify the creation of relevant assets.
[fixed] Ensured that the attack task already binds to the projectile task before any setup.
[fixed] Using the correct class to notify damage instigators about the damage they applied.
[fixed] Reviewed ragdoll flow to ensure it will properly trigger on host and clients.
```

## 5.7.10 - 17/11/2025
```
[fixed] Removed TScriptInterface types from Projectile and Melee Scan notifies, to match the Weapon Manager interface.
```

## 5.7.9 - 17/11/2025
```
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 5.7.8 - 13/11/2025
```
[fixed] Corrected projectile handling to allow multiple projectiles from the same ability activation.
[fixed] Ensured that clients running UAbilityTask_WaitTargetDataWithActorCallback will receive the replicated target.
```

## 5.7.6 - 21/10/2025
```
[added] New network prediction strategy for Combos (open/close window, advance combo).
[added] New ability task for Net Sync with pre-defined server timeouts.
[changed] Added Combo State Tree validation for 5.6+.
[changed] Combat Animation Montage will change sections using the ASC.
[changed] Combo Manager will track combo window durations and fallback-close them, since notifies might not end correctly on dedicated servers.
[changed] Updated declarations using raw pointers, replacing them with TObjectPtr.
[fixed] Deferred ASC initialization in the base ViewModel will obtain world from the owning actor.
[fixed] Combat ViewModel resolver was renamed to follow the correct naming convention.
```

## 5.4.1 - 10/09/2025
```
[added] New strafe-related functions, integrated with the Target Manager.
[changed] Rewrote integration with Ninja Inventory, using reflection instead of compiler conditions. 
[changed] Rewrote integration with Ninja Factions, using reflection instead of compiler conditions.
```

## 5.1.1 - 23/08/2025
```
[changed] Updated integration with Ninja Inventory, to match version 2.0.0.
[changed] Exposed binding/unbinding function in the base Anim BP, to support deferred initialization.
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
[changed] Included guard conditions to avoid ticking in invalid component states.
[changed] Updated Gameplay Targeting "Target Lock Filter Task" so it won't filter actors when there's no lock-on.
[changed] Included option to perform an AOE selection in the Gameplay Targeting "Select Combat Target Task".
[changed] Exposed floor distance setting for the Cast Actor.
[changed] Tracking death/destroyed for warp targets to remove them from the component faster.
[changed] Implemented the time-stretching guard conditions for all Anim Notify states.
[changed] Included option to opt in/out of physical animations for recurring damage.
[changed] Exposed the trace channel used by Cast Actors to detect Hit Results.
[changed] Changed the Physical Reaction Damage Handler, so it's tag-based. 
[changed] Introduced a fallback method for projectiles launched when an actor was not obtained by the targeting system. 
[fixed] Fixed the calculation for the Motion Warping pushback.
[fixed] Fixed the starting bone for the Physical Animation Component.
[fixed] Fixed dangling warping targets that might be invalid.
[fixed] Fixed crashes that might happen when closing the game while blocking.
[fixed] Fixed scenarios where the effect context proxy would incorrectly discard zero damage. 
[fixed] Fixed Target Lock event handling and source lock effect application. 
[fixed] Fixed Invulnerability calculation, to actually reset the damage on the Defense Manager. 
```

## 4.1.3 - 25/04/2025
```
[added] Added `GetAdditionalCombatMagnitudes` to attacks and casts, allowing more flexibility regarding damage effect magnitudes.
[changed] Introduced the `bAllowMeleePushback` property in the Motion Warping Component, to allow melee pushback from the optimal distance.
[fixed] Added guard condition to avoid editor crashes in the `AnimNotify_Cast`.
[fixed] Fixed the guard condition for the Targeting Subsystem in the Motion Warping component.
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
[changed] Organized the Combat Ability Tags to allow other types of game-related categories, without clutter.
[changed] Added support for multiple hits in the same melee scan.
[changed] Marked Attribute Set functions "InitializeDamageCalculationInput" and "ApplyDamage" as virtual.
[changed] Added a base cost attribute for Stamina and Magic.
[changed] Added support functions to the base Weapon Manager.
[changed] Covered Player States and Controllers in the GetCombatManagerComponent function, from the Combat Library.
[changed] Exposed the combat forward reference in the Combat Manager and Function Library.
[changed] Exposed setters for the speeds in the custom Movement Manager and getters for current states.
[changed] Improved the way the Combat Manager is retrieved via library, supporting multiple types of owner: controller, player state, weapon.
[changed] Exposed access to the current Gameplay Ability Target Actor, via the Target Manager interface/component.
[changed] Simplified the Cast flow for GAS Targeting Actors in the Cast Ability.
[changed] Allowed the base Animation Ability to dynamically determine if commits should be done before the animation plays.
[changed] Lowered severity of the log, when a weapon is not found by normal means.
[changed] Exposed the Root Motion Scale in the Animation Provider object.
[changed] Added a logic path for game cues to play Camera Shakes for the local player, even if no target was hit (i.e. hit the ground).
[changed] Improved the "AlignWithFloor" function, from the base Cast Actor, so it also aligns with the floor orientation.
[changed] Exposed the last scans and positions obtained by a Melee Scan.
[changed] Simplified the extension of melee trace cosmetic parameters.
[changed] Added a test to the cosmetics component, in case the game ends before the callback is invoked.
[changed] Added a "GetCastOwner" to the Cast Interface.
[changed] Added a block tag for Hit Reactions.
[changed] Added an option for Cast Actors to manage application and removal of infinite Gameplay Effects while actors are colliding with them.
[changed] Added an option for Cast Abilities to commit after the cast has been completed.
[changed] Reviewed and improved how the Physical Animation Component works for hit reactions.
[fixed] Fixed the cancel regeneration tags being applied incorrectly.
[fixed] Ensured that predicted rep-notifies in the combat manager won't broadcast twice (for prediction and replication).
[fixed] Ensured warp targets are cleared when animation abilities end.
[fixed] Fixed the armor mitigation calculation.
[fixed] Fixed the name shown for the Combat Animation Ability Task, in the editor node.
[fixed] Fixed a bug in the Combat Animation Ability Task, that would avoid the montage to be moved to another section.
[fixed] Ensured that the Wait Target Data With Actor Callback Task properly correctly applies modifications.
[fixed] Fixed a call to the "_implementation" version of "CastToTargets", in the Cast ability.
[fixed] Handled "lifespan on death" when there's no damage setup provided during the death event. 
[fixed] Fixed hard requirement for poolable actors in the Cast Ability.
[fixed] Removed the duplicated damage calculation from the ranged damage effect.
[fixed] Correctly handling stacks in the Status Effect ViewModel.
[fixed] Added missing calls to super in Notifies and States.
[fixed] Fixed the logic for "Actors Hit" in the projectile Targeting Filter Task.
```

## 3.1.6 - 31/01/2025
```
[added] Handling scenarios where a melee attack hits non-combatant actors, such as the environment.
[changed] Vastly improved how the Combat Framework retrieves Combat Meshes and Anim Instances.
[changed] Improved categories and function settings from the Actor Pool and its Function Library.
[fixed] Ensured that combo delegates are broadcast correctly when the combo is reset, considering interruptions.
[fixed] Ensured that melee cosmetic parameters are properly using the Niagara parameter names set.
[fixed] Ensured that the play rate set by Animation Providers carries over to the Animation Montage task.
[fixed] Fixed the Defend Damage calculation, so it calculates based on the final applied damage.
```

## 3.0.0 - 30/12/2024
```
[major] Combat Delegates were changed to provide the source component whenever applicable.
[added] An extensible Behavior Tree Service that can send Combo Events to an ongoing Combo Ability branch.
[added] Option to collect specific Melee Scan meshes, via Gameplay Tags.
[added] Added "Mac" to the list of Allowed Build Platforms.
[changed] Support for additional roles in the Opportunity Attack ability.
[changed] Exposed optional settings for Damage and Poise Consumption in weapons and projectiles.
[changed] Added an extension point for opportunity attacks, before starting the paired animation.
[changed] Added a more flexible way to select melee impact particles, sounds and shakes in the Base Weapon actor.
[changed] Added a more flexible way to select melee impact particles and sounds in the Base Projectile actor.
[changed] Exposed the default widget visibility in the base Combat Widget. 
[fixed] Removed all warnings regarding Ability Tags, introduced in Unreal Engine 5.5. 
[fixed] Fixed a crash that could happen while executing an animation ability, with Motion Warping, and closing the game before ability ends.
[fixed] Fixed the ragdoll being invoked, even when no ragdoll settings were enabled.
[fixed] Fixed cancel regen tag application for max health, stamina and magic.
```

## 2.18.42 - 22/11/2024
```
[added] Animation Provider for random animations.
[added] Viewmodel for Target Lock.
[changed] Base combat widget has flexible flags to show/collapse based on a combatant actor being set or not.
[fixed] Added missing include that could break some builds.
[fixed] Fixed property visibility for State Tree nodes, so they can be used for property binding.
```

## 2.16.40 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[changed] Introduced functions to dynamically modify projectile and cast damage.
[fixed] Fixed the Combat Aware interface for widgets and widget components.
```

## 2.15.38 - 04/10/2024
```
[added] Camera Targeting Task for the Gameplay Targeting System.
[added] Added options to change Animation Sections in the Cast Ability.
[added] Added AI tests for "Is Dead" using the Damage Component.
[added] Exposed Play Rate to Montage Abilities, unified animation-related interfaces, removing the "WeaponAnimationProvider" one.
[changed] Added an extension point to the Stagger Ability, that can be used for custom "on stagger" events.
[changed] Improved lifecycle for poolable actors to be more flexible.
[changed] Ensured that casts and projectiles will only ever be called once for each request.
[changed] Added an option to recalculate the projectile's speed at any time.
[changed] Refactored the Dissolve Component for better flexibility (i.e. "Appear").
[changed] Exposed method to change Montage Sections (i.e. "Aiming/Firing on cast").
[changed] Moved Melee Scan logic to the Combat Manager and ensured that it has a "duration" fallback so it won't rely on the "Notify End".
[changed] Exposed Hit Results to the Damage Calculation.
[fixed] Fixed the cast not triggering the first time for simulated clients.
[fixed] Handled authority scenario for Status Effects Viewmodel.
[fixed] Reinforced the Actor Pool initialization for blueprint subclasses.
[fixed] Fixed damage AI event being called on dead actors.
[fixed] Ensured that Melee Scans start/end correctly in dedicated servers.
[fixed] Weapon Impact Cosmetics component name changed to "WeaponCosmetics".
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
[changed] Added option to disable collision with warp targets in gameplay abilities.
[changed] Combo Abilities can also have costs/cooldowns, regardless of the triggered abilities in the combo.
[changed] Ensured that Marker Widgets are collapsed when not in use.
[changed] Added an "Ignored Damage" filter to Hit Reactions.
[changed] Added more logs to Melee Scans.
[changed] Handled uninitialized states for the Widget Component.
[changed] Added the correct melee/ranged damage for Attacks, instead of the "base" one.
[changed] Added a directional offset angle for evades, to accommodate angled forward references.
[changed] Added directional logic to death ability.
[changed] Cast actors can obtain precise hits even for component collisions.
[changed] Introduced new add/remove weapons to the default Weapon Manager.
[fixed] Ensured that Opportunity Attacks will only dismiss a target if they were actually triggered.
[fixed] Fixed calculation for left/right hit reactions.
[fixed] Fixed the Magic Percent value in the Vitals viewmodel.
[fixed] Reinforced tags as rollbacks in the Melee Scan.
[fixed] Fixed ASC requirement from Cast Actors to apply damage.
```

## 2.7.16 - 24/09/2024
```
[added] Added a Weapon Animation Provider for abilities. This allows weapons to provide their own animations and reuse the same ability.
[added] Added the Weapon Trail notify option to the Melee Scan. This allows you to use trails with your weapons, in the same duration of the melee scan.
[changed] Added the option to forward Gameplay Events directly to the Combo Manager, without needing the Input Action mappings.
[changed] Added option to automatically rotate the player controller to face the target locked.
[changed] Added a watch for the owner's death in the Weapon Manager.
[changed] Added option to dissolve attached actors, such as weapons, along with the owner.
[changed] Added blending of hit location and source location to Hit Reactions.
[changed] Removed prioritization of current target in warp providers. That can be done with sorting in the Targeting Preset.
[changed] Ensured that fallback abilities are only triggered after the opportunity attack ends, to avoid blocks.
[changed] Created an Ability Task for contextual animations.
[changed] Added an option for cast actors to add or remove casters from overlaps.
[changed] Removed the combo data asset that was already unnecessary on v2.
[changed] Removed the requirement from the Combo Gameplay Event to be triggered on both Server and Client. Local client is enough to advance it.
[fixed] Fixed case for include directive in TargetProvider_TargetingSystem.
[fixed] Fixed Niagara parameter name in NinjaCombatWeaponCosmeticsComponent.
[fixed] Ensures that contextual animations always start with correct actor transforms, even when they are not automatically calculated.
[fixed] Removed a temp log from NinjaCombatAttackSupport.
[fixed] Fixed basic setup for the Damage Execution in damage effects.
[fixed] Fixed the Gameplay Cue filter in the Cast Ability.
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
[changed] Simplified the integration with Ninja Inventory.
[changed] Updated the default Weapon Manager so it can be used as-is for simpler scenarios.
[changed] Reviewed and expanded the Poise and Stagger functionality so it is easier to use.
[changed] Added the option to override Gameplay Effects from Melee Scans and Projectile Launch requests.
[fixed] Fixed projectiles not working when retrieved from the Actor Pool.
[fixed] Fixed projectiles not transferring their original Hit Result to the Gameplay Cue.
[fixed] Fixed combo State Trees not being cancelled along with the combo ability.
[fixed] Removed FORCEINLINE macros that were breaking builds.
```

## 1.15.10 - 27/07/2024
```
[changed] Added more checks for the Critical Damage Calculation, to avoid possible crashes.
[changed] Added more verbose logs to damage and defense systems.
[changed] Exposed damage details in the Damage Handler, for easier access in Blueprint implementations.
[fixed] Fixed the calculation of Health, Stamina and Magic totals, ensuring that these are updated at the right time.
[fixed] Reinforced components in the Damage Received fast array serializer, to avoid crashes in more complex actor hierarchies.
[deprecated] The Gameplay Effect used to initialize attributes have been removed.
```

## 1.15.4 - 17/07/2024
```
[added] Added more methods to the Default Weapon Manager, allowing adding and removing weapon actors.
[added] Added exclusive delegates to the Default Weapon Manager that will broadcast weapons that were added or removed.
[changed] Added more logs to the Default Weapon Manager, to help troubleshooting the weapon initialization.
[changed] Renamed the function LoadAttachedWeapons to FindAttachedWeapons to better convey its purpose.
[changed] Added more logs to the Melee Scan Notify to help troubleshooting.
[fixed] Fix the weapon check in the Melee Scan Notify, to ensure it's compatible with both C++ and Blueprint Weapons.
```

## 1.13.3 - 08/07/2024
```
[added] Added an integration with Ninja Factions, to allow members of the same faction to have friendly fire enabled or disabled.
[changed] Improved the Actor Pool to provide more extension points to users needing to expand on it.
[fixed] Ensure that the End Melee Scan event is not triggered if a Melee Start Scan was not triggered as well.
[fixed] Fixed the edit condition for the weapon query in the Melee Scan.
```

## 1.12.9 - 27/06/2024
```
[added] Added an Animation Task interface and a base class for common Animation Montages. This simplifies creating tasks for other types of animations (i.e. Paper2D).
[changed] Re-enabled all blueprint activations for combat abilities, with an option to disable them via properties.
[changed] Renamed UNinjaCombatMontageAbility to UNinjaCombatAnimationAbility. A class redirect was added to avoid issues with Blueprints, but your C++ classes will have to be re-parented.
[changed] Removed the requirement of a UAbilityTask_PlayMontageAndWait in the UNinjaCombatAnimationAbility.
[changed] Marked the InitializeAnimationTask function from UNinjaCombatAnimationAbility as Blueprint Native.
[changed] Marked the SetupAndPlayAnimation function from UNinjaCombatAnimationAbility as Blueprint Native.
[changed] Reviewed the relationship between InitializeAnimationTask and SetupAndPlayAnimation to support other Animation Tasks.
[changed] Ensured that the Ability System's Actor Info will collect the combatant's main Skeletal Mesh Component and Animation Instance.
[fixed] Fixed the flag bStrafeWhileLockedOnTarget being ignored in the CombatMovementComponent.
[fixed] Fixed the assigned Scan Class being ignored by the UAnimNotifyState_MeleeScan.
```

## 1.11.13 - 21/06/2024
```
[added] Added a configurable reusable Actor to indicate the Target Lock.
[added] A flexible Actor Pool, used for Projectiles and Cast actors.
[added] A Weapon Manager integrated with the Ninja Inventory/Equipment, usable if Ninja Inventory is detected in the project/engine.
[changed] Improved the Actor destruction in the Damage Manager, allowing setting a lifespan instead of destroying actors immediately.
[changed] Added velocity settings for strafing on the Movement Component.
[changed] Created a schema for Combo Trees, validating the combo context and providing easier access to the Combo Manager (5.4 and above).
[deprecated] The Gameplay Effect used to initialize attributes will be removed in favor of the Datatable initialization.
```

## 1.8.12 - 30/04/2024
```
[added] Added a base Animation Instance class that contains the commonly expected movement values, plus bindings to the Combat System.
[added] Introduced the Model-View-View-Model (MVVM) pattern to Combat Widgets. You can learn more about this in the docs.
[added] Added a new Damage Handler for Camera Shakes.
[added] Added a new Damage Handler for Dissolving Materials.
[added] Added Opportunity Abilities (for attackers and victims). It can be used as a base for backstabs, stealth take-downs, ripostes, etc.
[added] Added the Parry Component and Backstab components for opportunity attacks.
[changed] Enhanced the Block ability to simplify its usage.
[changed] Enhanced the Evade ability to simplify its usage.
[changed] Added lenient test functions for Actor Components that should implement Combat System interfaces.
[changed] Improved multiple debug messages/ensure/assertions to hopefully facilitate troubleshooting.
[changed] Added the Dead state tag as a blocker to any applicable Combat Ability and cancellation tags to the Death ability.
[changed] Improved the Motion Warping System by allowing fine-tuning the target position via Scene Components.
[changed] Upgraded to Unreal Engine 5.4.
[fixed] Breaker hits won't have the "blocked" tag in their context anymore. This simplifies the setup of Hit Reactions.
[fixed] Fixed the way rotations are set in Hit Reactions, so it can replicate properly.
[fixed] Fixed a bug where the Death Ability could occasionally  raise a scope lock assertion.
[fixed] Added the MinimalAPI class modifier that was missing in some interfaces.
[fixed] Fixed the Damage Handler definition, to support generic Actor Components instead of the specific Damage Manager.
```

## 1.2.16 - 04/04/2024
```
[changed] Improved flexibility to provide specific projectile classes to the Attack ability (weapon > owner > notify > ability).
[changed] Modified access to many properties in the base projectile, they are now marked as BlueprintReadWrite.
[fixed] Fixed the scenario where projectiles wouldn't launch correctly without a gameplay effect assigned to them.
```

## 1.2.13 - 01/04/2024
```
[added] Added Poise/Stagger mechanics. Hit Reactions can be "default" and "stagger" reactions.
[added] Added a Movement Manager Component. For now, it handles "walking while blocking" and "strafing while locked on target".
[changed] The default Weapon Manager Component will load weapon actors attached to the owner.
[changed] The default Weapon Manager Component allows subclasses to access the replicated weapon array.
[changed] The Target Ability can be activated/deactivated from external events. Activation takes a target Actor in the payload.
[changed] The Attack Ability provides functions that can be overridden to fine-tune Gameplay Effects and Levels.
[changed] The Attack Ability automatically sets damage and poise to Gameplay Effects, if interfaces will provide them.
[changed] Melee and Projectile interfaces can provide their respective Effect Levels.
[changed] Melee and Projectile interfaces can provide damage and poise consumptions to Gameplay Effects, as "Set By Caller" magnitudes.
[changed] Updated the Evade Ability to use the new Directional Evade Animation Provider.
[changed] The Default Weapon Actor replicates its Gameplay Tags.
[changed] Added a default setting to globally define the Motion Warping setting for Gameplay Abilities.
[changed] Added a setting to determine the duration of Melee Scan debug information on screen.
[fixed] The Damage Calculation will properly trigger conditional Gameplay Effects, if the damage output is greater than zero.
[fixed] The Combo Manager is properly replicated to better support dedicated server scenarios.
```

## 1.0.0 - 15/03/2024
First release for Unreal Engine 5.3.

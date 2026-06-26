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
<secondary-label ref="wip"/>
```
[major] Projectile Actors were rewritten to use Projectile Behaviors, hosted by the Projectile Behavior Component.
[major] Cast Actors were rewritten to use Cast Behaviors, hosted by the Cast Behavior Component.
[major] Melee Scan exchanges internal data, between Object and Ability Task, via Instanced Structs.
[major] Renamed Magic attribute (and related effects) to Mana.
[major] Consolidated Projectile interfaces.
[new] Base Ability Targeting Actor, compatible with the Actor Pool.
[new] Dedicated Launch Projectile ability.
[new] Dedicated Melee Scan ability. 
[change] Introduced extension point for when a Cast has effectively started in the Ability.
[change] Organized method visibility in Melee/Parry scans.
[change] Centralized Health Damage and Poise Damage from Melee and Projectile Interfaces into the Magnitude Interface.
[change] Better integrated Parry Scans and Melee Attacks, exposing available Parry Scan Windows through the Melee Interface.
[change] Exposed parameters for target cycling, in the target lock ability.
[change] Made the Combat/Faction integration component more flexible, allowing non-boolean mitigations.
[change] Replaced core stagger resolution in favour of the new outcome.
[fix] Corrected check for "InParryAttackerWindow" in the Combat Manager.
[fix] Considering socket rotation to debug draw functions in the Melee Scan.
[fix] Added missing EditCondition to the Cast Ability.
[fix] Corrected optimal distance logic for Melee Motion Warping.
[fix] Corrected interface name: ICombatMitigationAttributeSetInterface.
[fix] Added missing export macro to the Melee Scan Anim Notify State.
[fix] Added support to Gameplay Cue Parameters not based on Hit Results.
[fix] Added default initialization for mitigation GE, to avoid spamming "SetByCaller" messages. 
[fix] Corrected damage manager check in the Invulnerability mitigation class.
[fix] Corrected scheduled notify timelines crashing when an animation is playing and avatar becomes invalid.
[fix] Ensured that bot assets are only released after the bot is unpossessed.
[fix] Included Block Angle to the list of mitigation attributes.
[deprecated] The generic Attack Ability will be removed in a future version. Please update to specialized Melee, Ranged and Opportunity attacks.
[deprecated] Launch Projectile Animation Notify has a new structure to set the same properties. Please review your settings.
[build] Added support for Unreal Engine 5.8, removed support for Unreal Engine 5.5
```

## 6.6.20 - 30/04/2026
```
[change] Additional logs to track reflection bridge between Combat and Inventory.
[fix] Corrected knockdown condition in the dead effect requirement.
[fix] Removed hard assertion for missing targets in the Combat Attribute Set.
[fix] Corrected knockdown integration in the GAS layer.
```

## 6.6.17 - 17/04/2026
```
[new] Moved internal logic from the Combat Manager, into damage outcomes for Knockbacks, Last Stands and Death. 
[new] Option to delay Cast activations using the "Delayed" trigger.
[new] Mitigation classes have Tag Containers to indicate damage effects that should skip that mitigation.
[new] New Combo Task that deliberately opens or closes the Combo Window.
[new] Support for Passive and Initial Cooldown tags, analogous to Ninja GAS.
[new] Option do find adjacent targets (left/right) in the Target Lock ability.
[change] Reviewed Cast Ability to unify all flows and avoid corner cases.
[change] Created a separate Poolable Actor Component with primary logic.
[change] Cast Ability will apply a "Waiting For Confirmation" effect state.
[change] The Combat CMC has a new property, "StrafeWhileBlocking", which reinforces strafe while blocking.
[change] The Combat CMC will perform retries when trying to connect to the Combat System.
[change] The Combat Animation Instance will perform retries when trying to connect to the Combat System.
[change] Introduced a catch-all tag for unblockable damage (Combat.Effect.Damage.Unblockable).
[change] Combo Manager Component will reliably block duplicated events within the same scope.
[change] Motion Warping Component has better tracking stability and will stop ticking more precisely.  
[fix] Ensured that the Combat Manager validation it will add messages to the error window.
[fix] Ensured that characters will not collide with the camera when they die.
[fix] Ensured that the animation notify scheduler will always clean up on interruptions.
[fix] Ensured that the animation notify scheduler will properly store meshes for notifies.
[fix] Ensured that Cast Actors won't collide with themselves, including other instances of the same class type.
[fix] Configured stacks for combat effects that cancel regeneration (stamina, poise and mana).
[fix] Ensured that not setting a block angle correctly means "no angle check".
[fix] Corrected target validation/binding/unbinding issues in the Target Lock Gameplay Ability and Target Lock ViewModel.
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
[new] Ammo tracking for the firearm component, and a ViewModel to display ammo count.
[new] Reload Gameplay Ability, along with Animation Provider and Reload Gameplay Event Animation Notify.
[new] Aim assist for firearm/shoot ability.
[new] Damage Absorption attributes (Absorption/MaxAbsorption) used during damage mitigation.
[change] Added near blast settings for firearms and a pre-defined gameplay effect.
[change] Pass on integration/reflection layer for Inventory and Factions.
[change] Improved the Combat Status Effect UI data, added a new ViewModel for an individual Status Effect.
[change] Reviewed the design of FNinjaCombatGameplayEffectContext to facilitate extensions.
[fix] fix duplicated gameplay tag implementation.
```

## 5.11.20 - 12/01/2026
```
[new] Knockout state that can be triggered before death.
[new] Animation Provider compatible with Equipment Instances, where weapons are the "effect causer".
[new] Introduced an entirely new firearm system that pairs with the overhauled Shoot gameplay ability.
[new] New melee scan mode for component overlap.
[change] Added flags to better control when attack animations should be canceled. This helps to avoid idle poses while net-synchronizing combos.
[change] Integration with Ninja GAS new "Play Animation" features, which are better fitted for IK retargeting scenarios.
[change] Organized/standardized all function categories.
[change] Removed unused/duplicated weapon animation interface.
[change] Added an output string that summarizes the combo state. Can be used with bindable texts in the Debug state tree task.
[change] Added a hook in the Combo Ability, PrepareToActivateCombo, that can be used to perform tasks on granted abilities, before the combo starts.
[change] Integrated Combat Data Asset with the editor, to simplify the creation of relevant assets.
[fix] Ensured that the attack task already binds to the projectile task before any setup.
[fix] Using the correct class to notify damage instigators about the damage they applied.
[fix] Reviewed ragdoll flow to ensure it will properly trigger on host and clients.
```

## 5.7.10 - 17/11/2025
```
[fix] Removed TScriptInterface types from Projectile and Melee Scan notifies, to match the Weapon Manager interface.
```

## 5.7.9 - 17/11/2025
```
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 5.7.8 - 13/11/2025
```
[fix] Corrected projectile handling to allow multiple projectiles from the same ability activation.
[fix] Ensured that clients running UAbilityTask_WaitTargetDataWithActorCallback will receive the replicated target.
```

## 5.7.6 - 21/10/2025
```
[new] New network prediction strategy for Combos (open/close window, advance combo).
[new] New ability task for Net Sync with pre-defined server timeouts.
[change] Added Combo State Tree validation for 5.6+.
[change] Combat Animation Montage will change sections using the ASC.
[change] Combo Manager will track combo window durations and fallback-close them, since notifies might not end correctly on dedicated servers.
[change] Updated declarations using raw pointers, replacing them with TObjectPtr.
[fix] Deferred ASC initialization in the base ViewModel will obtain world from the owning actor.
[fix] Combat ViewModel resolver was renamed to follow the correct naming convention.
```

## 5.4.1 - 10/09/2025
```
[new] New strafe-related functions, integrated with the Target Manager.
[change] Rewrote integration with Ninja Inventory, using reflection instead of compiler conditions. 
[change] Rewrote integration with Ninja Factions, using reflection instead of compiler conditions.
```

## 5.1.1 - 23/08/2025
```
[change] Updated integration with Ninja Inventory, to match version 2.0.0.
[change] Exposed binding/unbinding function in the base Anim BP, to support deferred initialization.
```

## 5.0.0 - 04/07/2025
> **Important Changes in this version**
>
> 1. Due to the changes in the Combo Ability Task, you will need to reconfigure your combo tasks.
> 2. The native Inventory Integration is disabled, and we'll be restored for Inventory 2.0.
> 3. The Shoot Ability and Camera Aiming are still work-in-progress.
```
[major] Rewrote the Combo Ability Task, using the native base class, to align with the recent changes in UE 5.6. 
[new] New Shoot ability that can handle Hit-Scans and Projectiles, in a "firearms" context (wip)
[new] New Magnitude Calculation that can consider the current combo count.
[new] New Static Gameplay Cue Notify for Parry Windows.
[new] New Gameplay Effect Requirement that checks for actual participants in the Combat System.
[new] Added a dedicated ViewModel for the Riposte State.
[new] Added the option to use Chooser Tables for Hit Reactions.
[change] Included guard conditions to avoid ticking in invalid component states.
[change] Updated Gameplay Targeting "Target Lock Filter Task" so it won't filter actors when there's no lock-on.
[change] Included option to perform an AOE selection in the Gameplay Targeting "Select Combat Target Task".
[change] Exposed floor distance setting for the Cast Actor.
[change] Tracking death/destroyed for warp targets to remove them from the component faster.
[change] Implemented the time-stretching guard conditions for all Anim Notify states.
[change] Included option to opt in/out of physical animations for recurring damage.
[change] Exposed the trace channel used by Cast Actors to detect Hit Results.
[change] Changed the Physical Reaction Damage Handler, so it's tag-based. 
[change] Introduced a fallback method for projectiles launched when an actor was not obtained by the targeting system. 
[fix] fix the calculation for the Motion Warping pushback.
[fix] fix the starting bone for the Physical Animation Component.
[fix] fix dangling warping targets that might be invalid.
[fix] fix crashes that might happen when closing the game while blocking.
[fix] fix scenarios where the effect context proxy would incorrectly discard zero damage. 
[fix] fix Target Lock event handling and source lock effect application. 
[fix] fix Invulnerability calculation, to actually reset the damage on the Defense Manager. 
```

## 4.1.3 - 25/04/2025
```
[new] Added `GetAdditionalCombatMagnitudes` to attacks and casts, allowing more flexibility regarding damage effect magnitudes.
[change] Introduced the `bAllowMeleePushback` property in the Motion Warping Component, to allow melee pushback from the optimal distance.
[fix] Added guard condition to avoid editor crashes in the `AnimNotify_Cast`.
[fix] fix the guard condition for the Targeting Subsystem in the Motion Warping component.
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
[new] Added a dedicated flow for Parries and Ripostes, based on the active frames of the Melee Scan, or a dedicated Parry Window Notify State.
[new] Non-dynamic multicast delegates added to the Combat Manager, so they can be used with lambdas (i.e. State Tree Tasks).
[new] Non-dynamic multicast delegates added to the Combo Manager, so they can be used with lambdas (i.e. State Tree Tasks).
[new] A direct call to the source of damage, to notify damage applied to a target. Useful for XP, specific attack notifies, etc.
[new] An extensible State Tree Task that can send Combo Events to an ongoing Combo Ability task.
[new] Support for impact data tables that can automatically override the default impact cosmetics, based on the surface that was hit.
[new] Handling scenarios where a projectiles hit non-combatant actors, such as the environment.
[new] Added "Ready" and "Started" events to the Combat Animation Ability Task. They will notify these new stages in a combat animation.
[new] Added dedicated attributes for base damage bonus and base damage reduction.
[change] Organized the Combat Ability Tags to allow other types of game-related categories, without clutter.
[change] Added support for multiple hits in the same melee scan.
[change] Marked Attribute Set functions "InitializeDamageCalculationInput" and "ApplyDamage" as virtual.
[change] Added a base cost attribute for Stamina and Magic.
[change] Added support functions to the base Weapon Manager.
[change] Covered Player States and Controllers in the GetCombatManagerComponent function, from the Combat Library.
[change] Exposed the combat forward reference in the Combat Manager and Function Library.
[change] Exposed setters for the speeds in the custom Movement Manager and getters for current states.
[change] Improved the way the Combat Manager is retrieved via library, supporting multiple types of owner: controller, player state, weapon.
[change] Exposed access to the current Gameplay Ability Target Actor, via the Target Manager interface/component.
[change] Simplified the Cast flow for GAS Targeting Actors in the Cast Ability.
[change] Allowed the base Animation Ability to dynamically determine if commits should be done before the animation plays.
[change] Lowered severity of the log, when a weapon is not found by normal means.
[change] Exposed the Root Motion Scale in the Animation Provider object.
[change] Added a logic path for game cues to play Camera Shakes for the local player, even if no target was hit (i.e. hit the ground).
[change] Improved the "AlignWithFloor" function, from the base Cast Actor, so it also aligns with the floor orientation.
[change] Exposed the last scans and positions obtained by a Melee Scan.
[change] Simplified the extension of melee trace cosmetic parameters.
[change] Added a test to the cosmetics component, in case the game ends before the callback is invoked.
[change] Added a "GetCastOwner" to the Cast Interface.
[change] Added a block tag for Hit Reactions.
[change] Added an option for Cast Actors to manage application and removal of infinite Gameplay Effects while actors are colliding with them.
[change] Added an option for Cast Abilities to commit after the cast has been completed.
[change] Reviewed and improved how the Physical Animation Component works for hit reactions.
[fix] fix the cancel regeneration tags being applied incorrectly.
[fix] Ensured that predicted rep-notifies in the combat manager won't broadcast twice (for prediction and replication).
[fix] Ensured warp targets are cleared when animation abilities end.
[fix] fix the armor mitigation calculation.
[fix] fix the name shown for the Combat Animation Ability Task, in the editor node.
[fix] fix a bug in the Combat Animation Ability Task, that would avoid the montage to be moved to another section.
[fix] Ensured that the Wait Target Data With Actor Callback Task properly correctly applies modifications.
[fix] fix a call to the "_implementation" version of "CastToTargets", in the Cast ability.
[fix] Handled "lifespan on death" when there's no damage setup provided during the death event. 
[fix] fix hard requirement for poolable actors in the Cast Ability.
[fix] Removed the duplicated damage calculation from the ranged damage effect.
[fix] Correctly handling stacks in the Status Effect ViewModel.
[fix] Added missing calls to super in Notifies and States.
[fix] fix the logic for "Actors Hit" in the projectile Targeting Filter Task.
```

## 3.1.6 - 31/01/2025
```
[new] Handling scenarios where a melee attack hits non-combatant actors, such as the environment.
[change] Vastly improved how the Combat Framework retrieves Combat Meshes and Anim Instances.
[change] Improved categories and function settings from the Actor Pool and its Function Library.
[fix] Ensured that combo delegates are broadcast correctly when the combo is reset, considering interruptions.
[fix] Ensured that melee cosmetic parameters are properly using the Niagara parameter names set.
[fix] Ensured that the play rate set by Animation Providers carries over to the Animation Montage task.
[fix] fix the Defend Damage calculation, so it calculates based on the final applied damage.
```

## 3.0.0 - 30/12/2024
```
[major] Combat Delegates were changed to provide the source component whenever applicable.
[new] An extensible Behavior Tree Service that can send Combo Events to an ongoing Combo Ability branch.
[new] Option to collect specific Melee Scan meshes, via Gameplay Tags.
[new] Added "Mac" to the list of Allowed Build Platforms.
[change] Support for additional roles in the Opportunity Attack ability.
[change] Exposed optional settings for Damage and Poise Consumption in weapons and projectiles.
[change] Added an extension point for opportunity attacks, before starting the paired animation.
[change] Added a more flexible way to select melee impact particles, sounds and shakes in the Base Weapon actor.
[change] Added a more flexible way to select melee impact particles and sounds in the Base Projectile actor.
[change] Exposed the default widget visibility in the base Combat Widget. 
[fix] Removed all warnings regarding Ability Tags, introduced in Unreal Engine 5.5. 
[fix] fix a crash that could happen while executing an animation ability, with Motion Warping, and closing the game before ability ends.
[fix] fix the ragdoll being invoked, even when no ragdoll settings were enabled.
[fix] fix cancel regen tag application for max health, stamina and magic.
```

## 2.18.42 - 22/11/2024
```
[new] Animation Provider for random animations.
[new] Viewmodel for Target Lock.
[change] Base combat widget has flexible flags to show/collapse based on a combatant actor being set or not.
[fix] Added missing include that could break some builds.
[fix] fix property visibility for State Tree nodes, so they can be used for property binding.
```

## 2.16.40 - 16/11/2024
```
[new] Support for Unreal Engine 5.5.
[change] Introduced functions to dynamically modify projectile and cast damage.
[fix] fix the Combat Aware interface for widgets and widget components.
```

## 2.15.38 - 04/10/2024
```
[new] Camera Targeting Task for the Gameplay Targeting System.
[new] Added options to change Animation Sections in the Cast Ability.
[new] Added AI tests for "Is Dead" using the Damage Component.
[new] Exposed Play Rate to Montage Abilities, unified animation-related interfaces, removing the "WeaponAnimationProvider" one.
[change] Added an extension point to the Stagger Ability, that can be used for custom "on stagger" events.
[change] Improved lifecycle for poolable actors to be more flexible.
[change] Ensured that casts and projectiles will only ever be called once for each request.
[change] Added an option to recalculate the projectile's speed at any time.
[change] Refactored the Dissolve Component for better flexibility (i.e. "Appear").
[change] Exposed method to change Montage Sections (i.e. "Aiming/Firing on cast").
[change] Moved Melee Scan logic to the Combat Manager and ensured that it has a "duration" fallback so it won't rely on the "Notify End".
[change] Exposed Hit Results to the Damage Calculation.
[fix] fix the cast not triggering the first time for simulated clients.
[fix] Handled authority scenario for Status Effects Viewmodel.
[fix] Reinforced the Actor Pool initialization for blueprint subclasses.
[fix] fix damage AI event being called on dead actors.
[fix] Ensured that Melee Scans start/end correctly in dedicated servers.
[fix] Weapon Impact Cosmetics component name changed to "WeaponCosmetics".
```

## 2.11.27 - 19/10/2024
```
[new] Added the RefreshTargetWarp Animation Notify, to refresh the Combat Warp Target.
[new] Added Combo Task to manually set a Combo Count.
[new] Introduced a new, formal way to handle recurring damage, that's perceived by other systems.
[new] Status Effects view model.
[new] Magic Regeneration Gameplay Effect.
[new] Automatic AI perception for Damage Events.
[new] Ragdoll support via the Ragdoll Animation Notify.
[new] Added support for Linux.
[change] Added option to disable collision with warp targets in gameplay abilities.
[change] Combo Abilities can also have costs/cooldowns, regardless of the triggered abilities in the combo.
[change] Ensured that Marker Widgets are collapsed when not in use.
[change] Added an "Ignored Damage" filter to Hit Reactions.
[change] Added more logs to Melee Scans.
[change] Handled uninitialized states for the Widget Component.
[change] Added the correct melee/ranged damage for Attacks, instead of the "base" one.
[change] Added a directional offset angle for evades, to accommodate angled forward references.
[change] Added directional logic to death ability.
[change] Cast actors can obtain precise hits even for component collisions.
[change] Introduced new add/remove weapons to the default Weapon Manager.
[fix] Ensured that Opportunity Attacks will only dismiss a target if they were actually triggered.
[fix] fix calculation for left/right hit reactions.
[fix] fix the Magic Percent value in the Vitals viewmodel.
[fix] Reinforced tags as rollbacks in the Melee Scan.
[fix] fix ASC requirement from Cast Actors to apply damage.
```

## 2.7.16 - 24/09/2024
```
[new] Added a Weapon Animation Provider for abilities. This allows weapons to provide their own animations and reuse the same ability.
[new] Added the Weapon Trail notify option to the Melee Scan. This allows you to use trails with your weapons, in the same duration of the melee scan.
[change] Added the option to forward Gameplay Events directly to the Combo Manager, without needing the Input Action mappings.
[change] Added option to automatically rotate the player controller to face the target locked.
[change] Added a watch for the owner's death in the Weapon Manager.
[change] Added option to dissolve attached actors, such as weapons, along with the owner.
[change] Added blending of hit location and source location to Hit Reactions.
[change] Removed prioritization of current target in warp providers. That can be done with sorting in the Targeting Preset.
[change] Ensured that fallback abilities are only triggered after the opportunity attack ends, to avoid blocks.
[change] Created an Ability Task for contextual animations.
[change] Added an option for cast actors to add or remove casters from overlaps.
[change] Removed the combo data asset that was already unnecessary on v2.
[change] Removed the requirement from the Combo Gameplay Event to be triggered on both Server and Client. Local client is enough to advance it.
[fix] fix case for include directive in TargetProvider_TargetingSystem.
[fix] fix Niagara parameter name in NinjaCombatWeaponCosmeticsComponent.
[fix] Ensures that contextual animations always start with correct actor transforms, even when they are not automatically calculated.
[fix] Removed a temp log from NinjaCombatAttackSupport.
[fix] fix basic setup for the Damage Execution in damage effects.
[fix] fix the Gameplay Cue filter in the Cast Ability.
```

## 2.0.0 - 08/09/2024
```
[major] Reviewed setup and architecture, with the main goal of simplifying the system's usage.
[major] Rebuilt the Opportunity System.
[major] Rebuilt the UI module to fully leverage View Models.
[major] Updated the Combo System so it's easier to configure. The Data Asset does not exist anymore.
[major] Updated the Cast System so it's more flexible and supports Gameplay Ability Target Actors.
[new] Added directional Hit Reactions.
[new] Added a Weapon Cosmetics component that unifies how Gameplay Cues are implemented (particles, sounds, camera).
[new] Added a new (optional) Player Camera Manager that blends between cameras, used by the Opportunity System.
[change] Simplified the integration with Ninja Inventory.
[change] Updated the default Weapon Manager so it can be used as-is for simpler scenarios.
[change] Reviewed and expanded the Poise and Stagger functionality so it is easier to use.
[change] Added the option to override Gameplay Effects from Melee Scans and Projectile Launch requests.
[fix] fix projectiles not working when retrieved from the Actor Pool.
[fix] fix projectiles not transferring their original Hit Result to the Gameplay Cue.
[fix] fix combo State Trees not being cancelled along with the combo ability.
[fix] Removed FORCEINLINE macros that were breaking builds.
```

## 1.15.10 - 27/07/2024
```
[change] Added more checks for the Critical Damage Calculation, to avoid possible crashes.
[change] Added more verbose logs to damage and defense systems.
[change] Exposed damage details in the Damage Handler, for easier access in Blueprint implementations.
[fix] fix the calculation of Health, Stamina and Magic totals, ensuring that these are updated at the right time.
[fix] Reinforced components in the Damage Received fast array serializer, to avoid crashes in more complex actor hierarchies.
[deprecated] The Gameplay Effect used to initialize attributes have been removed.
```

## 1.15.4 - 17/07/2024
```
[new] Added more methods to the Default Weapon Manager, allowing adding and removing weapon actors.
[new] Added exclusive delegates to the Default Weapon Manager that will broadcast weapons that were added or removed.
[change] Added more logs to the Default Weapon Manager, to help troubleshooting the weapon initialization.
[change] Renamed the function LoadAttachedWeapons to FindAttachedWeapons to better convey its purpose.
[change] Added more logs to the Melee Scan Notify to help troubleshooting.
[fix] Fix the weapon check in the Melee Scan Notify, to ensure it's compatible with both C++ and Blueprint Weapons.
```

## 1.13.3 - 08/07/2024
```
[new] Added an integration with Ninja Factions, to allow members of the same faction to have friendly fire enabled or disabled.
[change] Improved the Actor Pool to provide more extension points to users needing to expand on it.
[fix] Ensure that the End Melee Scan event is not triggered if a Melee Start Scan was not triggered as well.
[fix] fix the edit condition for the weapon query in the Melee Scan.
```

## 1.12.9 - 27/06/2024
```
[new] Added an Animation Task interface and a base class for common Animation Montages. This simplifies creating tasks for other types of animations (i.e. Paper2D).
[change] Re-enabled all blueprint activations for combat abilities, with an option to disable them via properties.
[change] Renamed UNinjaCombatMontageAbility to UNinjaCombatAnimationAbility. A class redirect was added to avoid issues with Blueprints, but your C++ classes will have to be re-parented.
[change] Removed the requirement of a UAbilityTask_PlayMontageAndWait in the UNinjaCombatAnimationAbility.
[change] Marked the InitializeAnimationTask function from UNinjaCombatAnimationAbility as Blueprint Native.
[change] Marked the SetupAndPlayAnimation function from UNinjaCombatAnimationAbility as Blueprint Native.
[change] Reviewed the relationship between InitializeAnimationTask and SetupAndPlayAnimation to support other Animation Tasks.
[change] Ensured that the Ability System's Actor Info will collect the combatant's main Skeletal Mesh Component and Animation Instance.
[fix] fix the flag bStrafeWhileLockedOnTarget being ignored in the CombatMovementComponent.
[fix] fix the assigned Scan Class being ignored by the UAnimNotifyState_MeleeScan.
```

## 1.11.13 - 21/06/2024
```
[new] Added a configurable reusable Actor to indicate the Target Lock.
[new] A flexible Actor Pool, used for Projectiles and Cast actors.
[new] A Weapon Manager integrated with the Ninja Inventory/Equipment, usable if Ninja Inventory is detected in the project/engine.
[change] Improved the Actor destruction in the Damage Manager, allowing setting a lifespan instead of destroying actors immediately.
[change] Added velocity settings for strafing on the Movement Component.
[change] Created a schema for Combo Trees, validating the combo context and providing easier access to the Combo Manager (5.4 and above).
[deprecated] The Gameplay Effect used to initialize attributes will be removed in favor of the Datatable initialization.
```

## 1.8.12 - 30/04/2024
```
[new] Added a base Animation Instance class that contains the commonly expected movement values, plus bindings to the Combat System.
[new] Introduced the Model-View-View-Model (MVVM) pattern to Combat Widgets. You can learn more about this in the docs.
[new] Added a new Damage Handler for Camera Shakes.
[new] Added a new Damage Handler for Dissolving Materials.
[new] Added Opportunity Abilities (for attackers and victims). It can be used as a base for backstabs, stealth take-downs, ripostes, etc.
[new] Added the Parry Component and Backstab components for opportunity attacks.
[change] Enhanced the Block ability to simplify its usage.
[change] Enhanced the Evade ability to simplify its usage.
[change] Added lenient test functions for Actor Components that should implement Combat System interfaces.
[change] Improved multiple debug messages/ensure/assertions to hopefully facilitate troubleshooting.
[change] Added the Dead state tag as a blocker to any applicable Combat Ability and cancellation tags to the Death ability.
[change] Improved the Motion Warping System by allowing fine-tuning the target position via Scene Components.
[change] Upgraded to Unreal Engine 5.4.
[fix] Breaker hits won't have the "blocked" tag in their context anymore. This simplifies the setup of Hit Reactions.
[fix] fix the way rotations are set in Hit Reactions, so it can replicate properly.
[fix] fix a bug where the Death Ability could occasionally  raise a scope lock assertion.
[fix] Added the MinimalAPI class modifier that was missing in some interfaces.
[fix] fix the Damage Handler definition, to support generic Actor Components instead of the specific Damage Manager.
```

## 1.2.16 - 04/04/2024
```
[change] Improved flexibility to provide specific projectile classes to the Attack ability (weapon > owner > notify > ability).
[change] Modified access to many properties in the base projectile, they are now marked as BlueprintReadWrite.
[fix] fix the scenario where projectiles wouldn't launch correctly without a gameplay effect assigned to them.
```

## 1.2.13 - 01/04/2024
```
[new] Added Poise/Stagger mechanics. Hit Reactions can be "default" and "stagger" reactions.
[new] Added a Movement Manager Component. For now, it handles "walking while blocking" and "strafing while locked on target".
[change] The default Weapon Manager Component will load weapon actors attached to the owner.
[change] The default Weapon Manager Component allows subclasses to access the replicated weapon array.
[change] The Target Ability can be activated/deactivated from external events. Activation takes a target Actor in the payload.
[change] The Attack Ability provides functions that can be overridden to fine-tune Gameplay Effects and Levels.
[change] The Attack Ability automatically sets damage and poise to Gameplay Effects, if interfaces will provide them.
[change] Melee and Projectile interfaces can provide their respective Effect Levels.
[change] Melee and Projectile interfaces can provide damage and poise consumptions to Gameplay Effects, as "Set By Caller" magnitudes.
[change] Updated the Evade Ability to use the new Directional Evade Animation Provider.
[change] The Default Weapon Actor replicates its Gameplay Tags.
[change] Added a default setting to globally define the Motion Warping setting for Gameplay Abilities.
[change] Added a setting to determine the duration of Melee Scan debug information on screen.
[fix] The Damage Calculation will properly trigger conditional Gameplay Effects, if the damage output is greater than zero.
[fix] The Combo Manager is properly replicated to better support dedicated server scenarios.
```

## 1.0.0 - 15/03/2024
First release for Unreal Engine 5.3.

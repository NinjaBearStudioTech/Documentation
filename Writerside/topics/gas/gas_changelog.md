# Changelog
<primary-label ref="gas"/>

## 1.12.21 - 30/06/2026
```
[new] Delegate to the ASC informing when abilities are granted.
[new] Notify States for effects and loose gameplay tags.
[fix] Integrated mesh montages with main GAS flow.
[build] Added support for Unreal Engine 5.8.
```

## 1.11.19 - 17/04/2026
```
[new] Paper2D variations of the main character classes.
[change] Replication of Ability Montages and Sections for different meshes will use Fast Array Replication.
[change] Removed outdated code from the Ability Activation/Cancelation State Tree tasks.
[fix] Ensured that montages for different meshes replicate play rate and sections to simulated proxies.
[fix] Fixed order where the ASC and owning character is cached.
```

## 1.10.14 - 12/01/2026
```
[change] Incorporated a dedicated flow for animation montages in different meshes.
[change] Organized/standardized all function categories.
```

## 1.10.12 - 17/11/2025
```
[change] Additional support for Animation Montages played on Anim BPs disconnected from the main Mesh.
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 1.10.10 - 13/11/2025
```
[new] Support for Local and Server Attribute Sets.
[new] Support for Respawn Policy in Attribute Sets.
[new] Async task to wait for an Ability to end.
[change] Ability data assets from the owner and avatar are handled separately, as an aggregation.
[change] Added ability task helper functions to base ability.
[change] Adjusted addition/removal of loose replicated tags for 5.7 support.
```

## 1.7.7 - 04/07/2025
```
[new] State Tree task to Activate Gameplay Abilities.
[new] State Tree task to Cancel Gameplay Abilities.
[new] Dedicated function to fully reset the ASC. Can optionally be used when the pawn restarts.
[new] Added useful clamp macros for Attribute Sets in C++.
[new] New State Tree Evaluator for ability activation, which can be used to count the activation streak.
[new] New State Tree Consideration to provide utility scores based on Ability Cooldowns.
[change] Support for the "InitialCooldown" tag, used to start an ability immediately on cooldown.
[change] Handled runtime retarget possibilities in the "CurrentMontageStop" function, in the ASC.
[fix] Added a check to ensure that default abilities and effect handles are valid, before storing them.
[fix] Ensured that passive abilities are properly cancelled when changing an avatar.
[deprecation] Dropped support for Unreal Engine 5.4 to avoid version branching and ensure full compatibility with new State Tree utility-based features.
```

## 1.2.0 - 16/11/2024
```
[new] Support for Unreal Engine 5.5.
[new] Player Pawn class, compatible with the GAS Player State.
```

## 1.3.3 - 31/01/2025
```
[new] Support for Lazy ASC initialization for base Actors.
[change] Fixed warnings from Unreal Engine 5.5
[change] Added Mac to the list of allowed platforms.
[change] Added replicated Input Events to the ASC, to ensure Pressed/Released events are triggered.
[fix] Ensured that attribute set classes not set for a default entry won't result in a crash.
```

## 1.0.0 - 19/10/2024
First release for Unreal engine 5.3 and 5.4.

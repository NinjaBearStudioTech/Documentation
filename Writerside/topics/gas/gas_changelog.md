# Changelog
<primary-label ref="gas"/>

## 1.10.12 - 17/11/2025
```
[improvement] Additional support for Animation Montages played on Anim BPs disconnected from the main Mesh.
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 1.10.10 - 13/11/2025
```
[added] Support for Local and Server Attribute Sets.
[added] Support for Respawn Policy in Attribute Sets.
[added] Async task to wait for an Ability to end.
[improvement] Ability data assets from the owner and avatar are handled separately, as an aggregation.
[improvement] Added ability task helper functions to base ability.
[improvement] Adjusted addition/removal of loose replicated tags for 5.7 support.
```

## 1.7.7 - 04/07/2025
```
[added] State Tree task to Activate Gameplay Abilities.
[added] State Tree task to Cancel Gameplay Abilities.
[added] Dedicated function to fully reset the ASC. Can optionally be used when the pawn restarts.
[added] Added useful clamp macros for Attribute Sets in C++.
[added] New State Tree Evaluator for ability activation, which can be used to count the activation streak.
[added] New State Tree Consideration to provide utility scores based on Ability Cooldowns.
[improvement] Support for the "InitialCooldown" tag, used to start an ability immediately on cooldown.
[improvement] Handled runtime retarget possibilities in the "CurrentMontageStop" function, in the ASC.
[bugfix] Added a check to ensure that default abilities and effect handles are valid, before storing them.
[bugfix] Ensured that passive abilities are properly cancelled when changing an avatar.
[deprecation] Dropped support for Unreal Engine 5.4 to avoid version branching and ensure full compatibility with new State Tree utility-based features.
```

## 1.2.0 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
[added] Player Pawn class, compatible with the GAS Player State.
```

## 1.3.3 - 31/01/2025
```
[added] Support for Lazy ASC initialization for base Actors.
[improvement] Fixed warnings from Unreal Engine 5.5
[improvement] Added Mac to the list of allowed platforms.
[improvement] Added replicated Input Events to the ASC, to ensure Pressed/Released events are triggered.
[bugfix] Ensured that attribute set classes not set for a default entry won't result in a crash.
```

## 1.0.0 - 19/10/2024
First release for Unreal engine 5.3 and 5.4.

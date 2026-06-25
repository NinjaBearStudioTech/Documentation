# Changelog
<primary-label ref="factions"/>

## 2.3.14 - 12/01/2026
```
[change] Added features for plugin integrations.
[change] Organized/standardized all function categories.
```

## 2.3.12 - 17/11/2025
```
[change] Added features for Bot integration.
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 2.3.10 - 03/09/2025
```
[change] Exposed IsFriendly helper function, to check the alignment between two targets.
[change] Exposed IsNeutral helper function, to check the alignment between two targets.
[change] Exposed IsHostile helper function, to check the alignment between two targets.
```

## 2.3.7 - 04/07/2025
```
[new] Gameplay Effect Requirements for attitude checks.
[change] Modified the Attitude State Tree Condition, to be C++ based and check an actor, instead of a source attitude.
[fix] Fixed the typo on the source event tags.
```

## 2.2.5 - 31/01/2025
```
[new] Added support for Mac.
[change] Made all hard checks more permissive, with logging.
[fix] Ensured that the library won't crash when the faction member is null.
```

## 2.2.3 - 16/11/2024
```
[new] Support for Unreal Engine 5.5.
```

## 2.1.3 - 19/10/2024
```
[new] Added support for Linux.
[change] Added pure functions to the Faction Solver.
[change] Improved flexibility in the Function Library to find components from multiple types of actor.
```

## 2.1.1 - 15/09/2024
```
[new] Added Save and Load functionality.
```

## 2.0.1 - 02/06/2024
```
[fix] Fixed an issue in the "Reputation Range" check, commonly used when adding reputation tiers.
```

## 2.0.0 - 21/05/2024
```
[change] Modified the Event parameters in most calls, from an enum-based uint8 to a Gameplay Tag. This will break previous calls.
[change] Cleaned-up some internal code to bring it to newer coding standards adopted by other plugins.
[fix] Fixed an issue where new memberships could not be added programmatically.
[fix] Fixed an issue where delegates were not triggering.
```

## 1.3.3 - 05/05/2024
```
[change] Added support to Unreal Engine 5.4.
```

## 1.3.2 - 03/04/2024
```
[fix] Restored missing AI and Player controller classes.
[deprecation] Removed support to Unreal Engine 5.2. All plugins are maintained for current engine versions.
```

## 1.3.0 - 15/01/2024
```
[new] Added support to Behavior Trees. Service to expose faction data and a Decorator to check attitude.
[new] Added support to State Trees. Evaluator to expose faction data and a Condition to check attitude.
[new] Factions can be configured via Gameplay Features / Modular Gameplay.
[change] Organized C++ folders so they are homogeneous with other Ninja Bear plugins.
[fix] Fixed a bug that happened when adding factions from a client, in multiplayer, before replication kicks in.
[deprecation] Removed support for Unreal Engine 5.0 and 5.1.
```

## 1.0.0 - 01/06/2023
First release for Unreal Engine 5.0, 5.1 and 5.2.
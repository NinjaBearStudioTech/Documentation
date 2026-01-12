# Changelog
<primary-label ref="factions"/>

## 2.3.14 - 12/01/2026
```
[improvement] Added features for plugin integrations.
[improvement] Organized/standardized all function categories.
```

## 2.3.12 - 17/11/2025
```
[improvement] Added features for Bot integration.
[build] Added support to Unreal Engine 5.7, removed Unreal Engine 5.4 support
```

## 2.3.10 - 03/09/2025
```
[improvement] Exposed IsFriendly helper function, to check the alignment between two targets.
[improvement] Exposed IsNeutral helper function, to check the alignment between two targets.
[improvement] Exposed IsHostile helper function, to check the alignment between two targets.
```

## 2.3.7 - 04/07/2025
```
[added] Gameplay Effect Requirements for attitude checks.
[Improvement] Modified the Attitude State Tree Condition, to be C++ based and check an actor, instead of a source attitude.
[Bugfix] Fixed the typo on the source event tags.
```

## 2.2.5 - 31/01/2025
```
[added] Added support for Mac.
[improvement] Made all hard checks more permissive, with logging.
[bugfix] Ensured that the library won't crash when the faction member is null.
```

## 2.2.3 - 16/11/2024
```
[added] Support for Unreal Engine 5.5.
```

## 2.1.3 - 19/10/2024
```
[added] Added support for Linux.
[improvement] Added pure functions to the Faction Solver.
[improvement] Improved flexibility in the Function Library to find components from multiple types of actor.
```

## 2.1.1 - 15/09/2024
```
[added] Added Save and Load functionality.
```

## 2.0.1 - 02/06/2024
```
[bugfix] Fixed an issue in the "Reputation Range" check, commonly used when adding reputation tiers.
```

## 2.0.0 - 21/05/2024
```
[improvement] Modified the Event parameters in most calls, from an enum-based uint8 to a Gameplay Tag. This will break previous calls.
[improvement] Cleaned-up some internal code to bring it to newer coding standards adopted by other plugins.
[bugfix] Fixed an issue where new memberships could not be added programmatically.
[bugfix] Fixed an issue where delegates were not triggering.
```

## 1.3.3 - 05/05/2024
```
[improvement] Added support to Unreal Engine 5.4.
```

## 1.3.2 - 03/04/2024
```
[bugfix] Restored missing AI and Player controller classes.
[deprecation] Removed support to Unreal Engine 5.2. All plugins are maintained for current engine versions.
```

## 1.3.0 - 15/01/2024
```
[added] Added support to Behavior Trees. Service to expose faction data and a Decorator to check attitude.
[added] Added support to State Trees. Evaluator to expose faction data and a Condition to check attitude.
[added] Factions can be configured via Gameplay Features / Modular Gameplay.
[improvement] Organized C++ folders so they are homogeneous with other Ninja Bear plugins.
[bugfix] Fixed a bug that happened when adding factions from a client, in multiplayer, before replication kicks in.
[deprecation] Removed support for Unreal Engine 5.0 and 5.1.
```

## 1.0.0 - 01/06/2023
First release for Unreal Engine 5.0, 5.1 and 5.2.
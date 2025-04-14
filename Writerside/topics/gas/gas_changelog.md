# Changelog
<primary-label ref="gas"/>

## 1.6.5
<secondary-label ref="wip"/>
```
[added] State Tree task to Activate Gameplay Abilities.
[added] State Tree task to Cancel Gameplay Abilities.
[added] Dedicated function to fully reset the ASC. Can optionally be used when the pawn restarts.
[improvement] Support for the "InitialCooldown" tag, used to start an ability immediately on cooldown.
[improvement] Handled runtime retarget possibilities in the "CurrentMontageStop" function, in the ASC.
[bugfix] Added a check to ensure that default abilities and effect handles are valid, before storing them. 
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

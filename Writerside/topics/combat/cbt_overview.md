# Ninja Combat
<primary-label ref="combat"/>

![Ninja Combat](cbt_feature.png "Ninja Combat")

**Ninja Combat** is a Gameplay Ability System-based combat framework for Unreal Engine. It provides a reusable combat
domain for attacks, damage, defense, weapons, vitals, reactions, targeting, and combat-driven abilities.

The plugin is designed for projects that need a flexible combat foundation without locking the game into a specific genre 
or feel. It can support melee combat, ranged combat, action RPGs, shooters, adventure games, and other ability-driven 
combat systems.

This is an advanced plugin built on top of multiple Unreal Engine systems. Designers can configure many parts through 
assets and Blueprints, while deeper customization may require C++.

## What It Does

- Provides a reusable **combat framework** built on top of the Gameplay Ability System.
- Adds common combat concepts such as **damage**, **defense**, **blocking**, **poise**, **critical hits**, and **vitals**.
- Supports melee, ranged, projectile, firearm, and ability-driven combat flows.
- Provides tools for **targeting**, **motion warping**, **projectile pooling**, and **hit reactions**.
- Separates authoritative combat results from cosmetic presentation.
- Integrates with Inventory, Input, Interaction, and GAS-based gameplay.

## Main Features

- **Combat Domain**: Provides common combat building blocks such as combat actors, abilities, damage, defense, vitals, and reactions.
- **GAS Integration**: Uses Gameplay Abilities, Gameplay Effects, Attribute Sets, Gameplay Events, and Gameplay Cues as the foundation for combat behavior.
- **Damage System**: Supports advanced damage flows with critical hits, breaker hits, armor, blocking, poise, and defense calculations.
- **Damage Outcomes and Cosmetics**: Separates gameplay results from presentation, allowing authoritative effects and client-side feedback to evolve independently.
- **Damage and Defense Pipelines**: buildable pipelines to mitigate incoming damage and handle its outcomes.
- **Targeting Support**: Integrates with Unreal's Gameplay Targeting System for ability targeting and target acquisition.
- **Motion Warping Support**: Supports responsive combat movement and positioning through Motion Warping.
- **Projectile and Firearm Support**: Provides systems for projectile-based and hit-scan weapons, ammunition, shooting, and reloading.
- **Animation and Cues**: Supports combat feedback through animation, Gameplay Cues, hit reactions, widgets, and ViewModels.
- **Actor Pool**: Actors frequently used, such as projectiles and explosions can be managed by an Actor Pool to avoid spawning and garbage collection hitches.
- **Extension Points**: Exposes Blueprint and C++ hooks for adapting combat rules, damage handling, targeting, reactions, and equipment integration.

## Architecture Overview

Ninja Combat is organized around a dedicated combat domain layered on top of the Gameplay Ability System.

Combat behavior is usually driven by abilities. Abilities can acquire targets, commit costs, trigger animation, apply 
damage, spawn projectiles, or route events into other combat systems. Damage is processed through a structured flow that 
can calculate mitigation, apply gameplay effects, trigger outcomes, and present feedback through Gameplay Cues.

A key part of the architecture is the separation between **Damage Outcomes** and **Damage Cosmetics**. Outcomes represent 
authoritative gameplay results, such as applying damage, reacting to hits, notifying AI, or changing combat state. Cosmetics 
represent visual and audio presentation, such as hit flashes, floating numbers, camera feedback, or impact effects.

The plugin is designed to integrate with surrounding gameplay systems without owning them. Inventory can provide weapons 
and equipment, Input can activate combat abilities, Interaction can trigger combat-related abilities, and Ninja G.A.S. 
can provide the base Ability System setup.

## Integrations

- **[Ninja G.A.S.][8]** can provide the Ability System setup used by combat actors and abilities.
- **[Ninja Input][9]** can activate combat abilities, combos, and gameplay events.
- **[Ninja Inventory][10]** can provide weapons and equipment actors used by combat systems.
- **[Ninja Interaction](int_overview.md)** can trigger combat abilities from interaction flows.

[1]: https://www.unrealengine.com/marketplace/product/ninja-combat
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-targeting-system-in-unreal-engine
[4]: https://dev.epicgames.com/documentation/en-us/unreal-engine/motion-warping-in-unreal-engine
[5]: https://dev.epicgames.com/documentation/en-us/unreal-engine/state-tree-in-unreal-engine
[6]: https://dev.epicgames.com/documentation/en-us/unreal-engine/physics-driven-animation-in-unreal-engine
[7]: https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel
[8]: gas_overview.md
[9]: ipt_overview.md
[10]: inv_overview.md
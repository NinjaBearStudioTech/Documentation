# Ninja Combat
<primary-label ref="combat"/>

![Ninja Combat](cbt_feature.png "Ninja Combat")

The **Ninja Combat** plugin was designed as a layer built on top of Unreal Engine's **Gameplay Ability System**, introducing 
a **Combat Domain** that can be used in various types of projects, such as _weapons_, _damage_, _vitals_, and many others.

This system provides a robust foundation covering numerous **Abilities**, **Effects**, and **Attributes**, along with 
other common aspects of a Combat System, such as **Motion Warping**, **Projectile Pooling**, **Physical Reactions**, and more.

This is an **ample** and **advanced** system, built on top of many Unreal Engine capabilities. To take full advantage of 
it, it's recommended that you have some familiarity with these base systems. **For advanced usage, you will need to use C++**.

## Main Features

- **Extensive Combat System Domain**: Includes a wide range of features for building comprehensive combat systems.
- **Integration with the [Gameplay Ability System][2]**: Seamless integration with Unreal Engine's powerful ability system.
- **Integration with the [Gameplay Targeting System][3]**: Supports precise targeting mechanisms.
- **Integration with the [Motion Warping System][4]**: Allows for dynamic and responsive character movement.
- **Data-driven and Event-based**: Designer-friendly Combat Combos can be crafted using [State Machines][5].
- **Advanced Damage and Defense Mechanics**: Includes features such as **Critical Hits**, **Breaker Hits**, **Armor**, **Blocking**, **Poise**, and [Procedural Hit Reactions][6].
- **Core Attributes**: Provides essential attributes like **Health**, **Magic**, **Stamina**, **Critical Damage**, and **Defense**.
- **Basic Widgets**: Includes common elements such as Health Bars and Damage Applied, integrated with **[UMG ViewModels][7]**.
- **Configurable and Extensible**: Highly customizable in both Blueprints and C++.
- **Clean Code and Thorough Documentation**: Well-documented codebase and comprehensive documentation site.

## Design Pillars

- **Separation of Concerns**: The Combat domain is self-contained and affect other domains such as "Locomotion", "Inventory", "Interaction", etc.
- **Flexibility**: The Combat System was built with _adventure_, _action RPGs_ and _souls-like_ in mind, but it's flexible enough for other types of games.
- **Extensibility**: Provides many extension points in C++ and Blueprints. Interface-oriented design for components.
- **Connectivity**: Parts of the system that must integrate with other domains are designed to be integration-friendly.
- **Engine Parity**: As much as possible, reuses features already available in the engine, without "reinventing the wheel".

## Integrations

- The Gameplay Ability System can be configured using **[Ninja GAS][8]**.
- Activate abilities and combos with input handlers from **[Ninja Input][9]**.
- Allows the creation of weapons as Equipment Actors with **[Ninja Inventory][10]**.

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

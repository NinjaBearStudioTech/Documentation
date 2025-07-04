# Ninja Inventory
<primary-label ref="inventory"/>

![Ninja Inventory](inv_feature.png "Ninja Inventory")

> **Major Upgrade!**
> 
> Inventory 2.0 is the next version for our Inventory System. Many parts were rebuilt to include optimizations, simplifications 
> quality-of-life, based on community feedback.
> 
> The new version is planned for late July/early August 2025 and will also refresh the integration with Ninja Combat.
> The documentation is already been updated to support the new features.
{style="note"}

The **Ninja Inventory** plugin was inspired by concepts introduced by Epic's project "Lyra", such as definitions, instances, 
and fragments. These concepts are quite powerful for an inventory system, as they promote defining items through _aggregation_ 
instead of the classic _inheritance_ approach.

For a generic and reusable framework like this, such concepts are fundamental, as they truly allow the Inventory System 
to remain agnostic of a game's design and requirements. Furthermore, in line with a recurring theme for all plugins from 
Ninja Bear Studio, this framework was designed with a strong focus on _separation of concerns_.

This is an **ample** and **advanced** system, built on top of many Unreal Engine capabilities. To take full advantage of
it, it's recommended that you have some familiarity with these base systems. **For advanced usage, you will need to use C++**.

## Main Features

- **Extensive Inventory and Equipment Domain**: Provides a comprehensive domain for managing inventory and equipment.
- **Gameplay Ability System Integration**: Uses Gameplay Abilities, Effects, and Attribute Sets for enhanced functionality.
- **Asset Manager Integration**: Loads assets when needed and unloads them when not, optimizing performance.
- **Aggregation and Inversion of Control**: Items and equipment pieces are declared via _aggregation_ and _inversion of control_, promoting flexibility and modularity.
- **UI Module**: Built using the [Common UI][4] and the [UMG Viewmodel][5] frameworks, for a robust and responsive user interface.
- **Flexibility and Extensibility**: Designed to support various types of projects.
- **Quality and Support**: Features clean, well-documented code, a thorough documentation site and a Discord support channel.

## Design Pillars

- **Separation of Concerns**: The Inventory domain is self-contained and affect other domains such as "Locomotion", "Combat", "Interaction", etc.
- **Flexibility**: The Inventory System is flexible enough to be used in multiple projects, from simple weapon wheels to RPG games.
- **Extensibility**: Multiple extension points are available so the Inventory System can be adapted to many situations.
- **Designer Friendly**: You can configure and operate the entire Inventory System using Data Assets and Blueprints. Deeper customization might require C++.
- **Engine Parity**: As much as possible, reuses features already available in the engine, without "reinventing the wheel".

## Integrations

- The Gameplay Ability System can be configured using **[Ninja GAS][6]**.
- The Equipment Manager can be used as the Weapon Manager for **[Ninja Combat][7]**.
- Pickups can be created as Interaction Actors from **[Ninja Interaction][8]**. 
- Inventory Abilities can be triggered using Input Handlers from **[Ninja Input][9].** 

[1]: https://www.unrealengine.com/marketplace/product/ninja-inventory
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine
[4]: https://dev.epicgames.com/documentation/en-us/unreal-engine/common-ui-quickstart-guide-for-unreal-engine
[5]: https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel
[6]: gas_overview.md
[7]: cbt_overview.md
[8]: int_overview.md
[9]: ipt_overview.md
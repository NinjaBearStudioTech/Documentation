# Ninja Inventory
<primary-label ref="inventory"/>

![Ninja Inventory](inv_feature.png "Ninja Inventory")

**Ninja Inventory** is a modular inventory and equipment framework for Unreal Engine. It is built around item definitions, 
runtime instances, and fragments, allowing items to be assembled through composition instead of rigid inheritance.

The plugin is designed to stay agnostic of a specific game genre or inventory style, making it suitable for anything from 
simple equipment slots and weapon wheels to deeper RPG-style inventory systems.

## What It Does

- Provides reusable systems for **items**, **inventory**, **equipment**, **loot** and **vendors**.
- Defines items through **definitions**, **instances**, and **fragments**.
- Supports flexible inventory and equipment behavior without forcing a specific game design.
- Integrates with the **Gameplay Ability System** for abilities, effects, and attributes.
- Provides UI support through **Common UI** and **UMG ViewModels**.
- Connects cleanly with Combat, Interaction, Input, and GAS-based gameplay.

## Main Features

- **Item Definitions and Fragments**: Build item behavior through reusable fragments instead of deep inheritance trees.
- **Runtime Item Instances**: Track item state, quantities, ownership, and runtime data independently of item definitions.
- **Inventory Management**: Provides systems for storing, moving, stacking, and managing items.
- **Equipment Management**: Supports equipping items, spawning equipment actors, and connecting equipment to gameplay systems.
- **Loot, Vendors and Pickups**: Supports other domains related to Inventory, with dedicated components, handlers and so on.
- **GAS Integration**: Uses Gameplay Abilities, Gameplay Effects, and Attribute Sets for ability-driven inventory and equipment behavior.
- **Asset Manager Integration**: Supports asset loading patterns that help keep item data scalable.
- **UI Support**: Provides ViewModel-based UI foundations for inventory screens and item presentation.
- **Extension Points**: Exposes Blueprint and C++ hooks for adapting the framework to project-specific rules.

## Architecture Overview

Ninja Inventory is organized around a clear separation between item data, runtime item state, inventory storage, equipment 
behavior, and UI presentation.

Item Definitions describe what an item is. Fragments add reusable pieces of behavior or data, such as equipment rules, 
gameplay ability grants, stack behavior, pricing, or other project-specific properties. Runtime Item Instances represent 
actual items owned by actors and can hold state that changes during play.

Inventory and equipment systems build on top of these concepts. Inventory components manage item ownership and storage, 
while equipment systems handle equipped items, equipment actors, and integrations with other gameplay systems such as 
Combat or GAS.

This composition-based approach allows designers to create many item types from reusable parts, while programmers can 
extend the system with custom fragments, specialized handlers, item logic, and UI behavior when needed.

## Integrations

- **[Ninja G.A.S.][6]** can provide the Ability System setup used by inventory abilities and equipment effects.
- **[Ninja Combat][7]** can use equipped items as weapons or combat-relevant equipment.
- **[Ninja Interaction][8]** can create pickups, containers, or interactable inventory actors.
- **[Ninja Input][9]** can trigger inventory abilities or equipment actions through input handlers.

[1]: https://www.unrealengine.com/marketplace/product/ninja-inventory
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine
[4]: https://dev.epicgames.com/documentation/en-us/unreal-engine/common-ui-quickstart-guide-for-unreal-engine
[5]: https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel
[6]: gas_overview.md
[7]: cbt_overview.md
[8]: int_overview.md
[9]: ipt_overview.md
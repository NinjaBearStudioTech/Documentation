# Ninja Input
<primary-label ref="input"/>

![Ninja Input](ipt_feature.png "Ninja Input")

The **Ninja Input** plugin is designed to separate the code used to handle **Player Input**, which is captured by Unreal 
Engine's **[Enhanced Input System][1]**.

For each Input Action, you can use any of the many **Input Handlers** provided by the system or easily create your own 
in **Blueprints** or **C++**. The system offers a variety of handlers out-of-the-box, including full integration with the **[Gameplay Ability System][2]**.

## Main Features

- **Enhanced Input System**: Fully integrated with Unreal Engine's official Input System.
- **Input Manager**: The Input Manager Component handles all the boilerplate functionality necessary to configure inputs.
- **Handler Collection**: Offers numerous Input Handlers out-of-the-box and a clean API design to create new ones as needed, either in C++ or Blueprints.
- **Trigger Abilities**: Fully integrated with the Gameplay Ability System, allowing it to activate and cancel Abilities and send Gameplay Events.
- **Animation-Based Input Buffer**: Includes an animation-based Input Buffer to ensure that player input is not dropped, enhancing game responsiveness.
- **Integrated with the Editor**: Enables the creation of relevant assets with proper contextual menus and the configuration of important aspects in the Project Settings page.

## Design Pillars

- **Separation of Concerns**: Separates Input Handling code from Character code.
- **Fast Iteration**: Faster iterations and prototyping with many common input handling code already provided.
- **GAS Integration**: Simple way to trigger abilities from user input.

## Integrations

- The Gameplay Ability System can be configured using **[Ninja GAS][3]**.
- It can trigger abilities and send events to the Combo Manager from **[Ninja Combat][4]**.
- It can trigger abilities from **[Ninja Inventory][5]**.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine
[2]: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
[3]: gas_overview.md
[4]: cbt_overview.md
[5]: inv_overview.md

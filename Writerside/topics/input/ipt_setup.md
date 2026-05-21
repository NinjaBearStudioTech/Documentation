# Setting Up Ninja Input
<primary-label ref="input"/>

This page summarizes the setup required for **Ninja Input** after the plugin has been installed and enabled.

For the general installation process, see the [**Installing Plugins**](installing_plugins.md) guide.

## Prerequisites

| Requirement    | Notes                                                                                                        |
|----------------|--------------------------------------------------------------------------------------------------------------|
| Enhanced Input | Ninja Input builds on Unreal Engine's Enhanced Input system.                                                 |
| Ninja G.A.S.   | Optional. Required only if you want to trigger Gameplay Abilities or Gameplay Events through input handlers. |

## Setup Checklist

| Step                                 | Required          | Guide                                       |
|--------------------------------------|-------------------|---------------------------------------------|
| Install and enable the plugin        | Yes               | [Installing Plugins](installing_plugins.md) |
| Add C++ module dependencies          | Yes, if using C++ | [Installing Plugins](installing_plugins.md) |
| Remove existing input handling logic | Recommended       | See below                                   |

## Remove Existing Input Handling
If your project already has input logic configured directly in your Character, Pawn, Player Controller, or Project Settings,
it is recommended to remove that setup before configuring Ninja Input.

<procedure title="Remove the original input handling logic" collapsible="true" default-state="expanded">
    <step>Open your <b>Project Settings</b>, navigate to <b>Enhanced Input</b> and make sure that there are no <b>Default Mapping Contexts</b>.</step>
    <step>Navigate to your <b>Player Character Blueprint</b>, open it and go to the <b>Event Graph</b>.</step>
    <step>Remove all input-related nodes, including the ones connected to <b>Begin Play</b> setting up Input Mapping Contexts.</step>
</procedure>
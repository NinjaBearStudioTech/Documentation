# Setting Up Ninja G.A.S.
<primary-label ref="gas"/>

This page summarizes the setup required for **Ninja G.A.S.** after the plugin has been installed and enabled.

For the general installation process, see the [**Installing Plugins**](installing_plugins.md) guide.

## Prerequisites

| Requirement             | Notes                                                                                                                                                            |
|-------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Gameplay Ability System | Your project should be using Unreal Engine's Gameplay Ability System.                                                                                            |
| Attribute Sets          | Ninja G.A.S. does not provide Attribute Sets. You must create your own or use Attribute Sets provided by other plugins, such as Ninja Combat or Ninja Inventory. |

## Setup Checklist

| Step                          | Required          | Guide                                       |
|-------------------------------|-------------------|---------------------------------------------|
| Install and enable the plugin | Yes               | [Installing Plugins](installing_plugins.md) |
| Add C++ module dependencies   | Yes, if using C++ | [Installing Plugins](installing_plugins.md) |
| Configure Asset Manager       | Yes               | [Asset Manager](asset_manager.md)           |

## Ability System Initialization
Projects using the Gameplay Ability System must initialize the **Global Data**. Ninja G.A.S. automatically initializes 
this data when its **Subsystem** initializes. **No additional steps are necessary**.
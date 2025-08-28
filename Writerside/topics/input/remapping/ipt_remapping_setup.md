# Key Remapping Setup
<primary-label ref="input"/>
<secondary-label ref="experimental"/>

Ninja Input provides all the necessary classes to support **Key Remapping**, a common feature in games that
allow players to customize controls to their preferences.

Setting up your project to support remapping is straightforward and involves three steps:

1. **Enable input remapping** in your project.
2. Configure your Input Actions or Mapping Contexts for **mappable inputs**.
3. (Optional) Configure Common UI to **provide platform icons** if you are using them with the provided ViewModels.

## Enabling Input Remapping
To enable Input Remapping with Ninja Input, you first need to ensure the correct **Settings Classes** are
configured in your project. You can use the classes provided by the framework **or your own subclasses**.

<procedure title="Enabling Input Remapping" collapsible="true" default-state="expanded">
    <step>In the engine, open the <b>Project Settings</b> window.</step>
    <step>Navigate to <b>Engine</b> &rarr; <b>Enhanced Input</b>, and expand the <b>User Settings</b> category.</step>
    <step>Check the <b>Enable User Settings</b> option.</step>
    <step>Set <code>NinjaInputUserSettings</code> (or a subclass) as the <b>User Settings Class</b>.</step>
    <step>Set <code>NinjaInputPlayerMappableKeyProfile</code> (or a subclass) as the <b>Default Player Mappable Key Profile</b>.</step>
    <img src="ipt_remapping_settings.png" alt="Enable Input User Settings" width="600"/>
</procedure>

## Mappable Inputs
You can configure mappable inputs either in your **Input Actions** or your **Input Mapping Context**.  
In this guide, we'll use the latter, so all settings remain centralized in a single place.

The goal here is to define **which actions can be remapped** and how they should be represented in the **user interface**.  
Repeat the steps below for every input you want to support remapping.

<procedure title="Configuring Mappable Inputs" collapsible="true" default-state="expanded">
    <step>Open the <b>Input Mapping Context</b> that contains the remappable Input Actions.</step>
    <step>Set the <b>Setting Behavior</b> to <code>Override Settings</code>.</step>
    <step>Set the <b>Player Mappable Key Settings</b> to <code>NinjaInputPlayerMappableKeySettings</code> (or a subclass).</step>
    <step>Assign a unique <b>Name</b> for this key. It must be distinct across all Input Actions and their keys.</step>
    <step>Set the <b>Input Filter</b> to specify the type of input (e.g., keyboard, mouse, gamepad). This helps the UI categorize keys correctly.</step>
    <step>Define the <b>Display Name</b> and <b>Display Category</b>. These values are shown in the UI and support localization.</step>
    <step>Optionally, define a <b>Tooltip</b> to be displayed in the UI. This also supports localization.</step>
    <img src="ipt_remapping_mappable_key_settings.png" alt="Configure Mappable Key Settings" width="600"/>
</procedure>

## Common UI Configuration

> **Optional Configuration**  
> 
> If you don’t plan to use automated brushes for key representation (for example, if you only want to display the key's 
> name), you can skip this step.  
{style="note"}

Most of the ViewModel functionality for Input Remapping works with default UMG.

However, the **Icon Brush** property in the **Key Mapping Entry** ViewModel requires the Common UI key setup in order to display the correct icon for the current key.

To configure this, follow the [official Common UI documentation][1] to create your **controller data binding**, making sure to set up items for **platform-specific UI elements**.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/common-ui-quickstart-guide-for-unreal-engine


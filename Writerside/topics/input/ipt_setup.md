# Setup
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>Install the Ninja Input plugin using the Epic Games Launcher.</li>
        <li>Open your project and enable the plugin: <code>Edit</code> &rightarrow; <code>Plugins</code>, search for <i>input</i>, and tick the checkbox for <b>Ninja Input</b>. Restart the engine.</li>
        <li>Add <code>NinjaInputManagerComponent</code> to your <b>Player Controller</b>.</li>
    </ul>
</tldr>

This page will walk you through the **steps** necessary to enable the **Ninja Input** plugin.

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type
_input_ and the **Ninja Input** plugin should appear. Tick the checkbox and restart the engine.

## C++ Libraries

If you plan to work with C++ and use classes from the Input System, ensure you add the following modules to your
`Build.cs` file:

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#" src="ipt_build.cs"/>
    </tab>
</tabs>

## Input Manager

The **[](ipt_input_management.md#input-manager)** must be added to the **Player Controller** or **Character**.

It's usually better to add the Input Manager to the **Player Controller**, but for prototypes or smaller projects, you
can also add it to the **Player Character**. The advantages for the Player Controller are:

- Lesser requirements in the Player Character, allowing a leaner **character hierarchy**.
- Support for **different pawns**, providing their own Input Setups when possessed.

<tabs group="sample">
    <tab title="Blueprint">
        <img src="ipt_add_component.png" alt="Input Manager Component Setup" border-effect="line"/>
    </tab>
    <tab title="C++">
        <code-block lang="c++" src="ipt_setup_manager_component.h"/>
        <br/>
        <code-block lang="c++" src="ipt_setup_manager_component.cpp"/>
    </tab>
</tabs>

## Creating and Assigning Input Setups

The plugin is ready and the next step is to configure your Input Handlers and Setup. 

You can go straight to that by following this **[guide](p01g01_configure_inputs.md)**, or you can continue to 
the next session to learn more about the system. 
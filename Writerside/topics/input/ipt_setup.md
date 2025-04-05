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
        <code-block lang="c#" src="ipt_setup_build.cs"/>
    </tab>
</tabs>

## Input Manager

The **[](ipt_input_management.md#input-manager)** must be added to the **Player Controller** or **Character**.

It's usually better to add the Input Manager to the **Player Controller**, but for prototypes or smaller projects, you
can also add it to the **Player Character**. The advantages for the Player Controller are:

- Lesser requirements in the Player Character, allowing a leaner **character hierarchy**.
- Support for **different pawns**, providing their own Input Setups when possessed.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="ipt_add_component.png" alt="Input Manager Component Setup" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="c++">
        <code-block lang="c++" src="ipt_setup_manager_component.h"/>
        <br/>
        <code-block lang="c++" src="ipt_setup_manager_component.cpp"/>
    </tab>
</tabs>

## Creating and Assigning Input Setups

<procedure title="Remove the original input handling logic" collapsible="true">
    <step>Open your <b>Project Settings</b>, navigate to <b>Enhanced Input</b> and make sure that there are no <b>Default Mapping Contexts</b>.</step>    
    <step>Navigate to your <b>Character Blueprint</b>, open it and go to the <b>Event Graph</b>.</step>
    <step>Remove all input-related nodes, including the ones connected to <b>Begin Play</b>.</step>
</procedure>

<procedure title="Configure the Input Setup" collapsible="true">
    <step>In the <b>Content Browser</b>, navigate to your <b>Input</b> folder.</step>
    <step>Right click to open the <b>Context Menu</b>, navigate to the <b>Input</b> category and select <b>Ninja Input Setup</b>. Name it in a way that it correlates with your <b>Input Mapping Context</b>, for example: <code>IMC_Gameplay</code> &rightarrow; <code>IS_Gameplay</code>.</step>
    <step>Open the new <b>Input Setup</b> and add your <b>Input Mapping Context</b>.</step>
    <step>Add three new entries to the <b>Input Handlers</b> list, selecting: <code>Character: Move</code>, <code>Character: Look</code> and <code>Character: Jump</code>.</step>
    <step>
        <p>For each one of these entries, expand their properties and add the appropriate <b>Input Action</b>.</p>
        <p>By default, they will have Input Actions starting with <code>IA_NI</code>, which are the ones provided by Ninja Input. Make sure to <b>replace them</b> with your project-related counterparts.</p>
        <img src="ipt_setup_input_setup_data.png" alt="Configure Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <tip>
        <p><b>Input Validation</b></p>
        <p>If you get a <b>Validation Error</b> while saving your <b>Input Setup</b>, it means that there are Input Actions in your <b>Input Mapping Context</b> that are <b>missing</b> in the list of <b>Input Handlers</b>.</p>
        <p>Check the <b>Message Log Window</b> and you will find which Input Actions are missing an Input Handler. And you can always separate your inputs into <b>multiple setups</b>.</p>
    </tip>
</procedure>

<procedure title="Assign the Input Setup to the Input Manager" collapsible="true">
    <step>Navigate to the <b>Player Controller</b>, where the <b>Input Manager</b> was added.</step>
    <step>Click the <b>Input Manager Component</b> to open its <b>Default Values</b>.</step>
    <step>
        <p>Add the newly-created <b>Input Setup</b> to the list of <b>Input Setups</b>.</p>
        <img src="ipt_setup_data_assignment.png" alt="Add the Input Setup" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>
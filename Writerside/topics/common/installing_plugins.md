# Installing Plugins

This page will walk you through the steps necessary to add and enable Ninja Bear Studio plugins.

## Prerequisites And Additional Steps
All plugins are designed to work standalone and will enable any required plugin dependencies through their `.uplugin` files.
For embedded Unreal Engine plugins listed as dependencies, such as the Gameplay Ability System, that is enough.

However, each plugin might have their own prerequisites or list additional steps necessary during its setup. To learn more 
about their specific prerequisites and steps, please check each plugin's dedicated **Setup Page**.

## Installing from the Launcher
To get started, install the plugin to your engine using the <b>Epic Games Launcher</b>.

<procedure title="Install via the Epic Launcher" collapsible="true" default-state="expanded">
    <step>Open the <b>Epic Games Launcher</b> and locate the <b>desired plugin</b> in your <b>library</b>.</step>
    <step>
        <p>Click <b>Install to Engine</b> and select the engine version to install, from the list of compatible versions.</p>
        <tip>Plugins installed via the Epic Launcher are added to your Engine directory and are available to <b>all projects</b> using that engine version.</tip>
    </step>
    <step>Once installed, open your project, navigate to <b>Edit</b> &rarr; <b>Plugins</b> and find the plugin in the list of installed plugins. You can also search for it, by name, using the Search Bar.</step>
    <step>Enable the plugin and restart the engine.</step>
</procedure>

## Working with the Source Code
<secondary-label ref="advanced"/>
If you plan to work with source code, you can copy the plugin to your project or clone it from <b>GitHub</b>, if you 
have access to the repository.

<tip>
    <p>If you decide to copy the plugin from the engine into your project, make sure to uninstall the version in the engine. <b>Make sure only one copy is active!</b></p>
    <p>Unreal may load the Engine version of the plugin over the one in your project, leading to <b>version mismatches</b> or <b>undefined behavior</b>.</p>
</tip>

<procedure title="Enable C++ in your Project" collapsible="true" default-state="expanded">
    <step>Make sure to perform all <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-your-development-environment-for-cplusplus-in-unreal-engine">necessary steps</a> to <b>enable C++</b> in your environment and project.</step>
    <step>To work with the source code, you will need an editor installed, such as <b>Visual Studio</b> or <b>Rider</b>. Make sure to install your editor of choice.</step>
    <step>If your project was originally Blueprint-only, create at least one C++ class, such as a base Character or Game Mode, via <b>Tools</b> &rarr; <b>New C++ Class</b>.</step>
</procedure>

<procedure title="Install from GitHub" collapsible="true" default-state="expanded">
    <step>Ensure that you have access to the plugin repository on <b>GitHub</b>.</step>
    <step>In your project root, create a <code>Plugins</code> folder if you don't have one. If you're using multiple Ninja Bear Studio plugins, we recommend organizing them under a <code>NinjaBearStudio</code> folder.</step>
    <step><b>Clone</b> the plugin repository into your desired Plugins folder.</step>
    <step>Right-click the <code>.uproject</code> file and select <b>Generate Visual Studio project files</b> (or your IDE equivalent).</step>
    <step>Launch the project. The plugin should now be available in your project's Plugins list.</step>
</procedure>

<procedure title="Add C++ Module Dependencies" collapsible="true" default-state="expanded">
    <step>Close your Unreal Engine project if it is currently open.</step>
    <step>
        <p>In your IDE of choice, open the <code>Build.cs</code> file, named after your project (e.g., <code>MyGame.Build.cs</code> in the <code>Source/MyGame</code> folder), and add the following modules, based on plugins you are using.</p>
        <tabs group="module_dependencies">
            <tab title="Bot" group-key="bot">
                <code-block lang="c#" src="bot_setup_build.cs"/>
            </tab>
            <tab title="Combat" group-key="cbt">
                <code-block lang="c#" src="cbt_setup_build.cs"/>
            </tab>
            <tab title="Factions" group-key="fct">
                <code-block lang="c#" src="fct_setup_build.cs"/>
            </tab>
            <tab title="GAS" group-key="gas">
                <code-block lang="c#" src="gas_setup_build.cs"/>
            </tab>
            <tab title="Interaction" group-key="int">
                <code-block lang="c#" src="int_setup_build.cs"/>
            </tab>
            <tab title="Inventory" group-key="inv">
                <code-block lang="c#" src="inv_setup_build.cs"/>
            </tab>
            <tab title="Input" group-key="ipt">
                <code-block lang="c#" src="ipt_setup_build.cs"/>
            </tab>
        </tabs>
        <warning><b>Do not remove or replace any existing dependencies</b>. Add the ones in the list above, and <b>watch out for duplicates</b>.</warning>
    </step>
    <step><b>Recompile the project</b>. If this is the first time doing so, it might take a while.</step>
</procedure>

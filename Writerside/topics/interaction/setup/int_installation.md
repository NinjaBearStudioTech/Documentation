# Installation
<primary-label ref="interaction"/>

<tldr>
    <p><b>Summary: Installing Ninja Interaction</b></p>
    <br/>
    <ul>
        <li>Install <b>Ninja Interaction</b> using the <b>Epic Launcher</b> and enable it in your project.</li>
        <li>Optionally, install the source code from <b>GitHub</b> and <b>enable C++</b> in the project.</li>
        <li>If using C++, then make sure to add all <b>module dependencies</b> to the <code>Build.cs</code> file.</li>
    </ul>
</tldr>

This page will walk you through the **pre-requisites** and **steps** necessary to enable the **Ninja Interaction** plugin.

## Pre-Requisites
Before enabling Ninja Interaction, make sure to have the following pre-requisites addressed:
1. A working setup for the **Gameplay Ability System Component**. If you are using **[](gas_overview.md)**, then make sure to configure it first.
2. A working setup for the **Enhanced Input**. If you are using **[](ipt_overview.md)**, then make sure to configure it first.

## Installing the Plugin
To get started, install the plugin to your engine using the **Epic Games Launcher**.

<procedure title="Installing via the Epic Launcher" collapsible="true" default-state="expanded">
    <step>Open the <b>Epic Games Launcher</b> and locate the <b>Ninja Interaction</b> code plugin.</step>
    <step>
        <p>Click <b>Install to Engine</b> and select the engine version to install, from the list of compatible versions.</p>
        <tip>Plugins installed via the Epic Launcher are added to your Engine directory and are available to all projects using that engine version.</tip>
    </step>
    <step>Once installed, create or open your project, navigate to <b>Edit</b> &rarr; <b>Plugins</b> and find Ninja Interaction on the list. You can search for it in the Search Bar too.</step>
    <step>Enable the plugin and restart the engine.</step>
</procedure>

## Working with the Source Code
<secondary-label ref="advanced"/>
If you plan to work with the source code, you can copy the plugin to your local engine or install it from GitHub. 

<procedure title="Enable C++ in your Project" collapsible="true" default-state="expanded">
    <step>Make sure to perform all <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-your-development-environment-for-cplusplus-in-unreal-engine">necessary steps</a> to <b>enable C++</b> in your environment and project.</step>
    <step>To work with the source code, you will need an editor installed, such as <b>Visual Studio</b> or <b>Rider</b>. Make sure to install your editor of choice.</step>
    <step>If your project was originally Blueprint-only, create at least one C++ class, such as a base Character or Game Mode, via <b>Tools</b> &rarr; <b>New C++ Class</b>.</step>
</procedure>

<procedure title="GitHub Repository" collapsible="true" default-state="expanded">
    <step>Ensure that you have access to the Ninja Interaction repository on <b>GitHub</b>.</step>
    <step>In your project, create a <code>Plugins</code> folder if you don't have one. If you're using multiple Ninja Bear Studio plugins, we recommend organizing them under a <code>NinjaBearStudio</code> folder.</step>
    <step><b>Clone</b> the Ninja Interaction repository into your desired Plugins Folder.</step>
    <step>Right-click the <code>.uproject</code> file and select <b>Generate Visual Studio project files</b> (or your IDE equivalent).</step>
    <step>Launch the project. The plugin should now be available in your project's Plugins list.</step>
</procedure>

<procedure title="Enable C++ Modules" collapsible="true" default-state="expanded">
    <step>Close your Unreal Engine project if it is currently open.</step>
    <step>
        <p>In your IDE of choice, open the <code>Build.cs</code> file, named after your project (e.g., <code>MyGame.Build.cs</code> in the <code>Source/MyGame</code> folder), and <b>add</b> the following contents.</p>
        <code-block lang="c#" src="int_setup_build.cs"/>
        <warning><b>Do not remove or replace any existing dependencies</b>. Add the ones in the list above, and <b>watch out for duplicates</b>.</warning>
    </step>
    <step>
        <p>Remove the version installed in the engine, if there is one.</p>
        <tip>Unreal may load the Engine version of the plugin over the one in your project, leading to <b>version mismatches</b> or <b>undefined behavior</b>. <b>Make sure only one copy is active</b>.</tip>
    </step>
    <step><b>Recompile the project</b>. If this is the first time doing that, it might take a while.</step>
</procedure>

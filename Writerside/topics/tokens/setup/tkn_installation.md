# Installation
<primary-label ref="tokens"/>

This page will walk you through any **pre-requisites** and steps necessary to enable **Ninja Tokens**.

## Pre-Requisites

Ninja Tokens is compatible with **Behavior Trees** or **State Trees**. Make sure that the AI Support plugin is enabled in 
your project and, if you are using State Trees, also make sure that the State Trees plugin is enabled as well.

## Installing the Plugin

To get started, install the plugin to a supported engine version using to your engine Epic Games Launcher, and then 
enable it in your project.

> Plugins installed via the Launcher are added to your engine and are available to all projects using the same engine version.
{style="note"}

<procedure title="Installing via the Epic Launcher" collapsible="true" default-state="expanded">
    <step>Open the <b>Epic Games Launcher</b> and locate the <b>Ninja Tokens</b> plugin.</step>
    <step>Click <b>Install to Engine</b> and select the desired version from the version list.</step>
    <step>Once installed, create or open your project, and navigate to <b>Edit</b> and <b>Plugins</b>.</step>
    <step>Find <b>Ninja Tokens</b> from the list and enable it.</step>
    <step>When prompted, <b>restart the engine</b> to fully activate the plugin.</step>
</procedure>

## Working with Sources
<secondary-label ref="advanced"/>

If you plan to work with the source code, you can copy the plugin to your local engine or install it from GitHub.

<procedure title="Enable C++ in your Project" collapsible="true" default-state="expanded">
    <step>Make sure to perform all <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-your-development-environment-for-cplusplus-in-unreal-engine">necessary steps</a> to <b>enable C++</b> in your environment and project.</step>
    <step>To work with the source code, you will need an editor installed, such as <b>Visual Studio</b> or <b>Rider</b>. Make sure to install your editor of choice.</step>
    <step>If your project was originally Blueprint-only, create at least one C++ class, such as a base Character or Game Mode, via <b>Tools</b> &rarr; <b>New C++ Class</b>.</step>
</procedure>

<procedure title="GitHub Repository" collapsible="true" default-state="expanded">
    <step>Ensure that you have access to the Ninja Tokens repository on <b>GitHub</b>.</step>
    <step>In your project, create a <code>Plugins</code> folder if you don't have one. If you're using multiple Ninja Bear Studio plugins, we recommend organizing them under a <code>NinjaBearStudio</code> folder.</step>
    <step><b>Clone</b> the Ninja Interaction repository into your desired Plugins Folder.</step>
    <step>Right-click the <code>.uproject</code> file and select <b>Generate Visual Studio project files</b> (or your IDE equivalent).</step>
    <step>Launch the project. The plugin should now be available in your project's Plugins list.</step>
</procedure>

<procedure title="Enable C++ Modules" collapsible="true" default-state="expanded">
    <step>Close your Unreal Engine project if it is currently open.</step>
    <step>
        <p>In your IDE of choice, open the <code>Build.cs</code> file, named after your project (e.g., <code>MyGame.Build.cs</code> in the <code>Source/MyGame</code> folder), and <b>add</b> the following contents.</p>
        <code-block lang="c#" src="tkn_setup_build.cs"/>
        <warning><b>Do not remove or replace any existing dependencies</b>. Add the ones in the list above, and <b>watch out for duplicates</b>.</warning>
    </step>
    <step>
        <p>Remove the version installed in the engine, if there is one.</p>
        <tip>Unreal may load the Engine version of the plugin over the one in your project, leading to <b>version mismatches</b> or <b>undefined behavior</b>. <b>Make sure only one copy is active</b>.</tip>
    </step>
    <step><b>Recompile the project</b>. If this is the first time doing that, it might take a while.</step>
</procedure>

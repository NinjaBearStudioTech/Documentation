# Install and Enable Plugins

Choose the Launcher install for a plugin from Fab, including for a Blueprint-only project. Use the project-source install if you have the plugin source and want to build it with your game.

## Installing from the Launcher

<procedure title="Install for the engine version your project uses">
    <step><p>Add the plugin to your Fab library using the Epic account you use in the Launcher. You can find the plugins on the <a href="https://www.fab.com/sellers/Ninja%20Bear%20Studio">Ninja Bear Studio Fab page</a>.</p></step>
    <step><p>Close the project. In the Epic Games Launcher, open <b>Unreal Engine → Library</b> and find the plugin in <b>Fab Library</b>. Refresh the library if you just acquired it.</p></step>
    <step><p>Choose <b>Install to Engine</b>, select your project's engine version, and wait for installation to finish. The version picker shows compatible installed engines. An engine installation makes the plugin available to projects using that version.</p></step>
</procedure>

## Working with the Source Code

<procedure title="Build a project-local copy">
    <step><p>Set up your platform's Unreal C++ toolchain. For a Blueprint-only project that you want to build from source, use <b>Tools → New C++ Class</b> to create a game module. See <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-your-development-environment-for-cplusplus-in-unreal-engine">Epic's C++ environment setup</a>.</p></step>
    <step><p>Close the editor. Copy the complete plugin folder, or clone its repository if you have access, into your project's <code>Plugins</code> folder. For example, a local Ninja Input install contains <code>Plugins/NinjaInput/NinjaInput.uplugin</code>. Use one copy of the plugin for this project so you can tell which version you are building.</p></step>
    <step><p>Generate project files for the <code>.uproject</code>, then build the project's <b>Development Editor</b> target for your platform. Open the project after the build succeeds.</p></step>
</procedure>

## Enable and Check the Plugin

Open **Edit → Plugins**, search for the plugin, and tick its checkbox. Allow Unreal to enable any required engine plugins it lists. Save and restart the editor. Reopen **Edit → Plugins** and check that the plugin is enabled in this project. If it is missing, check the engine version used to open the project or the location of the project-local `.uplugin`. [Epic's plugin installation guide](https://dev.epicgames.com/documentation/unreal-engine/working-with-plugins-in-unreal-engine)

Once the plugin is enabled, [choose its Setup and First Steps guide](getting_started.md#choose-your-plugin).

If a walkthrough uses assets supplied by the plugin, open the Content Browser's **Settings** and enable **Show Plugin Content**. For an engine-installed plugin, also enable **Show Engine Content** if its folder is hidden.

## C++ Module Dependencies

When your game's C++ code uses a plugin class, add the module that provides it to your game module's `Build.cs`. This example adds the module for a Ninja Input Manager used in a private implementation file.

```c#
PrivateDependencyModuleNames.Add("NinjaInput");
```

Use `PublicDependencyModuleNames` for a dependency exposed by your module's public headers. Keep your existing dependencies and rebuild the Editor target after adding the module.

## AI-Assisted Development

As a limited exception to the Fab NoAI designation, licensed customers may submit portions of this product's source code 
to private generative AI tools solely for analysis, debugging, modification, or integration within their own licensed projects. 

This permission does not include training, fine-tuning, dataset inclusion, persistent AI knowledge bases, redistribution, 
public exposure, or development of competing products.

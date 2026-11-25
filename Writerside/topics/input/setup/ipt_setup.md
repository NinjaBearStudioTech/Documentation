# Set Up Ninja Input
<primary-label ref="input"/>

## Prerequisites

Start with an Unreal project using **Enhanced Input**. The Third Person template supplies a character, movement actions, and keyboard and gamepad mappings for the first walkthrough.

## Setup Checklist

| Step                                                                                | When you need it                           | Where to go                                              |
|-------------------------------------------------------------------------------------|--------------------------------------------|----------------------------------------------------------|
| Enable Ninja Input and Enhanced Input.                                              | Every project                              | [Install plugins](installing_plugins.md)                 |
| Check that the project uses Enhanced Player Input and the Enhanced Input Component. | When migrating an older project            | Project Settings → Engine → Input, under Default Classes |
| Add module dependencies for plugin classes you use.                                 | C++ projects that reference those classes  | [Install plugins](installing_plugins.md)                 |
| Enable Enhanced Input User Settings.                                                | Key remapping or saved control preferences | [Build a key remapping menu](ipt_remapping_ui.md)        |

## Migrate Existing Controls

Keep the template actions and mapping context. Look for the code or Blueprint that adds the context, often in the Player Controller or Character at Begin Play. Also check **Project Settings → Enhanced Input → Default Mapping Contexts**. When your new setup takes ownership, remove the old registration for that context and disconnect the old callbacks for the migrated actions. Leave other controls in place.

You can build movement and camera controls with the plugin alone. Ability handlers need a working Unreal Gameplay Ability System on the pawn. Ninja G.A.S. is one way to supply it.

[Move a template character](ipt_first_steps.md).

# Gameplay Debugger
<primary-label ref="factions"/>

The **Gameplay Debugger** is an Unreal Engine functionality that helps with the development of AI Agents, providing a 
visual reference to common AI Topics such as the Navigation Mesh, Behavior Tree and Environment Queries.

The Faction System provides its own category for it, allowing you to evaluate Memberships from an agent.

## Configuring the Gameplay Debugger

The Debugger Module is active by default, but you need to assign a key to show the overlay. You can do so in your Project 
Settings panel.

<img src="fct_debugger_setup.png" alt="Enabling the Gameplay Debugger" thumbnail="true" border-effect="line"/>

1. Select the **Gameplay Debugger** category.
2. Select the key used to toggle the debugger Overlay on and off. Optionally set different keys to toggle categories, which can be useful in case you don't have a keypad.
3. The display order for each category can be modified. The Faction System doesn't have a strict order (-1), so you can select the "Override" flag and re-arrange this, or any other category.

## Using the Gameplay Debugger

While running your project in the Editor, press the selected key to display the debugger overlay, while aiming at the 
general direction of the AI Agent you want to connect to the debugger.

<img src="fct_debugger_overlay.png" alt="Faction Category in the Gameplay Debugger" thumbnail="true" border-effect="line"/>

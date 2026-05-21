# Gameplay Debugger
<primary-label ref="inventory"/>

<tldr>
<p><b>Summary: Gameplay Debugger</b></p>
    <br/>
    <ul>
        <li>Provides a live view of the inventory system using Unreal’s <b>Gameplay Debugger</b>.</li>
        <li>Shows <b>initialization state</b>, <b>containers</b>, <b>item details</b>, and <b>equipment states</b>.</li>
        <li>Includes <b>hotkeys</b> to toggle container visibility and enable detailed item views.</li>
        <li>Useful for <b>backend validation</b> before the UI is implemented.</li>
    </ul>
</tldr>

The Inventory Debugger is a category available in the **Gameplay Debugger**. You can check your debugger settings—and 
most importantly, the **key** used to open the debugger—under **Project Settings** → **Engine** → **Gameplay Debugger**.

While you're there, ensure that your **Activation Key** is properly set, along with your **Category Keys**. If multiple 
systems are contributing categories to the Gameplay Debugger, you may need to ensure the **Inventory Category** is 
properly listed under the **Add-Ons** section.

Once activated, the Inventory Debugger will appear in the **Default View**.

![Default Debugger View](inv_gameplay_debugger.png "Default Debugger View")

### General Inventory State

The first section displays important information about the overall **inventory state**.

| Inventory Property   | Description                                                                                                       |
|----------------------|-------------------------------------------------------------------------------------------------------------------|
| Initialization State | Shows the current initialization state. Useful for debugging failures during the inventory startup process.       |
| Owner and Avatar     | Displays the owner and avatar associated with the inventory.                                                      |
| Data Source          | Indicates whether the inventory was initialized using default items or loaded from a save game.                   |
| Wealth               | Current wealth value assigned to the owner, as defined by the relevant Gameplay Attribute.                        |
| Encumbrance          | Displays current item weight, max supported weight, and encumbrance, based on the appropriate Gameplay Attribute. |

### Container and Item Breakdown

After the general state, the debugger shows all **containers** and their **current items**. For each item, the following\
details are displayed:

- **Name**
- **Position** in the container
- **Stack Info** (current amount, max stack size, storage limit)
- **Equipment State**, if applicable

Additional notes:

1. Container titles indicate their type (**Default**, **Equipment**, or **Loot**) and their **storage capacity**.
2. You can toggle container visibility using the following shortcuts:
    - `Shift+1` – Show/Hide Default Containers
    - `Shift+2` – Show/Hide Equipment Containers
    - `Shift+3` – Show/Hide Loot Containers
    - `Shift+4` – Show/Hide Empty Containers
3. Press `Shift+5` to switch to the **Detailed View**, which displays extended item information from various fragments.

> **Backend Validation**
>
> The <b>Inventory Gameplay Debugger</b> is a valuable tool for inspecting and validating your setup before implementing the user interface.
> Use it to verify your <b>initialization state</b>, <b>container configuration</b>, <b>item placement</b>, and other backend behaviors.
{style="note"}

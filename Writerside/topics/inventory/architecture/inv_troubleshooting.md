# Troubleshooting
<primary-label ref="inventory"/>

<tldr>
    <ul>
        <li>The Inventory System provides <b>Gameplay Debugger</b> category with <b>basic</b> and <b>advanced</b> perspectives.</li>
        <li>The <b>Inventory Debugger</b> is very useful to evaluate the inventory's state, without the need of creating any user interface.</li>
        <li>Enable the <b>LogNinjaInventory</b> and <b>LogNinjaInventoryEquipment</b> log categories to track multiple internal flows.</li>
    </ul>
</tldr>

The Inventory System has a dedicated **Gameplay Debugger Category** to display its internal **state**. It can also print 
log messages in the dedicated `LogNinjaInventory` category, allowing you to track its internal logic flows.

## Inventory Debugger

The Inventory Debugger is a category available in the **Gameplay Debugger**. You can check your debugger settings, and 
most importantly the **key** used to open the debugger, in **Project Settings** > **Engine** > **Gameplay Debugger**.

While there, ensure that your **Activation Key** is properly set, along with your **Category Keys**. If you have many 
systems providing categories to the Gameplay Debugger, you might need to ensure that the **Inventory Category** is 
properly assigned in the list of **Categories**, in the **Add Ons** section.

The Inventory Debugger is a great tool to help you evaluate your inventory state, especially when your user interface is 
not fully implemented or simply won't show certain details about the internal items.

### Default View

Once activated, the Inventory Debugger will be shown in the **Default View**.

![Default Debugger View](inv_debugger_default.png "Default Debugger View")

It will show you all the **containers** and their current **items**. For each item, it will display the item's **name**, 
**position in the container**, **stack** (current amount, stack size, storage limit), and the **equipment state**.

There are a few important things to note here:

1. Container titles will inform their type (default, equipment, and loot) and the slot count (current and maximum slots).
2. You can show or hide the main container types, or empty containers, by pressing `shift+1`, `shift+2`, `shift+3`, and `shift+4`.
3. You can switch to the **Detailed View** by pressing `shift+5`.

### Detailed View

By pressing `shift+5`, you can toggle between the **default** and **detailed** views of the Inventory Debugger.

![Detailed Debugger View](inv_debugger_detailed.png "Detailed Debugger View")

In the **detailed view**, you can see more information about each item: **position**, **stack**, **level**, **quality**, 
**durability**, **weight**, and **equipment details**.

## Log Messages

The Inventory and Equipment systems can provide a lot of information in your console log, which can be useful to track 
issues or confirm certain flows.

The output will be categorized by _severity_. Use the following table to decide what severity level you want to enable 
when configuring your logs:

| Severity    | Usage                                                                                                                                           |
|-------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| Fatal       | Fatal conditions in the system that will result in an exception/crash.                                                                          |
| Warning     | Conditions that should not happen but are being handled by the code. They might expose incorrect setups or assumptions and should be addressed. |
| Log         | General messages used to confirm certain important logic flows and significant changes.                                                         |
| Verbose     | Useful debug messages to confirm internal data and states.                                                                                      |
| VeryVerbose | Very specific messages mostly relevant when developing or extending functionalities. Can be overwhelming!                                       |

To enable relevant log categories for certain log severities, add the following lines to your `DefaultEngine.ini` file, located in your project's `Config` folder.

> Make sure that you are not duplicating the `Core.Log` section!
{style="warning"}

```ini
[Core.Log]
LogNinjaInventory=Verbose
```

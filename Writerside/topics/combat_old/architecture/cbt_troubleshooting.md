# Troubleshooting
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>You can enable <b>messages and visual cues</b> in each <b>Combat Ability</b>.</li>
        <li>Multiple <b>Logs</b> are printed under the <code>LogNinjaCombat</code> category.</li>
    </ul>
</tldr>

The Combat System has a can provide debug information from each **Combat Ability**. It can also print log messages in the
dedicated `LogNinjaCombat` category, allowing you to track its internal logic flows.

## Ability Debug

Combat Ability have a property that allows you to enable debugging. Abilities will provide different types of details,
relevant to the task they are performing.

For example, the Attack Ability will display certain screen messages and draw shapes in the world that represent the 
melee scan and enemies being hit.

## Log Messages

The Combat System can provide a lot of information in your console log, which can be useful to track issues or confirm
certain flows.

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

``` ini
[Core.Log]
LogNinjaCombat=Verbose
```

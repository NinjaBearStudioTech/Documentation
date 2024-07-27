# Debugger and Logs
<primary-label ref="inventory"/>

## Inventory Debugger

## Ability System

### Gameplay Debugger

### Debug Console Command

## Log Messages

The Inventory and Equipment systems can provide a lot of information in your console log, which can be useful to track
issues or confirm certain flows.

The output will be categorized by _severity_, so when configuring your logs, considering the following table to decide
what severity level you want to enable.

| Severity    | Usage                                                                                                                                    |
|-------------|------------------------------------------------------------------------------------------------------------------------------------------|
| Fatal       | Fatal conditions in the Inventory System, that will result in an exception/crash.                                                        |
| Warning     | Conditions that should not happen but are being treated by the code. They might expose wrong setup or assumptions and should be handled. |
| Log         | General messages used to confirm certain important logic flows and important changes.                                                    |
| Verbose     | Useful debug messages to confirm internal data and states.                                                                               |
| VeryVerbose | Very specific messages mostly relevant when developing or extending functionalities. Can be overwhelming!                                |

> Since the Inventory System heavily uses Gameplay Effects, it might be useful to also log their messages too!

To enable relevant log categories, for certain log severities, please add the following lines to your `DefaultEngine.ini`,
located in your project's `Config` folder. Make sure that you are not duplicating the `Core.Log` section, as it may 
already exist!

```ini
[Core.Log]
LogGameplayEffects=Log
LogNinjaInventory=Verbose
```


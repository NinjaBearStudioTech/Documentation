# Troubleshooting
<primary-label ref="input"/>

<tldr>
    <ul>
        <li>You can enable <b>on-screen messages</b> in the <b>Project Settings</b>, under <b>Ninja Input</b>.</li>
        <li>Multiple <b>Logs</b> are printed under the <code>LogNinjaInputManagerComponent</code> and <code>LogNinjaInputHandler</code> categories.</li>
    </ul>
</tldr>

The Input System provides **on-screen messages** and **log output** to assist with any troubleshooting.

## On-Screen Messages

You can enable the **on-screen messages** in the Project Settings panel. You can enable **Show Screen Debug Messages**
and also configure their **duration**.

> **Ninja Input Settings**
> 
> You can find the Input System configuration under: `Edit` > `Project Settings` > `Ninja Input`.

![Ninja Input Settings](ipt_settings.png "Ninja Input Settings")

## Log Messages

The Input System can provide a lot of information in your console log, which can be useful to track issues or confirm 
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
LogNinjaInputManagerComponent=VeryVerbose
LogNinjaInputHandler=VeryVerbose
```

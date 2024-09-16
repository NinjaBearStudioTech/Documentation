# Debugger and Logs
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

## Output Log Messages

Both the **Input Manager Component** and **Handlers** will output messages to the log. By default, you will see the
`Log`, `Warning` and `Error` levels, but if you need additional information, then you can enable `Verbose` or even
`VeryVerbose` levels.

To enable these levels, edit the `DefaultEngine.ini` file, and add the following lines.

``` ini
[Core.Log]
LogNinjaInputManagerComponent=VeryVerbose
LogNinjaInputHandler=VeryVerbose
```

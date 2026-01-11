# Settings
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: Global Settings</b></p>
    <br/>
    <ul>
        <li>Certain global parameters are exposed in the Developer Settings page.</li>
        <li>You can use a Team Provider to connect Ninja Bot and Ninja Factions.</li>
    </ul>
</tldr>

Ninja Bot exposes a small set of global settings through Unreal Engine’s Developer Settings system. These settings affect 
the behavior of all bots using the framework and are intended for high-level configuration rather than per-bot customization.

<img src="bot_setup_settings.png" alt="Bot Settings" thumbnail="true" width="800" border-effect="line"/>

| Setting                 | Description                                                                                                                                                                                          |
|-------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Disable Logic**       | Globally disables Ninja Bot AI logic. When enabled, perception evaluation and awareness updates are skipped. This is useful when testing other gameplay systems without AI interference.             |
| **Team Provider Class** | Defines the class responsible for resolving team affiliation for actors. This is used by Ninja Bot to determine friend or foe relationships and serves as the integration point with Ninja Factions. |

> Now that the initial setup is complete, you can either continue reading about Ninja Bot, or check the quick start
> guide for your [**first ten minutes**](bot_guide_01_first_ten_minutes.md) with the plugin.
{style="note"}
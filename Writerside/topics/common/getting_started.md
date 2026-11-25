# Getting Started

Choose the feature you want to try first. If you're starting a new Unreal project, the Third Person template gives you a playable character and a test level for most walkthroughs. An existing project works too.

[Install and enable your plugin](installing_plugins.md). Then use its **Setup** page for project settings and its **First Steps** guide for the first result you can check in play.

## Choose Your Plugin

| Plugin            | What to configure                                                                                          | First Steps                                                           |
|-------------------|------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------|
| Ninja Bot         | [Register bot setups](bot_setup.md) and give the guard navigable ground.                                   | [Make a guard roam, detect the player, and chase](bot_first_steps.md) |
| Ninja Combat      | [Configure the ability system and collision](cbt_setup.md) for a character that can deal and receive hits. | [Set up a combatant](cbt_first_steps.md)                              |
| Ninja Factions    | [Register your factions and choose the attitude rules](fct_setup.md).                                      | [Give two actors opposing factions](fct_first_steps.md)               |
| Ninja G.A.S.      | [Register ability bundles](gas_setup.md) for starting abilities and attributes.                            | [Give a character an ability system](gas_first_steps.md)              |
| Ninja Input       | [Check Enhanced Input and the template's existing bindings](ipt_setup.md).                                 | [Move a template character](ipt_first_steps.md)                       |
| Ninja Interaction | [Set up the pawn's ability system and interaction collision](int_setup.md).                                | [Use a nearby switch](int_first_steps.md)                             |
| Ninja Inventory   | [Register item and container definitions](inv_setup.md).                                                   | [Give a character a backpack with three bandages](inv_first_steps.md) |

## Using Several Plugins

For a project using the full set, one workable setup order is G.A.S., Input, Inventory, Combat, Interaction, Factions, then Bot. Follow the parts your game uses. For example, to build a guard that recognizes rivals, start with Factions and Bot. Once both First Steps examples work, [connect the guard's perception to faction attitudes](integration_bot_factions.md). Explore other combinations in the [integration matrix](integrations.md#integration-matrix).

## Support

Open **Edit → Plugins** and find your plugin's card for Ninja Bear Studio's support email and Discord link.

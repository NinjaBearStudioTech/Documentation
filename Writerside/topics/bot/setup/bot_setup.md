# Set Up Ninja Bot
<primary-label ref="bot"/>

## Prerequisites

Start with an Unreal project and a level where you can move a player character. For the first walkthrough, the bot needs navigable ground and a clear line of sight to the player.

## Setup Checklist

| Step                                                                                                 | When you need it                                                | Where to go                                      |
|------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------|--------------------------------------------------|
| Install and enable Ninja Bot.                                                                        | Every project                                                   | [Install plugins](installing_plugins.md)         |
| Add module dependencies for the Ninja Bot classes you use.                                           | C++ projects that reference those classes                       | [Work with plugin source](installing_plugins.md) |
| Register the primary asset type **BotSetupData** and the folder where you will save your bot setups. | Every project                                                   | [Asset Manager](asset_manager.md)                |
| Check project-wide AI settings.                                                                      | When changing perception defaults or diagnosing an inactive bot | See below.                                       |

## Choose Which Pawns Can Be Seen

Unreal registers pawns as sight sources by default. You can keep this for the first walkthrough. If you want to choose exactly which pawns participate, add the following to your project's `DefaultEngine.ini`.

```ini
[/Script/AIModule.AISense_Sight]
bAutoRegisterAllPawnsAsSources=false

[/Script/AIModule.AISense_Hearing]
bAutoRegisterAllPawnsAsSources=false
```

With automatic registration off, add an **AI Perception Stimuli Source** component to the player pawn, enable automatic registration on the component, and add **AI Sight** to its registered senses.

<img src="bot_setup_stimuli_source.png" alt="Sight registered on the player's stimuli source" width="780" border-effect="line"/>

Under **Edit → Project Settings → AI System**, **Forget Stale Actors** lets Unreal clear perception records after their stimuli expire. The bot's Awareness Profile controls how quickly its suspicion fades during play.

## Before You Press Play

In **Edit → Project Settings → Ninja Bot**, leave **Disable Logic** off. You can keep the default **Team Provider Class** while learning how sight works. Continue to [First Steps](bot_first_steps.md).

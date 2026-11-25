# Ninja Bot
<primary-label ref="bot"/>

![Ninja Bot](bot_feature.png "Ninja Bot")

Use Ninja Bot to build characters that notice what happens around them and decide how to respond. A guard might walk a route, grow suspicious when the player crosses a doorway, then give chase.

## What It Does

A bot can see or hear several actors at once. You decide which signals deserve its attention, how long it remembers someone, and what it does with that information.

## Main Features

- Give guards, civilians, and other characters different senses and behaviors through reusable **Bot Setup** assets.
- Build decisions in a **Behavior Tree** or **State Tree**. Both can read the selected target and the bot's awareness of it.
- Set walking and running speeds, link patrol points, or give a particular stop its own activity.
- Let [threat from damage or healing](bot_threat_manager.md) draw a guard's attention to a new target.
- Show players how close a guard is to spotting them with an awareness indicator.

## How a Bot Works

The character supplies its **Bot Setup** to its AI Controller. The controller applies the setup and starts the chosen tree. When sight picks up a player, the tree gets a target it can move toward. You can make the guard chase immediately or wait until its awareness reaches a threshold.

Start with [Set Up Ninja Bot](bot_setup.md), then [build a bot that roams and chases](bot_first_steps.md).

## Integrations

Use [Bot and Factions](integration_bot_factions.md) to decide who counts as an enemy. Use [Bot and Combat](integration_bot_combat.md) to lock on when the bot selects a target and release it when the target is lost.

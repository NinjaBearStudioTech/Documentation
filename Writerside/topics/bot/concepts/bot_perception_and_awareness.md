# Perception and Awareness
<primary-label ref="bot"/>

A guard glimpses the player through a doorway. **Perception** tells the tree whom the guard is paying attention to. **Awareness** lets a brief glimpse carry less weight than a long look. The tree decides whether the guard should investigate, chase, or keep walking.

## What the Guard Can Sense

The **Sense Profile** defines the senses the bot uses. Start with Sight. Set its radius, field of view and accepted team attitudes, then select a **Dominant Sense**. Add Hearing or Damage when your game produces those events.

When several actors compete for attention, each sense contributes to a score. Increase its **Base Weight** to give it more influence. If the guard keeps switching between similar targets, increase **Min Switch Cooldown** or the score advantage a challenger needs to take over.

## How Suspicion Builds

Without an Awareness Profile, an active sense makes the bot Aware immediately. An **Awareness Profile** sets how quickly awareness rises and falls for each actor. A continuous sense such as sight can build awareness over time. An instant contribution gives it a jump, useful for a sudden event. Thresholds mark **Suspicious**, **Alerted**, and **Aware**. Below the first threshold the bot is **Unaware**.

While the guard is Aware, the tree can read **Last Known Location**. If it should search there after the target clears, copy that location to a separate search destination while it is still available. With an Awareness Profile, suspicion can linger while the stored awareness falls. To make a guard wait before chasing, check **Awareness Level** in its tree. A condition that checks only **Sensed Actor** can start a chase on the first glimpse.

## When Threat Should Change the Target

If damage, healing, or a taunt should draw the guard's attention, use [Threat and Target Priority](bot_threat_manager.md). It explains how a guard tracks threat from several actors and sends the leader to perception.

## Let the Player React

For a single overhead indicator, read that guard's [Awareness Feedback](bot_user_interface.md). For a player-wide response, add the **Awareness Target** component to the player pawn and bind [On Aggregated Awareness Changed](bot_awareness_target.md#notifications). For example, use that event to play a warning when the highest awareness level among nearby observers rises.

[Tune detection and awareness in play](bot_guide_05_awareness_setup.md).

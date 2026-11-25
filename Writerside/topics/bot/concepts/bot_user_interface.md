# Awareness Feedback
<primary-label ref="bot"/>

An indicator above a guard answers a question for the player: “Has this guard spotted me?” Each guard needs its own reading. Two guards looking in different directions can show different levels.

## What the Indicator Shows

The **Bot Awareness ViewModel** reads the guard's selected target and the pawn of the player who owns the widget. While that pawn is selected, the widget can show its awareness level and progress. When the guard selects another target or clears its target, the reading returns to Unaware.

For a detection meter, use **Get Progress to Aware State**. The bar fills when the guard reaches its Aware threshold, even if the threshold is below 1. Use **Awareness Progress** if you want the underlying value across the full range.

## Decide When to Show It

The **Bot Awareness Tracker Widget** can hide when Unaware, show a bar as suspicion grows, and change its label or color when the guard becomes Alerted or Aware. Set these choices on the widget Blueprint. To drive a single warning for several guards, use the player's Awareness Target component instead.

[Build an overhead awareness indicator](bot_guide_06_awareness_ui.md).

## Customize the Tracker's Response

In a Widget Blueprint derived from **Bot Awareness Tracker Widget**, override **Handle Awareness Changed** (`HandleAwarenessChanged`) to react to a change of level. It gives you both the old and new levels. For example, play a pulse animation when a guard goes from Alerted to Aware. Call the parent implementation to keep the built-in visibility, label, and color updates.

To customize just one part of the display, override **Update Awareness Visibility** (`UpdateAwarenessVisibility`), **Update Awareness Text** (`UpdateAwarenessText`), or **Update Progress Bar Color** (`UpdateProgressBarColor`). For an event on the player that accounts for several guards, see [Awareness Target notifications](bot_awareness_target.md#notifications).

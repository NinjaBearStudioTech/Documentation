# Awareness Targets
<primary-label ref="bot"/>

Add an **Awareness Target** component to your player pawn when you want the player to react to being spotted. If two guards are watching, the component reports the highest awareness score and the highest awareness level across those guards. Your player Blueprint can listen in one place.

## Notifications

The component notifies you when the highest score or level changes. Each notification gives you the score, the level, and the perception component responsible for the highest score. When the last observer is removed, a previous positive reading returns to zero and the source can be empty.

| Where you want to react                | Hook                                  | How to use it                                                                                                                                                                                                   |
|----------------------------------------|---------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| In the player Blueprint                | `OnAggregatedAwarenessChanged`        | Select the Awareness Target component and add **On Aggregated Awareness Changed**, or bind a custom event to it. Use the score to drive a detection meter.                                                      |
| In your own Awareness Target component | `HandleAggregatedAwarenessChanged`    | Override **Handle Aggregated Awareness Changed** in a derived Blueprint, or override `HandleAggregatedAwarenessChanged_Implementation` in C++. Use this when several characters should share the same response. |
| In another C++ object                  | `Native_OnAggregatedAwarenessChanged` | Subscribe to the native multicast delegate with a member function or a lambda. It supplies the same score, level, and source.                                                                                   |

For a warning sound, store the previous level in the listener and play the sound when the level first changes to **Aware**. The score can keep changing while the level stays Aware, so playing a sound on every notification would repeat it.

## Awareness User Interface

Use the component's score for a single HUD meter that reflects the most alert observer. For an indicator above each guard, use the **Bot Awareness ViewModel** and **Bot Awareness Tracker Widget**. See [Awareness Feedback](bot_user_interface.md) and [Display an Awareness Indicator](bot_guide_06_awareness_ui.md).

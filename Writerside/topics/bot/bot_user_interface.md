# User Interface
<primary-label ref="bot"/>

<tldr>
    <p><b>Summary: User Interface</b></p>
    <br/>
    <ul>
        <li>Ninja Bot provides a base UI layer to expose awareness and perception state.</li>
        <li>UI support is presentation-only and fully optional.</li>
        <li>Visual styling and behavior remain project-defined.</li>
    </ul>
</tldr>

Ninja Bot includes a small set of **UI-facing base objects** intended to expose **perception and awareness** state to 
players. The most common use case is displaying an AI agent's awareness as a **progress indicator** with a corresponding 
state, such as unaware, suspicious, or alerted.

## Awareness ViewModel

The **Bot Awareness ViewModel** exposes perception and awareness data in a UI-friendly, presentation-only form. It is 
designed to be consumed by widgets without embedding AI logic or visual decisions into the AI systems themselves.

The ViewModel can be initialized by the **Bot Resolver** and requires its Bot Owner to be set via `SetComponentIOwner`. 
The Bot Owner is typically the host actor of a **Widget Component** responsible for spawning the Awareness Widget bound 
to this ViewModel.

> More information on the initialization process, including ViewModel bindings, can be found in the Awareness Implementation Guide.

| Field / Function            | Description                                                                                                                                                                                           |
|-----------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Is Selected Target**      | Indicates whether the current player is the selected perception target for the bot hosting this widget.                                                                                               |
| **Awareness Progress**      | Normalized awareness value in the range `[0, 1]`. Intended for use in progress indicators.                                                                                                            |
| **Awareness Level**         | Discrete awareness level the bot currently has toward the player owning the UI.                                                                                                                       |
| **Is Awareness Relevant**   | Returns true when awareness information is meaningful to display. This requires the player to be the selected target and awareness progress to be greater than zero.                                  |
| **Awareness Alpha**         | Returns an alpha value suitable for bars or materials. Awareness progress is returned only when the player is the selected target.                                                                    |
| **Progress to Aware State** | Returns progress toward the *Aware* threshold instead of full awareness. Useful when the aware threshold is less than 1 and a progress bar should represent confirmation rather than total awareness. |

## Awareness Tracker Widget

The **Bot Awareness Tracker widget** is a highly extensible base widget intended to visualize an AI agent's awareness state. 
It is commonly added to a Widget Component attached to AI pawns and bound to the Bot Awareness ViewModel. At its default level, 
the widget attempts to bind to:

- A `UTextBlock` named **AwarenessText**
- A `UProgressBar` named **AwarenessProgress**

> Both components are optional. Projects are not required to use them and may replace or ignore them entirely.

### Default Behavior Configuration

The following properties control the widget's default **presentation behavior**. These settings are optional and can be 
overridden entirely via Blueprint logic.

| Property                        | Description                                                             |
|---------------------------------|-------------------------------------------------------------------------|
| **Visibility When Unaware**     | Visibility applied while the AI agent is fully unaware.                 |
| **Visibility When Progressing** | Visibility applied while awareness is increasing but not yet confirmed. |
| **Visibility When Aware**       | Visibility applied while the AI agent is fully aware.                   |
| **Unaware Label**               | Text displayed while the AI is unaware.                                 |
| **Suspicious Label**            | Text displayed while the AI is suspicious.                              |
| **Alerted Label**               | Text displayed while the AI is alerted.                                 |
| **Aware Label**                 | Text displayed while the AI is fully aware.                             |
| **Unaware Color**               | Color applied to the progress bar while unaware.                        |
| **Suspicious Color**            | Color applied while suspicious.                                         |
| **Alerted Color**               | Color applied while alerted.                                            |
| **Aware Color**                 | Color applied while fully aware.                                        |

### Extensibility Hooks

The Bot Awareness Tracker exposes several **BlueprintNativeEvent functions** that allow projects to customize behavior 
without modifying the base widget. These functions are **purely cosmetic** and intended for presentation logic only.

| Function                        | Description                                                                                                                   |
|---------------------------------|-------------------------------------------------------------------------------------------------------------------------------|
| **Handle Awareness Changed**    | Called when the awareness level changes, providing both previous and new values. Useful for triggering animations or effects. |
| **Update Awareness Visibility** | Updates widget visibility based on the new awareness level.                                                                   |
| **Update Awareness Text**       | Updates the awareness text based on the new awareness level.                                                                  |
| **Update Progress Bar Color**   | Updates the progress bar color based on the new awareness level.                                                              |

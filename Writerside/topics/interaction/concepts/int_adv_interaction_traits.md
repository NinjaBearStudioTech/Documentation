# Traits, Duration, and Feedback
<primary-label ref="interaction"/>

On a Smart Object slot, use the **Interaction Type Tag** to name the action and **Runtime Tags** to describe how the slot should be used. Keep the matching type in the runtime tags so a request for that action can select the slot. Put the text the player sees in the **Execute Interaction** configuration.

| Setting | Example | What it changes |
| --- | --- | --- |
| Interaction Type Tag | `Interaction.Type.Collect` | Identifies Collect when the same actor offers more than one action. |
| Interaction Priority Tag | `Interaction.Priority.Primary` | Lets a prompt choose the primary offer. Pass an explicit type or summary ID when a button means one particular action. |
| Slot runtime trait | `Interaction.Trait.Automatic` | The manager tries to start this slot when the target **gains focus**. No button is required. |
| Slot runtime trait | `Interaction.Trait.Disposable` | The source unregisters the target when the interaction ends. The world actor and any contents are managed separately. |
| Project-defined slot tag | `Interaction.Trait.OnEnter` | Your own registration handler can recognize slots meant to run on entering range. Add and handle this tag in your project. See [Interact Without Focus](int_guide_without_focus.md). |

<img src="int_adv_trait_automatic.png" alt="Runtime tags on a Smart Object slot" width="720" border-effect="line"/>

## Choose What the Progress Bar Measures

Use **Duration** when the world action itself takes time. For a two-second search, the interaction starts on press, the slot is claimed, and the tree waits for the manager's relevant elapsed time. With **Automatic** time accumulation the clock starts with the interaction. With **Triggered** accumulation the tree starts it explicitly, for example after the character reaches the terminal. [Time an interaction in the State Tree](int_adv_interaction_duration.md).

Use an Enhanced Input **Hold** threshold when the **player's confirmation** takes time. Show input progress while the key is down, then request a zero-duration interaction when the hold triggers. [Set up a Hold Input Action](int_guide_hold_input.md).

## Give the Player Feedback

Override `GetDisplayTextForInteraction` on the target to change the prompt at runtime, such as showing **Unlock** on a locked door. The manager's `OnInteractionTimeAccumulated` and `Native_OnInteractionTimeAccumulated` provide the updated summary while interaction time is accumulating. Use its summary ID to update the right bar. For a ready-made widget and ViewModel bindings, see [Show a Prompt and Timed Progress](int_ui_mvvm.md).

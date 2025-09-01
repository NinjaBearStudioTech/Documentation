# Combat Handlers
<primary-label ref="input"/>

These are **additional handlers**, still based on the **Gameplay Ability System**, but providing certain flows mostly
related to [**Ninja Combat**](cbt_overview.md).

## Combat Combo
This input handler will properly handle a **Ninja Combat combo**, with Activation/Advancement features.

You can use this handler for **both** or **either** of the combo features. Activation will send the initial set of tags 
to activate the Combo Ability (i.e. `Combat.Ability.Combo`) and Advancement will check for an active combo window and 
send the provided set of tags (i.e. `Combat.Event.Combo.Attack.Primary`). 

This handler can be also used by the **secondary combo keys**, only handling follow-up events, but not the activation.

Even though this is mostly designed considering **Ninja Combat's input system**, it's just a GAS based check using 
gameplay tags, so if your combo system also follows that approach, this can be used too. 

| Property         | Purpose                                                                          |
|------------------|----------------------------------------------------------------------------------|
| `ComboStateTag`  | The gameplay tag that represents an **active combo state**.                      |
| `ActivationTags` | Gameplay tags that will be used to start the [**Combo ability**](cbt_combos.md). |
| `AdvancementTag` | Gameplay tag representing the **Advance Combo Event**.                           |

## Default, Hold, Combo
An Input Handler that handles three **combo/attack ability scenarios from the same Input Action**.

1. **Default Activation**: Triggers a default ability, when the input is quickly released.
2. **Hold to Activate**: Triggers a different ability, like a "hold" attack.
3. **Combo Event**: Sends a Gameplay Event to the active default ability.

The accompanying input handler just requires a "Hold" trigger. **Make sure to set the trigger as "One Shot"**, otherwise 
this handler will keep trying to activate the same ability each frame.
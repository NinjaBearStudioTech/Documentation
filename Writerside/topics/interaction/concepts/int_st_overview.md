# Smart Object Slots and Interaction Flow
<primary-label ref="interaction"/>

Give an object a slot for each action someone can use. A terminal might offer a quick **Read** and a longer **Search**. Each slot has its own position, interaction type, behavior configuration, and State Tree. A claim reserves that slot while a source uses it.

## From a Request to a Result

1. The source requests an action. On a focused target, pass the desired type to **Try Initialize Interaction With Current Target**. **Execute Interaction** claims the slot on the server and starts its tree on the Interaction Manager.
2. A tree using the **Interaction** schema (`NinjaInteractionComponentSchema`) can read the **Interaction State** evaluator's target actor, summary ID, slot transform, duration, and claim handle. **Interaction Player Context** adds the pawn and player controller for tasks that need them.
3. The tree can move the character, wait, or animate. **Trigger Target Behavior** is the step that calls the target. Bind its **Target Actor** and **Smart Object Claim Handle** to the corresponding evaluator outputs.
4. End the tree in success when its work is done, or failure when it cannot proceed. Keep **Release Handle Automatically** enabled on the trigger task for a short action. If a longer flow retains the slot, release the claim on its exit paths with **Release Interaction Handle**. The execution ability also cleans up its claim when it ends.

To change what the object offers during play, call **Set Interaction Slot Enabled** (`SetInteractionSlotEnabled`) on its target component on the server. For example, disable Search on an empty crate while keeping Inspect available.

## Position the Character

Use **Move To Interaction Point** when the player needs a path to the slot. Give it a player controller with a Path Following Component and a destination on the Nav Mesh. For an AI controller, use its usual AI Move To task. **Rotate To Interaction Target** can turn the pawn toward the target. For a short final adjustment at a lever or handle, use **Reach Target** with the slot transform. Put the operation that changes the world after a successful approach. Route a failed approach to the tree's failure exit.

## Put the Result on the Target

On a target implementing `IInteractionTargetInterface`, **Start Interaction** can return **Finished** for an immediate behavior, **Rejected** if the action cannot run, or **Started** for ongoing work. For ongoing work, retain the supplied Gameplay Behavior and end it when the target is done. **Finish Interaction** receives an **Interrupted** flag. Check that flag before granting a reward. On the supplied base actor, the default start result is Finished.

The target component also exposes `OnInteractionStarted`, `OnInteractionFinished`, and `OnInteractionCancelled`. Bind a lever's gameplay result to its successful finish. Use the manager's `OnInteractionStateChanged` or `Native_OnInteractionStateChanged` for source-side feedback, including cancellation before the target behavior starts.

To extend the execution ability, override **Handle Interaction Started**, **Handle Interaction Event**, or **Handle Interaction Finished** (`BP_HandleInteractionStarted`, `BP_HandleInteractionEvent`, `BP_HandleInteractionFinished`). For example, start a sound on the source, then stop it on finish or interruption.

[Build an immediate switch](int_guide_immediate.md) or [add a timed search](int_adv_interaction_duration.md).

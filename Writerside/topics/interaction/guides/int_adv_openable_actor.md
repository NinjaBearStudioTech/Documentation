# Make a Lockable Door
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Make a door show **Unlock** while locked, open for a player with the right key, and offer **Close** afterward. Start with a [working interaction source](int_first_steps.md) and a door mesh with a hinge or animation you can control.

<procedure title="Configure the door and key">
    <step><p>Create a Blueprint based on <code>NinjaInteractionOpenableActor</code>. Set up the target collision and give its Smart Object an <b>Open</b> slot and a <b>Close</b> slot. On each, set the behavior type and matching runtime tag to <code>Interaction.Type.Open</code> or <code>Interaction.Type.Close</code>. Use the <a href="int_guide_immediate.md">immediate tree</a> for each.</p></step>
    <step><p>Enable <b>Starts Locked</b>, set <b>Key Item Query</b> to match the intended key, and choose a <b>Key Resolver Class</b>. The default resolver can use Ninja Inventory keys. For a quest flag or another key system, subclass <code>NinjaInteractionKeyResolver</code> and override <b>Try Unlock With Key</b>. Return true when the instigator can unlock this door.</p></step>
    <step><p>Use the offered action when the player presses Interact. The base door handles a locked door through the <b>Open</b> action. It shows the unlock text, checks the key, and opens on success. Enable automatic closing and choose a delay if the door should close by itself.</p></step>
</procedure>

## Animate the Door for Each Player

Implement `ApplyOpenState` and `ApplyClosedState` to move the mesh. When **Snap To Final State** is true, set the final pose immediately so a player joining later sees the correct door. Use `ApplyLockedState` and `ApplyUnlockedState` for a lock indicator. Extend the server-side `Open` or `Close` functions for gameplay, such as revealing a room, and call the parent to preserve the door's state changes.

<img src="int_adv_openable_actor_blueprint_graph.png" alt="Door Blueprint applying its open and closed poses" width="740" border-effect="line"/>

Override `CanCloseAfterOpen` or `CanOpenAfterClosed` to restrict later uses. For a scripted unlock, call `ForceUnlock` on the server.

## Try It in Play

Try Open without a key, then with the matching key. The first attempt should leave the door closed. The second should open it and offer Close. If an open door still offers Open, compare the offered slot with the actor's **Is Open** state and verify the slot runtime tags.

# Interact Without Focus or Pick Up on Contact
<primary-label ref="interaction"/>
<secondary-label ref="guide"/>

Let the player collect a coin at their feet while their Interact button still points at a door. The scan can register both objects. For the coin, use its **registered slot** directly. The built-in `Interaction.Trait.Automatic` activates a slot when its target gains focus. The setup below works even if the coin never gains focus.

<procedure title="Mark the slots that can run in range">
    <step><p>Start with the <a href="int_guide_immediate.md">immediate State Tree</a>. Give the coin's slot the behavior type <code>Interaction.Type.Collect</code>, the same type in <b>Runtime Tags</b>, and <b>Duration</b> zero.</p></step>
    <step><p>In <b>Project Settings → Gameplay Tags</b>, add a project tag such as <code>Interaction.Trait.OnEnter</code>. Add it to the coin slot's <b>Runtime Tags</b>. Your handler below gives this tag its meaning. Leave <code>Interaction.Trait.Automatic</code> off so focus cannot also start the coin.</p></step>
    <step><p>For this first coin, size the scan overlap to the pickup distance. If your game needs a larger scan for doors, use a smaller pickup trigger as well. When the pawn enters that trigger, look up the coin in the manager and run the selection below. This gives a coin already registered at a distance a new chance to run on contact. The pawn needs an Interaction Manager and the granted <b>Execute Interaction</b> ability. A focus box or search ability is only needed for actions that use focus.</p></step>
</procedure>

## Start the Registered Slot

Do this on the **server**. It owns registration and claims. For a player button, send the selected summary ID to a server event on the player's pawn and validate it there.

1. For a walk-over coin, listen to the manager's `OnInteractionRegistered`. Break the summary and check **Is Enabled**, **Interaction Type** equals `Interaction.Type.Collect`, and **Slot Tags** contains the exact `Interaction.Trait.OnEnter` tag. If your listener attaches after registration, also check **Get Registered Interaction Targets** and **Get Interaction Summaries for Target**.
2. For a button-operated action without focus, run the lookup on the button press instead. For example, find enabled `Interaction.Type.Interact` summaries with a custom `Interaction.Trait.NearbyUse` tag and choose the closest matching actor in reach. Leave this tag off the door if its action should require focus.
3. Use **Get Interaction Summary** on the source manager to read the selected ID again. Check that the target is still in reach, is available, can handle the type, and the source has no running interaction. If the slot has Smart Object user conditions, evaluate them for this pawn and slot as part of your selection. Skip an unavailable or occupied slot.
4. On the manager, call **Create Request for Summary** with that summary. If the request is valid and its summary ID matches, make a **Gameplay Event Data** payload. Set **Event Tag** to `Interaction.Event.StartInteraction`, **Instigator** to the pawn, **Target** to the coin or switch, **Optional Object** to the request, and **Target Tags** to the request's slot tags. Call **Send Gameplay Event to Actor** with the **pawn** as the receiving actor and the same event tag. Its **Execute Interaction** ability claims the selected slot and runs its tree.

For a simple coin, use the target component's `OnInteractionFinished` to award one coin to the source pawn on the server. Mark the coin collected and disable its slot or remove it once the award succeeds. To transfer an actual inventory item and handle partial or failed pickups, follow [Interaction and Inventory](integration_interaction_inventory.md).

## Try It in Play

Face the door and approach the coin from the side so it enters scan range outside the focus box. The coin should be collected once without a button press. The door should stay closed and still respond when you press its button. Remove the custom OnEnter tag from a second coin and walk past it. That coin should stay in place. If both coins collect on focus, check which slots carry the built-in Automatic trait.

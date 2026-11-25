# First Steps: Interact with a Nearby Object
<primary-label ref="interaction"/>

Make a switch print a message when the player faces it and presses Interact. Start with the [collision presets and generic assets](int_setup.md) and a character whose Ability System Component is initialized.

<procedure title="Make the switch">
    <step><p>Create a Blueprint based on <code>NinjaInteractionActor_StaticMesh</code>. Give it a visible mesh and set its <b>Interaction Target Component</b> to a copy of <code>SO_Interaction_Generic</code>.</p></step>
    <step><p>In the Smart Object, give one slot an <b>Execute Interaction</b> configuration in its Gameplay Behavior definition. Choose <code>Interaction.Type.Interact</code> as the <b>Interaction Type Tag</b>, add the same tag to the slot's <b>Runtime Tags</b>, set the display text to <b>Use switch</b>, choose <code>ST_Interaction_Generic</code>, and set <b>Duration</b> to zero.</p></step>
    <step><p>Add a box around the switch mesh. Enable <b>Generate Overlap Events</b> and use the <b>InteractionTarget</b> collision preset. On the target component, bind <b>On Interaction Finished</b> to print <b>Switch used</b>. Place the switch in the level.</p></step>
</procedure>

<img src="int_target_actor_01.png" alt="Smart Object definition assigned to the Interaction Target Component" width="760" border-effect="line"/>

<procedure title="Give the player a scan area and a focus area">
    <step><p>Add an <b>Interaction Manager Component</b> to the player pawn. Add a sphere large enough to detect the switch from a few steps away. Set its <b>Component Tags</b> to include <code>Interaction.Component.InteractableScan</code>.</p></step>
    <step><p>Add a smaller box in front of the pawn, within the sphere. Give it the component tag <code>Interaction.Component.InteractableFocus</code>. Set both shapes to <b>InteractionSource</b> and enable <b>Generate Overlap Events</b>.</p></step>
    <step><p>Grant <code>InteractionAbility_FindInteractableActor</code> and <code>InteractionAbility_ExecuteInteraction</code> through the pawn's usual ability setup. For this example, keep the find ability's default <b>Find Closest Interaction Target</b> task.</p></step>
    <step><p>Map a Boolean Enhanced Input action to a key. Give it a <b>Pressed</b> trigger. On <b>Triggered</b>, call <b>Try Initialize Interaction With Current Target</b> on the pawn's manager with <code>Interaction.Type.Interact</code>.</p></step>
</procedure>

<tabs>
    <tab title="Scan sphere"><img src="int_source_component_scan.png" alt="Scan sphere and component tag on the pawn" width="760" border-effect="line"/></tab>
    <tab title="Focus box"><img src="int_source_component_focus.png" alt="Smaller focus box in front of the pawn" width="760" border-effect="line"/></tab>
</tabs>

## Try It in Play

Approach the switch and face it. Press once and look for one **Switch used** message. Press again to confirm the slot was released. Turn away so the switch leaves the focus box and press again. If the first press did nothing, bind **On Target Registered** and **On Focus Applied** on the target component to separate print messages. A registration message alone means the scan reached the switch but selection still needs attention.

## Next Steps

[Time a search in the tree](int_adv_interaction_duration.md), [confirm a switch with a held input](int_guide_hold_input.md), or [collect a tagged object without focusing it](int_guide_without_focus.md).

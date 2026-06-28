# Creating Opportunity Attacks

<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to create an **Opportunity Attack** using a **Gameplay Ability**, paired **Animation Montages**, a 
**Contextual Animation Scene**, and an optional **Camera Animation**.

For an overview of the feature, see [**Paired Animations**](cbt_concept_paired_animations.md).

## Required Components

Each character participating in the paired animation must have these components:

1. A **Contextual Animation Scene Actor Component**.
2. A **Motion Warping Component**, which may already be present if the character uses Melee Attacks.

<procedure title="Add the Required Components" collapsible="true" default-state="collapsed">
    <step>Open your base character class or blueprint.</step>
    <step>Click the <b>Add</b> button in the <b>Component List</b> and add <code>NinjaCombatMotionWarpingComponent</code>.</step>
    <step>Click the <b>Add</b> button in the <b>Component List</b> and add <code>ContextualAnimSceneActor</code>.</step>
    <step>Implement <code>GetMotionWarpingComponent</code> from <code>CombatSystemInterface</code>, returning your <b>Motion Warping Component</b>.</step>
    <tip>
        <p><b>All Participants</b></p>
        <p>If players and enemies use different base classes or blueprints, add these components to both.</p>
    </tip>
</procedure>

## Contextual Animation

Contextual animations are configured through a **scene asset** that plays **Animation Montages** for each defined **role**.

To create the scene, define the roles, prepare the montages, and then create the Contextual Animation Scene.

<procedure title="Define Contextual Roles" collapsible="true" default-state="collapsed">
    <img src="cbt_opportunity_roles_asset.png" alt="Contextual Roles Asset" thumbnail="true" border-effect="line"/>
    <step>Create a new <b>Data Asset</b> based on <code>ContextualAnimRolesAsset</code>.</step>
    <step>
        <p>Add a new role named <b>Victim</b>.</p>
        <p>Configure the role:</p>
        <ul>
            <li>Mark it as a <b>Character</b>.</li>
            <li>Set the capsule <b>Half Height</b> and <b>Radius</b> to match the character's Capsule Component.</li>
            <li>Set <b>Mesh Rotation Yaw</b> to <code>-90</code>, matching the common mesh rotation used by Character Blueprints.</li>
        </ul>
    </step>
    <step>Add a new role named <b>Attacker</b> and configure it with the same values used by the <b>Victim</b> role.</step>
    <note>
        <p><b>Multiple Role Assets</b></p>
        <p>If your Contextual Animations involve characters with different capsule or mesh settings, create a Role Asset for each setup.</p>
    </note>
</procedure>

<procedure title="Create the Attacker Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_opportunity_montage_attacker.png" alt="Attacker Animation Montage" thumbnail="true" border-effect="line"/>
    <step>Create an <b>Animation Montage</b> for the attacker.</step>
    <step>Set the montage to use the correct full-body <b>Slot</b>.</step>
    <step>Make sure the source Animation Sequence has <b>Root Motion</b> enabled.</step>
    <step>
        <p>Add <b>Melee Scan Animation Notify States</b> as needed.</p>
        <ul>
            <li>You can use different <b>Gameplay Effects</b> for each hit.</li>
            <li>For example, early hits can apply partial damage, while the final hit can apply fatal damage.</li>
        </ul>
    </step>
    <step>Add a <b>Motion Warping Animation Notify State</b> and name it <code>ExecutionWarp</code>.</step>
</procedure>

<procedure title="Create the Victim Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_opportunity_montage_victim.png" alt="Victim Animation Montage" thumbnail="true" border-effect="line"/>
    <step>Create an <b>Animation Montage</b> for the victim.</step>
    <step>Set the montage to use the correct full-body <b>Slot</b>.</step>
    <step>Make sure the source Animation Sequence has <b>Root Motion</b> enabled, if the victim animation moves the character.</step>
    <step>If this animation represents <b>fatal damage</b>, add the <b>Death Animation Notify</b>.</step>
    <step>Optionally, add the <b>Ragdoll Animation Notify</b>.</step>
</procedure>

<procedure title="Create the Contextual Scene" collapsible="true" default-state="collapsed">
    <img src="cbt_opportunity_scene_asset.png" alt="Contextual Scene Asset" thumbnail="true" border-effect="line"/>
    <step>In the <b>Content Browser</b>, click the <b>Add</b> button and select <b>Animation</b> &rarr; <b>Contextual Anim Scene</b>.</step>
    <step>Open the new asset and set the <b>Roles Asset</b> created earlier.</step>
    <step>Click <b>Update Roles</b> and confirm.</step>
    <step>For the <b>Primary Role</b>, select <b>Victim</b>.</step>
    <step>
        <p>Click <b>New Animset</b> and configure it:</p>
        <ul>
            <li>Set the <b>Section Name</b> to identify the scene.</li>
            <li>Set the Animation Montage for the <b>Victim</b> role.</li>
            <li>Set the Animation Montage for the <b>Attacker</b> role.</li>
        </ul>
        <tip>
            <p><b>Movement Mode</b></p>
            <p>Leaving Movement Mode set to <b>Walking</b> is usually fine. Some montages may produce better results with <b>Flying</b>.</p>
        </tip>
    </step>
    <step>In the <b>Timeline</b>, select the <b>Attacker</b> role track.</step>
    <step>In the <b>Mesh To Scene</b> panel, adjust the attacker position to match the intended animation distance.</step>
    <step>Select the <b>Victim</b> role track and adjust rotation as needed.</step>
    <step>
        <p>Add a new <b>Warp Point Definition</b>:</p>
        <ul>
            <li>Set <b>Warp Target Name</b> to <code>ExecutionWarp</code>. This must match the name used by the <b>Motion Warping Animation Notify State</b>.</li>
            <li>Set <b>Mode</b> to <b>Primary Actor</b>, so the warp targets the victim.</li>
            <li>Click <b>Update Warp Points</b>.</li>
        </ul>
    </step>
</procedure>

## Camera

<secondary-label ref="optional"/>

Opportunity Attacks can play **Camera Animations** along with the Contextual Animation Scene.

Camera Animations are played through the **Player Camera Manager**, so your Player Controller must use a compatible camera manager.

<procedure title="Use the Combat Camera Manager" collapsible="true" default-state="collapsed">
    <step>Create a Player Camera Manager based on <code>NinjaCombatPlayerCameraManager</code>.</step>
    <step>Assign this Player Camera Manager to your <b>Player Controller</b>.</step>
    <step>
        <p>If you cannot use <code>NinjaCombatPlayerCameraManager</code>, implement <code>CombatCameraManagerInterface</code> in your own Player Camera Manager.</p>
        <p>In that case, implement <code>PlayCombatCameraAnimation</code> and <code>StopCombatCameraAnimation</code>.</p>
    </step>
</procedure>

<procedure title="Create Camera Animations" collapsible="true" default-state="collapsed">
    <step>In the <b>Content Browser</b>, click the <b>Add</b> button and select <b>Cinematics</b> &rarr; <b>Camera Animation</b>.</step>
    <step>In the <b>Content Browser</b>, click the <b>Add</b> button and select <b>Cinematics</b> &rarr; <b>Level Sequence</b>.</step>
    <step>Create and open an empty level to author the Camera Animation.</step>
    <step>
        <p>In the empty level, place your <b>Player Character Blueprint</b> or a simpler reference blueprint.</p>
        <p>The blueprint should have the correct camera setup and a Mesh or Animation Blueprint able to play the <b>Attacker Animation Montage</b>.</p>
        <p>Place this blueprint at location <code>[0, 0, 0]</code> and rotation <code>[0, 0, 0]</code>.</p>
        <tip>
            <p><b>Complex Character Setups</b></p>
            <p>If your character uses systems such as IK Retargeting, Mutable, or Leader Pose Components, consider creating a simpler Mannequin-based Character Blueprint for camera authoring.</p>
        </tip>
    </step>
    <step>
        <p>Add a <b>Cine Camera Actor</b> to the level and position it to match the camera location from the Player Blueprint.</p>
        <p>Optionally, set <b>Lens Settings</b> to <code>12mm Prime</code> and <b>Crop Settings</b> to <code>2.39</code>.</p>
    </step>
    <step>Add a <b>Camera Cuts Track</b> to the Level Sequence.</step>
    <step>Add the <b>Player Blueprint</b> from the level to the sequence.</step>
    <step>Add the <b>Cine Camera</b> from the level to the sequence.</step>
    <step>If Sequencer starts piloting the camera, click <b>Eject</b> to return to regular viewport navigation.</step>
    <step>Remove the <b>Transform</b> track from the Cine Camera, since the camera movement will be authored in the Camera Animation asset.</step>
    <step>Save this level as a reusable <b>Camera Animation Authoring Level</b>.</step>
    <step>Add an <b>Animation</b> track to the Player Blueprint and select the <b>Attacker Animation Sequence</b>.</step>
    <step>Adjust the timeline length to match the animation.</step>
    <step>Add a <b>Template Sequence</b> to the Cine Camera track and select the <b>Camera Animation</b>.</step>
    <step>
        <p>Animate the camera by creating <b>keyframes</b> for changes in location, rotation, and other camera properties.</p>
        <p>For smoother transitions, it is usually best for the camera to return to its origin point by the end of the animation.</p>
    </step>
    <step>Optionally, create <b>Camera Shake</b> assets and add them to the timeline on each attack.</step>
</procedure>

<procedure title="Create a Camera Anchor" collapsible="true" default-state="collapsed">
    <step>Create a new <b>Actor Blueprint</b> based on <code>NinjaCombatCameraAnchorActor</code>.</step>
    <step>Optionally, modify the <b>Camera Component</b> to use a different camera type.</step>
</procedure>

## Gameplay Ability

Opportunity Attacks are executed by <code>CombatAbility_OpportunityAttack</code>, using the assets configured in the 
previous steps.

<procedure title="Configure the Opportunity Attack" collapsible="true" default-state="collapsed">
    <img src="cbt_opportunity_ability.png" alt="Opportunity Attack Ability" thumbnail="true" border-effect="line"/>
    <step>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_OpportunityAttack</code>.</step>
    <step>Set a <b>Targeting Preset</b> to select eligible targets.</step>
    <step>Set the <b>Contextual Animation</b> configured for the attack.</step>
    <step>Set the <b>Camera Animation</b>, if the attack uses one.</step>
    <step>Set the <b>Camera Anchor Class</b>, if needed.</step>
    <step>Add an <b>Activation Tag</b> for the Opportunity Attack.</step>
    <step>Grant the Gameplay Ability to the owner.</step>
    <step>Configure input or interaction logic to activate the ability.</step>
</procedure>

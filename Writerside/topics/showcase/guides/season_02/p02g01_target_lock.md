# Configure the Target Lock
<secondary-label ref="guide"/>

The **Target Lock Ability** helps with camera focus, precision and add visual indicators to a target. This system uses
Unreal Engine's **Gameplay Targeting System** to collect targets.

<procedure title="Create a Targeting Preset" collapsible="true">
    <step>Create a new <b>Targeting Preset</b>. It will be used for the target selection.</step>
    <step>Add the <b>Camera</b> Selection Task. You can use its default values or adjust them as you like.</step>
    <step>Add the <b>AOE</b> Selection Task. Use a <b>Sphere</b> shape, add <b>Pawn</b> and <b>World Dynamic</b> as <b>Collision Object Types</b>, set it to <b>ignore the source actor and instigator</b>, and a <b>radius</b> of <b>1600</b>.</step>
    <step>Add the <b>Actor Class</b> Filter Task. Set your <b>base Character Class</b> as the <b>Required Actor Class Filter</b>, or adjust these filters to match your character hierarchy.</step>
    <step>Add the <b>Facing</b> Filter Task. Set the maximum angle to <b>60</b>, or any other value that makes sense to you.</step>
    <step>Add the <b>Dead</b> Filter Task.</step>
    <step>Add the <b>Sort By Distance</b> Filter Task.</step>
    <img src="p02g01_targeting_preset.png" alt="Targeting Preset" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the Target Lock Ability" collapsible="true">
    <step>Create a new <b>Gameplay Ability</b> using <code>CombatAbility_TargetLock</code> as the base class.</step>
    <step>Set the <b>Targeting Preset</b> that was created in the step above.</step>
    <step>Disable <b>Move to New Targets</b> for now, but feel free to explore this if you'd like.</step>
    <step>Set the <b>Distance Threshold</b> to <b>1600</b>, or any other value that makes sense to you. This will disengage from the target, if the distance from the avatar exceeds this value.</step>
    <step>Add this Gameplay Ability to the list of <b>Default Abilities</b> added to the player.</step>    
    <img src="p02g01_target_lock_ability.png" alt="Targeting Preset" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create a Target Lock Widget" collapsible="true">
    <step>Create a new <b>User Widget</b> using <code>NinjaCombatBaseWidget</code> as the base class.</step>
    <step>Add an <b>Image</b> component, using any marker that you'd like.</step>
    <img src="p02g01_target_lock_widget.png" alt="Targeting Preset" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create a Marker Actor" collapsible="true">
    <step>Create a new <b>Blueprint</b> using <code>NinjaCombatMarkerActor</code> as the base class.</step>
    <step>Add the widget created in the previous step to this actor's <b>Target Lock Widget Component</b>.</step>
    <step>Set the new Blueprint to your player character, in its <b>Combat Manager Component</b>, in the <b>Target Marker Actor Class</b>.</step>
    <img src="p02g01_marker_actor.png" alt="Targeting Preset" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Configure the enemy anchor" collapsible="true">
    <step>In your <b>Base Character</b> (or Base Enemy Blueprint), add a new <b>Scene Component</b> under the main <b>Character Mesh</b>.</step>
    <step>Set this component's location where the Marker Actor should be attached.</step>
    <step>Add the <code>Combat.Component.TargetLockAnchor</code> tag to the component.</step>
</procedure>

<procedure title="Configure the Target Lock Input" collapsible="true">
    <step>Create a new <b>Input Action</b> for the Target Lock input. Add a <b>Pressed</b> trigger to it.</step>
    <step>Add the new Input Action to your <b>Input Mapping Context</b> asset, mapping it to an appropriate key.</step>
    <step>Create a new <b>Input Handler</b> or add one directly to your <b>Input Setup</b>, using the <b>Activate Ability by Tags</b> as base.</step>
    <step>Add <code>Ability.TargetLock</code> to the <b>Ability Tags</b>.</step>
    <step>Set <b>Toggle Activation</b>, so the ability is activated and then deactivated on input.</step>
    <img src="p02g01_input_handler.png" alt="Input Handler" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Test Everything" collapsible="true">
    <step>Hit <b>Play</b> and test the target lock by pressing the appropriate key.</step>
    <step>Capture the correct target via <b>camera aiming</b>, and also by <b>proximity</b>.</step>
</procedure>
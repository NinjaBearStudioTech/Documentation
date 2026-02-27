# Collision Settings
<primary-label ref="interaction"/>

<tldr>
    <p><b>Summary: Configuring Collisions for Ninja Interaction</b></p>
    <br/>
    <ul>
        <li>Configure a new <b>Object Channel</b> for <b>Interaction Objects</b>.</li>
        <li>Configure a new <b>Trace Channel</b> for <b>Interaction Line-of-Sight</b>.</li>
        <li>Configure new <b>Collision Presets</b> for the <b>Interaction Source</b> and <b>Interaction Target</b>.</li>
    </ul>
</tldr>

In this page, you will learn how to configure the necessary **Collisions** that will be used by **Ninja Interaction**. 
These are used by **Interaction Scans** and **Line-of-Sight Validation** between an interactor and a target.

## Object and Trace Channels
Ninja Interaction uses **Object** and **Trace** channels to detect interaction targets and to validate visibility between
the scanner and the interactable. For more details about Object and Trace Channels, check the [official Unreal Engine documentation][1].

<procedure title="Configure the Interaction Object channel" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Object Channel</b> section, create a new channel, by clicking the <b>New Object Channel</b> button, and name it <b>InteractionObject</b>. Set its <b>default response</b> to <b>ignore</b>.</step>
    <tip>This channel represents any actor in the world that can be detected as an <i>Interaction Target</i>.</tip>
</procedure>

<procedure title="Configure the Interaction Trace channel" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Trace Channel</b> section, create a new channel, by clicking the <b>New Trace Channel</b> button, and name it <b>InteractionTrace</b>. Set its <b>default response</b> to <b>ignore</b>.</step>
    <tip>This channel is used to validate <i>line-of-sight</i> between the scanner and the interaction target.</tip>
</procedure>

## Collision Presets
To simplify assigning the correct channels and responses to relevant actors, we will create two **Collision Presets**:
one for the scanner (Source) and one for the targets (Target).

> Using presets helps you apply consistent collision rules to scanning components and interactable actors without
> having to configure each one manually.
{style=note}

The **InteractionSource** preset can be assigned to any scanning component (usually attached to the Interaction Manager's
owner). It detects and overlaps with Interaction Objects.

The **InteractionTarget** preset can be assigned to any Interactable Actor. It ensures it can be detected by scans and
also blocks line-of-sight traces.

<procedure title="Configure the Interaction Object Channel" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Object Channels</b> section, create a new entry, name it <b>InteractionObject</b>.</step>
    <step>Set its <b>Default Response</b> to <b>Ignore</b>.</step>
</procedure>

<procedure title="Configure the Interaction Trace" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Trace Channels</b> section, create a new entry, name it <b>InteractionTrace</b>.</step>
    <step>Set its <b>Default Response</b> to <b>Ignore</b>.</step>
</procedure>

<procedure title="Configure the Interaction Source preset" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Preset</b> section, create a new entry, name it <b>InteractionSource</b>.</step>
    <step>
        <p>Set <b>Collision Enabled</b> to <b>Query Only</b>, the <b>Object Type</b> to <b>InteractionObject</b> and a meaningful description like <i>Scanner preset that overlaps with interaction targets</i>.</p>
        <tip>Make sure <b>InteractionObject</b> was created in the <i>Object Channel</i> section above, or it won't show in the dropdown!</tip>
    </step>
    <step>
        <p>Set the <b>Collision Responses</b> so everything is <b>ignored</b>, except for <b>InteractionObject</b>, which should be set to <b>Overlap</b>.</p>
        <p><img src="int_setup_collision_preset_source.png" alt="Interaction Source Preset" border-effect="line"/></p>
    </step>
</procedure>

<procedure title="Configure the Interaction Target preset" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>In the <b>Preset</b> section, create a new entry, name it <b>InteractionTarget</b>.</step>
    <step>
        <p>Set <b>Collision Enabled</b> to <b>Query Only</b>, the <b>Object Type</b> to <b>InteractionObject</b> and a meaningful description like <i>Allows targets to be detected for interactions</i>.</p>
        <tip>Make sure <b>InteractionObject</b> was created in the <i>Object Channel</i> section above, or it won't show in the dropdown!</tip>
    </step>
    <step>
        <p>Set the <b>Collision Responses</b> so everything is <b>ignored</b>, except for <b>InteractionObject</b>, which should be set to <b>Block</b>.</p>
        <p><img src="int_setup_collision_preset_target.png" alt="Interaction Target Preset" border-effect="line"/></p>
    </step>
</procedure>

<procedure title="Set Line of Sight on Relevant Presets" collapsible="true" default-state="expanded">
    <step>In the Engine, navigate to your <b>Collision</b> settings (Edit &rarr; Project Settings &rarr; Engine).</step>
    <step>
        In the <b>Preset</b> section the <b>Block All</b> preset and set the <b>Interaction Trace</b> response to <b>Block</b>.
        <tip>Make sure <b>InteractionTrace</b> was created in the <i>Object Trace</i> section above, or it won't show in the dropdown!</tip>
    </step>
    <step>Repeat this for any other preset that could potentially block line-of-sight for interactions, such as <b>Pawn</b> and <b>Destructible</b>.</step>
    <note>
        <p><b>Blocking Objects vs. Tracing Interaction Targets</b></p>
        <p>When validating interaction Line of Sight, traces are meant to detect blocking geometry, not to confirm a hit on the interaction target. This avoids coupling interaction logic to the target's collision setup, mesh composition, or component hierarchy.</p>
        <p>Interaction should succeed as long as nothing physically blocks the line of sight. Interaction should fail because something blocks it, not because the interaction target failed to respond to a trace.</p>
    </note>
</procedure>

These settings cover the **most common interaction scenarios**, and should be sufficient for the majority of interaction 
targets.

For more specialized cases, it is **optional but recommended** to create dedicated collision presets for interaction 
targets with unique behavior or requirements, such as _vendors_, _pickups_, _corpses_, or other bespoke gameplay actors. 

This helps keep interaction rules explicit, predictable, and easy to reason about as complexity grows.

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/collision-in-unreal-engine---overview

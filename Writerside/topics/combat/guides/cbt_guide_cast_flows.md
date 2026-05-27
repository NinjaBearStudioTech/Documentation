# Building Cast Flows
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to build common **Cast Flows** using the Cast Ability, Targeting Presets, Ability Targeting Actors,
and Cast Actors.

For a deeper explanation of the systems and settings used by these examples, see the [**related concepts**](cbt_concepts_cast_flows.md).

## Prerequisites

### Player Vitals Widget
<secondary-label ref="optional"/>

Before following this guide, consider [**setting up your combat UI**](cbt_guide_widgets.md#player-vitals) so you can
track resource changes, such as mana costs and regeneration delays, while testing the examples. Alternatively, you can
use the Gameplay Debugger for this purpose.

### Input Handling

Make sure your input setup can activate the ability and confirm or cancel targeting for interactive Cast Flows. For more
information, see [**Combat and Input Integration**](integration_combat_input.md).

Integration with Ninja Input is optional, but input handling for ability activation should already be configured.  

## Gameplay Targeting System
Use this approach when the ability can rely on a **Targeting Preset** to **find and filter valid targets**. This is the
most direct Cast Ability setup: the preset collects the targets, then the ability applies its configured Gameplay Effect
to the results.

<procedure title="Create the Targeting Preset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_targeting_preset.png" alt="Targeting Preset" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Targeting data folder, create a new <b>Data Asset</b> using <code>TargetingPreset</code> as the base class.</p>
    </step>
    <step>
        <p>Add <b>Targeting Selection Task AOE</b> to the list of <b>Tasks</b>.</p>
    </step>
    <step>
        <p>Configure the AOE task with the following values:</p>
        <ul>
            <li><b>Shape Type</b>: <b>Sphere</b></li>
            <li><b>Collision Channel</b>: <code>CombatObject</code></li>
            <li><b>Ignore Source Actor</b>: enabled</li>
            <li><b>Ignore Instigator Actor</b>: enabled</li>
            <li><b>Radius</b>: <code>600</code></li>
        </ul>
    </step>
    <step>
        <p>Add <b>Targeting Filter Task Dead</b> to the list of <b>Tasks</b>.</p>
        <note>
            <p><b>Task Order Matters!</b></p>
            <p>Targeting Presets evaluate tasks <b>in the order they are listed</b>. Add selection tasks first, followed by filters, then sorting tasks if needed.</p>
        </note>
    </step>
</procedure>

<procedure title="Create the Damage Gameplay Effect" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_effect_damage.png" alt="Damage Gameplay Effect" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Cast Ability folder, create a new <b>Gameplay Effect Blueprint</b> using <code>CombatEffect_Damage</code> as the base class.</p>
    </step>
    <step>
        <p>Add <code>Combat.Effect.Damage.Unblockable</code> to <b>Tags This Effect Has</b>.</p>
        <tip>
            <p><b>Skipping Blocking</b></p>
            <p>This step is optional. In this example, targets cannot mitigate this damage by blocking.</p>
        </tip>
    </step>
    <step>
        <p>Add a <b>Calculation Modifier</b> for the <b>Calculation Class</b>. Select <b>Damage Multiplier Backing Data</b> and set <b>Scalable Float Magnitude</b> to <code>2.0</code>.</p>
        <tip>
            <p><b>Damage Scaling</b></p>
            <p>This doubles the <b>Base Damage</b> value defined in the <b>Combat Attribute Set</b>. You can adjust this value to make the cast stronger or weaker.</p>
        </tip>
    </step>
    <step>
        <p>Optionally, add a <b>Gameplay Cue</b> that should be applied to each target affected by the cast.</p>
    </step>
</procedure>

<procedure title="Create the Success Gameplay Effect" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_effect_success.png" alt="Success Gameplay Effect" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Cast Ability folder, create a new <b>Gameplay Effect Blueprint</b> using <code>GameplayEffect</code> as the base class.</p>
    </step>
    <step>
        <p>Add a <b>Gameplay Cue</b> that should be applied to the instigator when the cast succeeds.</p>
        <tip>
            <p><b>Gameplay Cues</b></p>
            <p>You can use this Gameplay Effect to grant benefits to the instigator, or simply to trigger a Gameplay Cue.</p>
            <p>Alternatively, you can play Gameplay Cues directly from the Animation Montage assigned to the ability.</p>
        </tip>
    </step>
</procedure>

<procedure title="Create the Cost Gameplay Effect" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_effect_cost.png" alt="Cost Gameplay Effect" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Cast Ability folder, create a new <b>Gameplay Effect Blueprint</b> using <code>GameplayEffect</code> as the base class.</p>
    </step>
    <step>
        <p>Add an <b>Apply Additional Effects</b> component and add <code>CombatEffect_CancelManaRegeneration</code>.</p>
        <p>This briefly interrupts mana regeneration, based on the <code>ManaRegenDelay</code> attribute, after the mana cost is applied.</p>
    </step>
    <step>
        <p>Add a new <b>Modifier</b> and set the <code>Mana</code> Gameplay Attribute.</p>
    </step>
    <step>
        <p>Set <b>Calculation Type</b> to <b>Attribute Based</b>. Set <b>Coefficient</b> to <code>-1.0</code> and set <code>ManaCost</code> as the <b>Attribute to Capture</b>.</p>
        <p>You can adjust this further by changing the multiplier or connecting the value to a curve.</p>
    </step>
</procedure>

<procedure title="Create the Animation Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_montage_notify.png" alt="Cast Animation Montage (with Notify)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Select the Animation Sequence that represents the Cast Ability and create an <b>Animation Montage</b> from it.</p>
    </step>
    <step>
        <p>If applicable, select the correct <b>Slot</b> for the Animation Montage, based on the setup in your <b>Animation Instance</b>.</p>
    </step>
    <step>
        <p>Navigate to the point in the Animation Montage where the cast should trigger, then add the <b>Trigger Cast</b> Animation Notify.</p>
    </step>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_targeting_preset.png" alt="Cast Ability (Targeting Preset)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Create a new <b>Gameplay Ability</b> using <code>CombatAbility_Cast</code> as the base class, and name it <code>GA_Cast_TargetingPreset</code>.</p>
    </step>
    <step>
        <p>Configure the Cast Ability with the following values:</p>
        <ul>
            <li><b>Cast Trigger</b>: <b>Gameplay Event</b></li>
            <li><b>Targeting</b>: <b>Targeting System</b></li>
            <li><b>Commit Time</b>: <b>Ability Activates</b></li>
            <li><b>Cast Effect Class</b>: Gameplay Effect created for the cast outcome</li>
            <li><b>Targeting Preset</b>: Targeting Preset created to select targets</li>
            <li><b>Default Animation Montage</b>: Animation Montage with the <b>Trigger Cast</b> Notify</li>
        </ul>
    </step>
    <step>Add any <b>Gameplay Tags</b> required to activate the ability.</step>
    <step>Set <b>Cost Effect Class</b> to the Cost Gameplay Effect created for this ability.</step>
</procedure>

## Ability Targeting Actor
Use this approach when the ability needs to **collect targets through the Gameplay Ability System's Targeting Actors**.
This supports the **target actor types provided by GAS**, including custom subclasses, making it useful for abilities
that already fit the standard GAS targeting flow.

<procedure title="Create the Looping Animation Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_montage_loop.png" alt="Cast Animation Montage (looping)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Select the Animation Sequence that represents the Cast Ability and create an <b>Animation Montage</b> from it.</p>
    </step>
    <step>
        <p>If applicable, select the correct <b>Slot</b> for the Animation Montage, based on the setup in your <b>Animation Instance</b>.</p>
    </step>
    <step>
        <p>Create a <b>Loop</b> section at the point where the ability should wait for target confirmation.</p>
    </step>
    <step>
        <p>Create a <b>Confirmed</b> section at the point where the animation should continue after the cast is confirmed.</p>
    </step>
    <step>
        <p>Configure the montage section transitions so <b>Default</b> transitions into <b>Loop</b>.</p>
    </step>
    <step>
        <p>Configure the <b>Loop</b> section to transition into itself, so the animation keeps playing while the ability waits for confirmation.</p>
    </step>
    <step>
        <p>Configure the <b>Confirmed</b> section as the section played after confirmation.</p>
        <note>
            <p><b>No Trigger Cast Notify</b></p>
            <p>This montage does not need the <b>Trigger Cast</b> Animation Notify. In this flow, the cast is triggered when the target is confirmed.</p>
        </note>
    </step>
</procedure>

<procedure title="Create the Ability Targeting Actor" collapsible="true" default-state="collapsed">
    <step>
        <p>Create a new <b>Ability Targeting Actor</b> using <code>ANinjaCombatAbilityTargetingActor</code> as the base class.</p>
        <tip>
            <p><b>Targeting Actor Base Class</b></p>
            <p>The base actor provided by Ninja Combat is not required. If another Targeting Actor from the Gameplay Ability System is a better fit for your ability, you can use that instead.</p>
        </tip>
    </step>
    <step>
        <p>Configure any visuals needed by the targeting actor, such as decals, meshes, particle effects, or other placement indicators.</p>
    </step>
    <step>
        <p>Set <b>Targeting Type</b> to <b>Targeting Preset</b>.</p>
    </step>
    <step>
        <p>Set <b>Targeting Preset</b> to the Targeting Preset created earlier in this guide.</p>
    </step>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_confirm_targets.png" alt="Cast Ability (Confirm Targets)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Duplicate the Cast Ability created in the Gameplay Targeting System section, <code>GA_Cast_TargetingPreset</code>, and name the new ability <code>GA_Cast_Confirm</code>.</p>
    </step>
    <step>
        <p>Configure the Cast Ability with the following values:</p>
        <ul>
            <li><b>Cast Trigger</b>: <b>Ability Activation</b></li>
            <li><b>Targeting</b>: <b>Wait for Confirmation</b></li>
            <li><b>Commit Time</b>: <b>Targets Acquired</b></li>
            <li><b>Confirmation Type</b>: <b>User Confirmed</b></li>
            <li><b>Targeting Actor Class</b>: the Ability Targeting Actor created in the previous procedure</li>
            <li><b>Default Animation Montage</b>: the Animation Montage with the <b>Loop</b> and <b>Confirmed</b> sections</li>
        </ul>
    </step>
</procedure>

## Cast Actor
Use this approach when the ability should **spawn a dedicated Cast Actor into the world**. The Cast Actor is responsible 
for collecting targets, usually through collision or overlap logic, and applying the Gameplay Effect set in the ability.

<procedure title="Create the Cast Actor" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_actor_graph.png" alt="Cast Actor Graph" width="780" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Blueprints folder, create a new <b>Cast Actor Blueprint</b> using <code>NinjaCombatCastActor_Sphere</code> as the base class.</p>
    </step>
    <step>
        <p>Add a <b>Niagara Component</b> and an <b>Audio Component</b> to the <b>Cast Sphere</b>. Set <b>Auto Activate</b> to <code>false</code> on both components.</p>
        <tip>Although you can assign particles and sound assets directly to these components, it is usually better to keep this Blueprint as an <b>abstract parent</b> for your Cast Actors.</tip>
    </step>
    <step>
        <p>In the <b>My Blueprint</b> tab, expand <b>Overridable Functions</b> and select <code>StartCast</code>. This adds the event to the <b>Event Graph</b>.</p>
    </step>
    <step>
        <p>Right-click the <code>StartCast</code> node and select <b>Add Call to Parent Function</b>. Connect the parent function call to the event.</p>
        <note>Always call the <b>Parent Function</b> in your base <b>Cast Actors</b>, since the base class runs important setup logic there.</note>
    </step>
    <step>
        <p>Bind a new event to the Niagara Component's <b>System Finished</b> delegate.</p>
    </step>
    <step>
        <p>Activate the <b>VFX</b> and <b>Audio</b> components. Make sure both components are set to <b>Reset</b>, then call <b>Play</b> on the audio component.</p>
    </step>
    <step>
        <p>In the <b>System Finished</b> event, unbind the callback and deactivate the Poolable Actor through the <b>Poolable Actor Component</b>.</p>
    </step>
    <step>
        <p>Close the base Blueprint and create a new <b>Child Blueprint</b>. This child Blueprint is the one that will be used by the ability.</p>
    </step>
    <step>
        <p>Assign the Niagara System and Sound assets that should be used by this Cast Actor.</p>
    </step>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_actor.png" alt="Cast Ability (Actor)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Duplicate the Cast Ability created in the Gameplay Targeting System section, <code>GA_Cast_TargetingPreset</code>, and name the new ability <code>GA_Cast_CastActor</code>.</p>
    </step>
    <step>
        <p>Set <b>Targeting</b> to <b>Cast Actor</b>.</p>
    </step>
    <step>
        <p>Set <b>Cast Actor Class</b> to the Cast Actor created in the previous procedure.</p>
    </step>
    <step>
        <p>Make sure <b>Successful Cast Effect Class</b> is set to the Success Gameplay Effect created earlier in this guide.</p>
        <p>This is the same Gameplay Effect created for the <code>GA_Cast_TargetingPreset</code>, so no changes should be needed here.</p>
    </step>
</procedure>

## Targeted Cast Actor
Use this approach when the ability needs a targeting step before spawning the Cast Actor. The Ability Targeting Actor
selects where the cast should happen, then the ability spawns a Cast Actor at that location to collect targets and apply
the configured Gameplay Effect.

<procedure title="Create the Ability Targeting Actor" collapsible="true" default-state="collapsed">
    <step>
        <p>Create a new <b>Child Blueprint</b> using the Ability Targeting Actor created in the previous section as the parent class.</p>
    </step>
    <step>
        <p>Set <b>Targeting Type</b> to <b>Targeting Preset</b>.</p>
    </step>
    <step>
        <p>Set <b>Targeting Preset</b> to the Targeting Preset created earlier in this guide.</p>
    </step>
</procedure>

<procedure title="Create the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_confirm_cast.png" alt="Cast Ability (Confirm Cast)" thumbnail="true" border-effect="line"/>
    <step>
        <p>Duplicate the Cast Ability created in the Ability Targeting Actor section, <code>GA_Cast_Confirm</code>, and name the new ability <code>GA_Cast_SelectLocation</code>.</p>
    </step>
    <step>
        <p>Set <b>Targeting</b> to <b>Wait for Confirmation and Spawn Actor</b>.</p>
    </step>
    <step>
        <p>Set <b>Targeting Actor Class</b> to the Ability Targeting Actor created in the previous procedure.</p>
    </step>
    <step>
        <p>Set <b>Cast Actor Class</b> to the Cast Actor created earlier in this guide.</p>
    </step>
</procedure>
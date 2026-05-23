# Building Cast Flows
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

The **Cast Ability** is a flexible Gameplay Ability base for effects that need to be **created**, **placed**, or **triggered** 
in the world. It supports traditional spellcasting patterns, such as _auras_ and _area-of-effect spells_, as well as one-off 
effects like _explosions_, _novas_, and similar bursts.

This guide covers the main ways to configure a Cast Ability. Each approach uses the **same base ability**, but changes
how **targets are collected** and, in some cases, **where the cast actor spawns**. You can pick the setup that best
matches the kind of ability you want to build.

Although some assets are shared between examples, each Cast Flow can be created **independently**. This guide presents 
them **incrementally**, moving from the simplest setup to more advanced flows that add custom targeting, spawned Cast 
Actors, and targeted placement.

## Gameplay Targeting System
Use this approach when the ability can rely on a **Targeting Preset** to **find and filter valid targets**. This is the 
most direct Cast Ability setup: **the preset collects the targets, then the ability applies its configured Gameplay Effect 
to the results**.

<procedure title="Create the Targeting Preset" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_targeting_preset.png" alt="Targeting Preset" thumbnail="true" border-effect="line"/>
</procedure>

<procedure title="Create the Damage Gameplay Effect" collapsible="true" default-state="collapsed">
</procedure>

<procedure title="Create the Success Gameplay Effect" collapsible="true" default-state="collapsed">
</procedure>

<procedure title="Configure the Cost Gameplay Effect" collapsible="true" default-state="collapsed">
</procedure>

<procedure title="Configure the Animation Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_montage_notify.png" alt="Cast Animation Montage (with Notify)" thumbnail="true" border-effect="line"/>
</procedure>

<procedure title="Configure the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_targeting_preset.png" alt="Cast Ability (Targeting Preset)" thumbnail="true" border-effect="line"/>
</procedure>

## Ability Targeting Actor
Use this approach when the ability needs to **collect targets through the Gameplay Ability System's Targeting Actors**. 
This supports the **target actor types provided by GAS**, including custom subclasses, making it useful for abilities 
that already fit the standard GAS targeting flow.

<procedure title="Configure the Looping Animation Montage" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_montage_loop.png" alt="Cast Animation Montage (looping)" thumbnail="true" border-effect="line"/>
</procedure>

<procedure title="Create the Ability Targeting Actor" collapsible="true" default-state="collapsed">
</procedure>

<procedure title="Configure the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_confirm_targets.png" alt="Cast Ability (Confirm Targets)" thumbnail="true" border-effect="line"/>
</procedure>

## Cast Actor
Use this approach when the ability should **spawn a dedicated Cast Actor into the world**. The Cast Actor is responsible 
for collecting targets, usually through collision or overlap logic, and applying the Gameplay Effect set in the ability.

<procedure title="Create the Cast Actor" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_actor_graph.png" alt="Cast Actor Graph" width="780" thumbnail="true" border-effect="line"/>
    <step>
        <p>In your Blueprints folder, create a new <b>Cast Actor Blueprint</b> using <code>NinjaCombatCastActor</code> as the base class.</p>
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

<procedure title="Configure the Cast Ability" collapsible="true" default-state="collapsed">
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
        <p>Make sure <b>Successful Cast Effect Class</b> is set to the <b>Instant Cast</b> Gameplay Effect responsible for applying the Gameplay Cue.</p>
        <p>This is the same Gameplay Effect created for the <code>GA_Cast_TargetingPreset</code>, so no changes should be needed here.</p>
    </step>
</procedure>

## Targeted Cast Actor
Use this approach when the ability needs a targeting step before spawning the Cast Actor. The Ability Targeting Actor 
determines where the cast should happen, then the ability spawns a Cast Actor at that location to handle the final target 
collection and Gameplay Effect application.

<procedure title="Create the Ability Targeting Actor" collapsible="true" default-state="collapsed">
</procedure>

<procedure title="Configure the Cast Ability" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_cast_ability_confirm_cast.png" alt="Cast Ability (Confirm Cast)" thumbnail="true" border-effect="line"/>
</procedure>
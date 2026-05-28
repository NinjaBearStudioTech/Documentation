# Combat and Input
<primary-label ref="integrations"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="input-sec"/>

[**Ninja Combat**](cbt_overview.md) can benefit from GAS-related **Input Handlers** provided by [**Ninja Input**](ipt_overview.md).

## Forward Reference

Ninja Combat usually needs a **Forward Reference** to determine angles for directional abilities, such as the **Evade Ability**.
In parallel, Ninja Input might need a **Forward Reference** as well, usually to orient pawns in top-down perspectives.

Both systems can share the same Forward Reference. This is usually a **Scene Component**, such as an Arrow Component,
configured with **absolute rotation**.

<procedure title="Add a shared Forward Reference component" collapsible="true" default-state="expanded">
    <step>In the <b>Character Class</b>, create a new <b>Arrow Component</b>, parented to the <b>Root Component</b>, usually the character's <b>Capsule Component</b>.</step>
    <step>Add the <code>Combat.Component.ForwardReference</code> tag to the list of <b>Component Tags</b>.</step>
    <step>Add the <code>Input.Component.ForwardReference</code> tag to the list of <b>Component Tags</b>.</step>
    <step>Set the <b>Transform</b> to use <b>Absolute Rotation</b>, so the component is not affected by its parent rotation.</step>
    <step>Implement or override the Combat System interface function, <code>GetCombatForwardReference</code>, so it returns the <b>Arrow Component</b>.</step>
</procedure>

## Gameplay Abilities

Ninja Combat is built on the **Gameplay Ability System** and therefore it is very **ability-centric**. Ninja Input
provides Input Handlers for **ability activation** and **interruption** that can be used out-of-the-box to activate
**Combat Abilities**.

## Combo Inputs

The **Combo System** in Ninja Combat is designed to try to **activate a Combo Ability** while outside a **Combo Window**,
or send a **Gameplay Event** to **advance the combo**, if a Combo Window is open. This is a generic GAS-based design,
leveraging Gameplay Tags. Because of that, Ninja Input provides a **Combo Input Handler** that can be used out-of-the-box.

<procedure title="Configure Combat Combo Handlers" collapsible="true" default-state="expanded">
    <img src="integration_combat_input_combo.png" alt="Adding Combo Handlers" border-effect="line" thumbnail="true" width="720"/>
    <step>
        <p>Open your <b>Input Setup</b> and add one <b>Combat Combo</b> handler for each supported <b>Input Action</b> (e.g., Primary and Secondary Actions).</p>
    </step>
    <step>
        <p>Configure the <b>Activation Tags</b> so they match your <b>Gameplay Ability Tags</b>.</p>
        <p>Configure the <b>Advancement Tags</b> so they match your <b>Combo Event Tags</b>.</p>
    </step>
    <step>
        <p>If the <b>Input Buffer</b> is being used to enhance <b>Combo Windows</b>, check <b>Can Be Buffered</b>.</p>
        <p>Optionally, designate a <b>Buffer Channel Tag</b> for combo inputs.</p>
    </step>
    <step>
        <p>Configure your <b>Input Actions related to your Combo Inputs (e.g., Primary and Secondary Actions).</b></p>
        <p>Add <b>Triggered</b> to the list of <b>Triggered Events</b>, if necessary.</p>
    </step>
</procedure>

## Ability Targeting

The Gameplay Ability System supports **target confirmation and cancellation** by using Targeting Actors. While those
actors are active, the Ability System Component waits for additional input so it can gather the relevant targets.

Ninja Input provides Input Handlers compatible with this flow. However, by default, they only perform these targeting
operations at the **Ability System Component** level. Since Ninja Combat keeps track of the Targeting Actor currently
active, it makes it possible for these flows to also happen at the **Targeting Actor** level, which might be ideal in
some cases.

<procedure title="Integrate the Target Confirmation Handler" collapsible="true" default-state="expanded">
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="integration_combat_input_confirm.png" alt="Providing the Targeting Actor" border-effect="line" thumbnail="true" width="720"/>
        </tab>
        <tab title="C++" group-key="c++">
            <code-block lang="c++" src="integration_ability_confirmation_handler.h"/>
            <p><br/></p>
            <code-block lang="c++" src="integration_ability_confirmation_handler.cpp"/>
        </tab>
    </tabs>
    <step>
        <p>Create a new <b>Input Handler</b> based on <code>InputHandler_AbilityConfirm</code>.</p>
        <p>You can create Input Handlers in the Content Browser by clicking <b>Add</b>, then selecting <b>Ninja Bear Studio</b> &rarr; <b>Ninja Input</b> &rarr; <b>Input Handler</b>, and then selecting the base class.</p>
    </step>
    <step>Override the <code>GetAbilityTargetActor</code> function.</step>
    <step>Retrieve the <b>Target Manager Component</b> from the Input Manager's Pawn.</step>
    <step>Return the current <b>Ability Targeting Actor</b> by calling the Target Manager Component's <code>GetAbilityTargetActor</code> function.</step>
    <step>Optionally, adjust the <b>Ability Targeting Operation</b> to only execute at the actor level.</step>
</procedure>

<procedure title="Integrate the Target Cancellation Handler" collapsible="true" default-state="expanded">
    <step>Create a new <b>Input Handler</b> based on <code>InputHandler_AbilityCancel</code>.</step>
    <step>Repeat the same integration steps from the <b>Target Confirmation Handler</b>.</step>
    <step>Optionally, adjust the <b>Ability Targeting Operation</b> to only execute at the actor level.</step>
</procedure>

## Fire Intent

The [**Firearms Module**](cbt_concept_firearms.md) handles **Fire Intent** using functions from the Firearm Component.
These functions are responsible for requesting activation or deactivation of the Shoot Ability.

Once this handler is created, you can reuse it across different projects by adding it to the **Input Setup** and mapping
it to the appropriate **Input Action**. This handler expects an Input Action with both **Pressed** and **Released**
triggers.

<procedure title="Create the Fire Intent Handler" collapsible="true" default-state="expanded">
    <tabs group="sample">
        <tab title="Blueprint" group-key="bp">
            <img src="integration_combat_input_fire_intent.png" alt="Managing Fire Intent" border-effect="line" thumbnail="true" width="720"/>
        </tab>
        <tab title="C++" group-key="c++">
            <code-block lang="c++" src="integration_fire_intent_handler.h"/>
            <p><br/></p>
            <code-block lang="c++" src="integration_fire_intent_handler.cpp"/>
        </tab>
    </tabs>
    <step>
        <p>Create a new <b>Input Handler</b> based on <code>NinjaInputHandler</code>.</p>
        <p>You can create Input Handlers in the Content Browser by clicking <b>Add</b>, then selecting <b>Ninja Bear Studio</b> &rarr; <b>Ninja Input</b> &rarr; <b>Input Handler</b>, and then selecting the base class.</p>
    </step>
    <step>
        <p>Create a <b>Gameplay Tag Query</b> property, which will be used to retrieve the <b>active firearm</b>.</p>
    </step>
    <step>
        <p>Override <code>HandleTriggeredEvent</code> so it retrieves the <b>Firearm Component</b> by query.</p>
        <p>Then, based on the <b>input value</b>, invoke <code>TryOpenFire</code> or <code>TryCeaseFire</code>, respectively.</p>
        <tip>
            <p><b>Boolean Value Conversion</b></p>
            <p>The conversion function is an auto-cast function, meaning <b>you won't be able to find it in the context menu</b>.</p>
            <p>Instead, you must <b>drag</b> the Value parameter pin to the Branch's Condition parameter, to automatically create the conversion.</p>
        </tip>
    </step>
    <step>Add <code>Triggered</code> to the list of <b>Trigger Events</b>.</step>
    <step>Optionally, set <b>Manage Fire Intent</b> as the <b>Display Name</b>.</step>
</procedure>

## Disabling Input

**Ninja Input** can **block movement, camera and rotation input** based on the presence of the respective blocking tags.
This can be used by certain Gameplay Abilities to block specific input categories. For example:

1. The **Target Lock Ability** has tags to block **camera input**, since while locked on a target, the camera yaw should be locked, facing the target.
2. The **Opportunity Attack Ability** has tags to block input for **movement** and **camera**, so the participants in the paired animation remain in their predefined positions and the cinematic camera is not affected.

## Input Buffer

Ninja Input provides an **[Animation-Based Input Buffer](ipt_input_buffer.md)**, which is a common requirement for certain combat systems.
This allows players to be less precise with their inputs while still getting the desired outcome, which tends to create
a more responsive input feel. Common examples are:

1. Buffering an **attack input** pressed while the Evade Ability is still executing, so the attack starts as soon as the evade can transition.
2. Buffering a **combo input** pressed slightly before the Combo Window opens, so the next combo step still activates when the window becomes valid.
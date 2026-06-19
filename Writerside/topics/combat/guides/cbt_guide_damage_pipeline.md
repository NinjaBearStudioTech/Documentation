# Configuring Damage Pipelines
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

This guide shows how to create a Gameplay Effect that applies damage through the default Damage Execution, configure the
target's mitigation pipeline, and define the outcomes and cosmetics that run after damage is resolved.

For a deeper explanation of the systems and settings used by these examples, see the
[**related concepts**](cbt_concept_damage_and_mitigation.md).

## Prerequisites

### Combat Attributes

Make sure the source and target have the [**Combat Attribute Set**](cbt_reference_attributes.md), since the default Damage Execution
uses combat attributes such as **Base Damage**, **Critical Hit Chance**, **Block**, **Defense**, **Armor**, and
**Absorption**.

### Damage Ability

You need an ability or gameplay flow that can apply a damage Gameplay Effect to a target. You can use
[**Melee Attacks**](cbt_guide_melee_attacks.md), [**Ranged Attacks**](cbt_guide_ranged_attacks.md),
[**Cast Attacks**](cbt_guide_cast_flows.md), or any custom Gameplay Ability that applies a Gameplay Effect.

## Damage Gameplay Effect

You may have already done this while creating offensive abilities. Ninja Combat provides base damage Gameplay Effects
that you can use as a starting point, or you can create your own Gameplay Effect and add the Damage Execution to it.

<procedure title="Create the Gameplay Effect" collapsible="true" default-state="collapsed">
    <img src="cbt_guide_damage_gameplay_effect.png" alt="Gameplay Effect with Damage Execution" border-effect="line" thumbnail="true"/>
    <step>Create a new <b>Gameplay Effect</b> based on one of the provided Gameplay Effect classes, such as <code>CombatEffect_MeleeHit</code>.</step>
    <step>Set the effect <b>Duration Policy</b> to <b>Instant</b>, if needed.</step>
    <step>Add <code>CombatExecution_Damage</code> to the effect's <b>Executions</b>, if needed.</step>
    <step>Optionally, add <b>Calculation Modifiers</b> using <code>Combat.Data.Damage.Multiplier</code> to modify the <b>Base Damage</b>.</step>
    <step>Save the Gameplay Effect and add it to your <b>Gameplay Ability</b>.</step>
</procedure>

> **Attribute Overrides**
>
> By default, the Damage Execution retrieves values from the source's **Combat Attributes**. You can optionally override
> these using **Set By Caller Magnitudes**, with their respective data tags.
{style="note"}

## Defense Data

The target's **Defense Data Asset** controls the mitigation pipeline. Ninja Combat provides a generic Defense Data Asset
assigned to the Combat Manager by default, but projects can duplicate that asset or create new ones to adjust their
pipelines as needed.

> **Do Not Modify the Generic Defense Data**
>
> Do not modify the Defense Data Asset provided by Ninja Combat. Your changes will be lost when you update the plugin
> to a new version.
{style="warning"}

<procedure title="Create Defense Data" collapsible="true" default-state="collapsed">
    <step>In your Combat Data folder, create a new <b>Defense Data Asset</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Combat &rarr; Defense Definition.</step>
    <step>
        <p>Open the new Defense Data Asset and expand the <b>Mitigation Pipeline</b>.</p>
        <tip>
            <p><b>Default Pipeline</b></p>
            <p>Ninja Combat provides a default Mitigation Pipeline with common mitigation types used by combat-heavy projects, such as action RPGs.</p>
        </tip>
    </step>
    <step>Add or remove mitigations as needed, ordering them from broad cancellation checks to regular reductions.</step>
    <step>Assign the Defense Data Asset to the target's <b>Combat Manager</b>, using the <b>Defense Data</b> property.</step>
</procedure>

## Damage Data

The target's **Damage Data Asset** controls what happens after damage has been resolved. Ninja Combat provides a generic
Damage Data Asset assigned to the Combat Manager by default, but projects can duplicate that asset or create new ones to
adjust their pipelines as needed.

> **Do Not Modify the Generic Damage Data**
>
> Do not modify the Damage Data Asset provided by Ninja Combat. Your changes will be lost when you update the plugin
> to a new version.
{style="warning"}

<procedure title="Create Damage Data" collapsible="true" default-state="collapsed">
    <step>In your Combat Data folder, create a new <b>Damage Data Asset</b> using the Content Browser contextual menu: Ninja Bear Studio &rarr; Ninja Combat &rarr; Damage Definition.</step>
    <step>
        <p>Open the new Damage Data Asset and expand the <b>Damage Outcomes</b>.</p>
        <tip>
            <p><b>Default Outcomes</b></p>
            <p>Ninja Combat provides a default list of basic outcomes commonly shared across multiple projects.</p>
        </tip>
    </step>
    <step>Add or remove damage outcomes as needed. Order them from the most drastic outcomes to milder ones, so the pipeline can stop as early as possible.</step>
    <step>
        <p>Expand the <b>Damage Cosmetics</b>.</p>
        <tip>
            <p><b>Default Cosmetics</b></p>
            <p>By default, Ninja Combat enables weapon and projectile cosmetics through their respective interfaces.</p>
        </tip>
    </step>
    <step>Add or remove damage cosmetics as needed. Order is less important for cosmetics, since they cannot interrupt the execution chain.</step>
    <step>Assign the Damage Data Asset to the target's <b>Combat Manager</b>, using the <b>Damage Data</b> property.</step>
</procedure>
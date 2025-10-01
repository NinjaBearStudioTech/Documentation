# Interaction Animations
<primary-label ref="interaction"/>
<secondary-label ref="advanced"/>

You can play animations that match your interactions through the provided **State Tree task** and **Gameplay Ability**. 
Montages can be set **directly on the task** or **selected from a Chooser table**, making the system highly flexible.

In this chapter, we'll cover both options and several advanced usages—such as **character placement** at the Smart Object 
location and **adjusting/extending the animation layer**.

## Chooser Tables
By default, Ninja Interaction selects animations via a **Chooser Table** driven by the `NinjaInteractionAnimationCriteria` 
class. This class will provide the following selection properties:

| Property        | Description                                                           |
|-----------------|-----------------------------------------------------------------------|
| InteractionTags | Tags describing the interaction being executed (e.g., type, subtype). |
| SlotTags        | Runtime tags added to the Smart Object’s slot at configuration time.  |
| AbilityTags     | Additional tags contributed by the Gameplay Ability during execution. |

Before creating a Chooser table, make sure that all your interaction slots have enough metadata for proper selection.
They are also expected to have the required **Interaction Type Tag** set.

<procedure title="Adding Details to an Interaction Slot" collapsible="true" default-state="expanded">
    <step>Open your <b>Smart Object</b> definition.</step>
    <step>Locate the relevant <b>Interaction Slot</b> and add tags to the <b>Runtime Tags</b> container that help identify the correct animation for this slot/interaction.</step>
    <p><img src="int_adv_animation_so_tags.png" alt="Add runtime tags to the Smart Object slot" border-effect="line" thumbnail="true"/></p>
</procedure>

With slots enriched by metadata, create a Chooser Table that catalogs your character's animations.

<procedure title="Creating a Chooser Table" collapsible="true" default-state="expanded">
    <step>Create a new <b>Chooser Table</b> and select <b>Generic Chooser</b> as the <b>Chooser Type</b>.</step>
    <step>Set the <b>Result Class</b> to <b>Animation Montage</b>.</step>
    <step>In <b>Parameters</b>, add a <b>Class Parameter</b> using <code>NinjaInteractionAnimationCriteria</code> and set its <b>Direction</b> to <b>Input</b>.</step>
    <p><img src="int_adv_animation_chooser_table.png" alt="Chooser Table setup: Generic Chooser with Animation Montage result and Criteria input" border-effect="line"/></p>
</procedure>

Now add rows/entries to map criteria to the appropriate montages. You can match using simple tag sets or **Gameplay Tag Queries** for more advanced logic (AND/OR/NOT).

<p><img src="int_adv_animation_chooser_criteria.png" alt="Chooser criteria mapping to Animation Montages" border-effect="line" thumbnail="true"/></p>

## Interaction Animation Ability
This Gameplay Ability should be **granted by default** to the **Interaction Instigator**. It is usually **triggered by a 
Gameplay Event** sent from the State Tree task, but you may also activate it manually for custom scenarios.

This ability receives the **Chooser Table**, or a montage specified in a payload, and plays the appropriate animation. 
You can fine-tune its behavior via **properties** or by **overriding base functions** as needed.

<p><img src="int_adv_animation_ability.png" alt="Interaction Play Animation ability configuration" border-effect="line" thumbnail="true"/></p>

This ability also applies a **Gameplay Effect** during its execution. This is a powerful extension point to add **gameplay 
tags**, **cues**, and other transient logic tied to the animation window.

> **Additional Details**
> 
> For property, function and other details related to the **Play Interaction Animation Ability**, see the 
> related [reference page](int_ability_play_animation.md). 
{style="note"}

## State Tree Task
Interaction animations are usually played from the **State Tree** using the **Play Animation** task. Use this task in a 
dedicated state for **instant** interactions, or pair it with a preceding **Delay/Wait** node for **timed** interactions.

This task is straightforward and also lets you specify an **Animation Montage override**. When provided, the override is 
used instead of a Chooser selection—handy for unique scenarios or simpler projects that don’t need a Chooser Table.

<p><img src="int_adv_animation_state_tree_task.png" alt="Play Animation task in the State Tree" border-effect="line" thumbnail="true"/></p>


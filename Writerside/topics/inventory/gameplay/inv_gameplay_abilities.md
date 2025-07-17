# Gameplay Abilities
<primary-label ref="inventory"/>

<tldr> 
    <p><b>Summary: Gameplay Abilities</b></p> 
    <br/>
    <ul> 
        <li>Each item can provide one or more <b>Gameplay Abilities</b> to its owner.</li> 
        <li>Abilities follow a <b>shared class hierarchy</b> that provides built-in support for inventory, equipment, and animation integration.</li> 
        <li>Animations are selected dynamically using <b>Chooser Tables</b> based on weapon type, state, and other runtime data.</li>
    </ul> 
</tldr>

Ninja Inventory provides **Gameplay Abilities** that support common **inventory actions** such as **equip**, **drop**,
and **consume**. These abilities are designed to accomplish the following tasks:

1. Select the items that will be modified by the ability.
2. Play an **animation** that represents the action being executed.
3. Apply changes to the **item or equipment** as a result of the action.

## Ability Structure

All Ninja Inventory abilities derive from the shared base class: `UNinjaInventoryAnimationAbility`. This base introduces
several key properties that configure the ability’s behavior:

| Property                  | Description                                                                                                                  |
|---------------------------|------------------------------------------------------------------------------------------------------------------------------|
| `DefaultAnimationChooser` | Chooser Table used to determine the animation montage to play. Can be overridden via the provided interface.                 |
| `ActionTag`               | The verb describing the animation action (e.g., equip, store, consume). Can be used to match animation events and responses. |
| `AnimationCriteriaClass`  | Class used to build the Chooser Table criteria object.                                                                       |
| `ItemQuery`               | Optional query used to locate an item if none is provided in the activation payload or as a context object.                  |
| `TriggerPolicy`           | Defines when the action should occur: at animation start, upon a Gameplay Event, or when the animation ends.                 |
| `EventTag`                | The Gameplay Event that will trigger the action, used only if the trigger policy is set to "Gameplay Event".                 |

Inventory abilities often require their actions to occur at a specific point during execution. To support varying project
needs, Ninja Inventory introduces the concept of a **Trigger Policy**. Supported values include:

- **Animation Starts**: The action is triggered as soon as the animation begins.
- **Gameplay Event**: The action is triggered when a specific Gameplay Event, defined by the **Event Tag**, is received.
- **Animation Ends**: The action is triggered once the animation has finished.

## Item Selection

The base ability also handles **item selection**, determining which items will be modified by the ability's logic. Items
are collected per ability execution and can be obtained in one of two ways:

- Provided directly via an **Activation Trigger Event payload**, as optional context objects.
- Queried from the inventory using the **Item Query** defined in the ability, when no payload items are provided.

> **Filtering Selected Items**
>
> You can apply additional filtering by overriding `IsEligibleItem`. This function is a great place to validate fragments, 
> item traits, or other custom conditions.
{style="note"}

When extending Inventory Abilities, you can respond to various lifecycle events by overriding the following Blueprint or C++ functions:

| Function                 | Description                                                                                                                                                     |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `HandleEventReceived`    | Handles the Gameplay Event used as a trigger. Executes item actions on payload items or all items gathered during activation.                                   |
| `HandleMontageStarted`   | Called when the ability animation starts. Executes the action if the trigger policy is set to "Animation Starts".                                               |
| `HandleMontageCancelled` | Called if the animation is canceled. Cancels the ability by default, but can be extended for fallback logic.                                                    |
| `HandleMontageCompleted` | Called when the animation completes. Executes the action if the trigger policy is set to "Animation Ends".                                                      |
| `HandleMissingItems`     | Called when no items were collected after filtering. Cancels the ability by default.                                                                            |
| `HandleMissingMontage`   | Called when items were found, but no valid Animation Montage was selected by the Chooser Table.                                                                 |
| `ExecuteItemAction`      | Executes the core logic of the ability on a selected item. Override this function to define the actual item transformation.                                     |

> **Default Function Behaviors**
>
> Be mindful of default behavior when overriding these functions. Call `super` only when the base implementation supports 
> your intended outcome.
{style="note"}

## Chooser Table

All inventory-related abilities that play an **Animation Montage** use a **Chooser Table** to dynamically select the
correct animation based on item traits and context.

<procedure title="Creating the Animation Chooser Table" collapsible="true" default-state="expanded">
    <step>Create a new asset from → <b>Miscellaneous</b> → <b>Chooser Table</b>.</step>
    <step>Select <b>Generic Chooser</b> as the <b>Chooser Type</b>.</step>
    <step>Set the <b>Result Type</b> to <code>Object of Type</code> and <b>Result Class</b> to <code>AnimMontage</code>.</step>
    <step>Add a new entry under <b>Parameters</b>, using <code>Class Parameter</code> as the type.</step>
    <step>Set the <b>Class</b> to <code>NinjaInventoryAnimationCriteria</code> and <b>Direction</b> to <code>Input</code>.</step>
    <img src="inv_gameplay_chooser_create.png" alt="Animation Chooser Table Creation" border-effect="line"/>
</procedure>

### Chooser Source Interface

While Inventory Abilities support setting a default Chooser Table, some avatars may require dedicated tables (e.g., due 
to skeleton or animation differences).

To support this, avatars can implement the `InventoryAnimationChooserSourceInterface`.

By overriding `GetInventoryAnimationChooser` and returning a valid Chooser Table, this value will take precedence over 
the default set on the ability.

## Animation Criteria

The **Criteria Object**, `NinjaInventoryAnimationCriteria`, is passed to the Chooser Table to determine which animation 
to play. It contains properties representing the **Gameplay Ability**, **Item**, and **Action Context**:

| Property      | Description                                                                            |
|---------------|----------------------------------------------------------------------------------------|
| `AbilityTags` | Tags assigned to the ability requesting the animation.                                 |
| `ActionTags`  | Tags representing the contextual action (e.g., equip, consume).                        |
| `ItemTags`    | All gameplay tags from the item targeted by the action.                                |

Chooser Tables evaluate this data using **Tag Matchers** or **Gameplay Tag Queries** to select the correct **AnimMontage**.

<img src="inv_gameplay_chooser_setup.png" alt="Animation Chooser Table Setup" border-effect="line"/>

In the example above:

- **Item Tags** use a **Gameplay Tag Query**, allowing multiple item types (e.g., rifles, shotguns) to share an animation.
- **Action Tags** use a **Tag Matcher**, allowing animation selection specific to actions like **equip**.

### Extending the Criteria
<secondary-label ref="advanced"/>

Because the criteria is a standard `UObject`, you can extend it with additional properties to support more advanced
selection logic.

<procedure title="Enabling a Custom Animation Criteria" collapsible="true" default-state="expanded">
    <step>Create a Blueprint or C++ class that inherits from <code>NinjaInventoryAnimationCriteria</code>.</step>
    <step>Add any custom parameters needed for your animation selection logic.</step>
    <step>Assign the new class to <code>AnimationCriteriaClass</code> in the Inventory Ability.</step>
    <step>Override <code>EnhanceAnimationCriteria</code> in the ability (Blueprint or C++) to set criteria values.</step>
    <step>Update the <b>Chooser Table</b> to use the custom criteria class.</step>
</procedure>

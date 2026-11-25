# Grant Starting Attributes and Abilities
<primary-label ref="gas"/>
<secondary-label ref="guide"/>

Give a character 25 energy and a Recover ability that restores 50. Use a character from [First Steps](gas_first_steps.md) and an Attribute Set supplied by your project. The example uses an `Energy` attribute declared by `UTrainingAttributeSet`. Substitute your set and attribute names throughout.

<procedure title="Start the character with 25 energy">
    <step><p>Create a Data Table with the <b>AttributeMetaData</b> row structure. Name the row <code>TrainingAttributeSet.Energy</code> and set <b>Base Value</b> to 25. The part before the dot is the reflected name of the class that declares the attribute. For a native class, omit the C++ prefix <code>U</code>.</p></step>
    <step><p>Open the character's G.A.S. Setup asset. Under <b>Default Attribute Sets</b>, add your set, assign the table to <b>Attribute Table</b>, and leave <b>Instantiation Scope</b> at <b>Both</b>. If your set clamps energy to a maximum, initialize that maximum to at least 75.</p></step>
</procedure>

<procedure title="Grant a recovery move">
    <step><p>Create an instant Gameplay Effect named <code>GE_RecoverEnergy</code>. Add a modifier for <b>Energy</b>, choose the additive operation, and set the magnitude to 50.</p></step>
    <step><p>Create <code>GA_Recover</code> as a Blueprint based on <code>NinjaGASGameplayAbility</code>. On <b>Activate Ability</b>, call <b>Commit Ability</b>. On success, use <b>Apply Gameplay Effect to Owner</b> with <code>GE_RecoverEnergy</code> at level 1. End the ability on both the success and failure paths.</p></step>
    <step><p>Add <code>GA_Recover</code> to the bundle's <b>Default Gameplay Abilities</b> at level 1. In a standalone test, use <b>Try Activate Ability by Class</b> on the character's component from a test button or a level event after initialization.</p></step>
</procedure>

## React to a Grant

For a passive move, give a `NinjaGASGameplayAbility` the exact asset tag `Ability.Passive`. The base ability tries to activate it when its avatar is set. A permanent starting bonus that only changes a value or grants a tag can go directly in **Default Gameplay Effects**.

For a C++ ability bar, read the abilities already granted when the bar opens, then listen to `OnAbilityGiven()` on the Ninja component for later grants. Its callback receives `const FGameplayAbilitySpec&`. Use the spec's class to choose the icon and its handle to identify the grant. Remove the delegate binding when the bar closes or changes components.

## Try It in Play

Inspect the character with `showdebug abilitysystem`. Energy should read 25 before you press the button, and the abilities list should already include `GA_Recover`. Activate it once and check for 75. If you see the grant but energy stays at 25, check the effect's target attribute and whether the ability committed. If energy starts at zero, check the table's row name and which bundle is assigned.

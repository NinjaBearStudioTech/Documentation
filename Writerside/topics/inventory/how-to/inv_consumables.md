# Create and Use Consumables
<primary-label ref="inventory"/>
<secondary-label ref="how-to"/>

In this how-to, we will configure a Health Potion, which is a Consumable Item responsible for applying a Gameplay Effect
to its owner, once the Consume Operation is triggered.

<procedure title="Create a Curve Table for the Potion" collapsible="true">
    <step>In your Content Browser, create a new <b>Curve Table</b> and set the Interpolation Type to <b>Linear</b>. For this example, we'll name it "<code>TB_Scale_Consumables</code>".</step>
    <step>Open your new Curve Table and click the <b>Add</b> button to create a new curve. In this example, we'll name it "<code>Potion.Health</code>".</step>
    <step>This curve contains <b>Level over Magnitude</b>, add as many values as you find necessary, by clicking the <b>Append Column</b> button.</step>
    <step>Save the Curve Table.</step>
</procedure>

<procedure title="Create the Gameplay Effect" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_HealthPotion</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and make sure it's <b>Duration Policy</b> is set to <code>Instant</code>. Then, add a new <b>Modifier</b> entry.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>Health</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>Set the <b>Modifier Operation</b> to <code>Add</code>.</step>
    <step>Set the <b>Magnitude Calculation Type</b> to <code>Scalable Float</code>.</step>
    <step>Set the <b>Magnitude</b> to <code>1.0</code>, the <b>Curve Table</b> to <code>TB_Scale_Consumables</code> and the <b>Curve</b> to <code>Potion.Health</code>.</step>
    <step>Compile and save the Gameplay Effect.</step>
</procedure>

<procedure title="Configure the Consumable Item" collapsible="true">
    <step>Create or select the Item Definition that will be used for your potion. In this example, we'll use the <code>Consumable_Potion_Health</code> item.</step>
    <step>Add the <code>Consumable</code> fragment to the <b>Fragments</b> list.</step>
    <step>In the Consumable Fragment, set the <b>Charges</b> to <code>Stack Fragment</code> and the <b>Effect Class</b> to <code>GE_HealthPotion</code>.</step>
    <step>Save the Item Definition.</step>
    <tip>
        <p><b>Setting the Charges strategy</b></p>
        <p>You can choose other types of Charges if that makes more sense to you. A <i>Flask</i>, for example, could use a Gameplay Attribute instead.</p> 
    </tip>
</procedure>

<procedure title="Prepare the Animation Montage" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_HealthPotion</code>".</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Create the Consume Gameplay Ability" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_HealthPotion</code>".</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Add the Item to the Inventory" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_HealthPotion</code>".</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
</procedure>

<procedure title="Execute the Consume Operation" collapsible="true">
    <step>Open your Character Blueprint or any other location where you are handling Player inputs.</step>
    <step>Create a new <b>Consume Operation</b>, using the <b>Inventory Function Library</b>.</step>
    <step>Retrieve the <b>Inventory Manager</b> from the character, using the <b>Inventory Function Library</b></step>
    <step>Request the execution of the Consume Fragment Operation to the Inventory Manager.</step>
    <step>Compile and save your Blueprint.</step>
    <note>
        <p><b>Multiplayer Events</b></p>
        <p>The Consume Operation is a Gameplay Event and as such, in multiplayer games, it must be triggered on the Server and Local Client.</p>
        <p>Make sure to account for that in your input handling. The <a href="ipt_overview.md">Ninja Input</a> plugin can help you with that!</p>
    </note>
</procedure>

# Create and Use Consumable Items
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>

This how-to will enhance the <b>Health Potion</b> to add the actual <b>consumable logic</b>.

## Part 1: Configuring the Consumable

<procedure title="Create a Curve Table for the Potion" collapsible="true">
    <step>In your Content Browser, create a new <b>Curve Table</b> and set the Interpolation Type to <b>Linear</b>. For this example, we'll name it "<code>TB_Scale_Consumables</code>".</step>
    <step>Open your new Curve Table and click the <b>Add</b> button to create a new curve. In this example, we'll name it <code>Potion.Health</code>.</step>
    <step>This curve contains <b>Level over Magnitude</b>, add as many values as you find necessary, by clicking the <b>Append Column</b> button.</step>
    <step>
        <p>Once you are done, you should have a similar Curve Table. Feel free to add others, if you like!</p>
        <img src="inv_consumable_scale_table.png" alt="Consumable Level Curve" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create the Gameplay Effect" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_HealthPotion</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and make sure it's <b>Duration Policy</b> is set to <code>Instant</code>. Then, add a new <b>Modifier</b> entry.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>Health</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>Set the <b>Modifier Operation</b> to <code>Add</code>.</step>
    <step>Set the <b>Magnitude Calculation Type</b> to <code>Scalable Float</code>.</step>
    <step>Set the <b>Magnitude</b> to <code>1.0</code>, the <b>Curve Table</b> to <code>TB_Scale_Consumables</code> and the <b>Curve</b> to <code>Potion.Health</code>.</step>
    <step>
        <p>Once you are done, your Gameplay Effect should look like this.</p>
        <img src="inv_consumable_healing_effect.png" alt="Healing Gameplay Effect" border-effect="line"/>
    </step>
</procedure>

<procedure title="Configure the Consumable Item" collapsible="true">
    <step>Create or select the Item Definition that will be used for your potion. In this example, we'll use the <code>Consumable_Potion_Health</code> item.</step>
    <step>Add the <code>Consumable</code> fragment to the <b>Fragments</b> list.</step>
    <step>In the Consumable Fragment, set the <b>Charges</b> to <code>Stack Fragment</code> and the <b>Effect Class</b> to <code>GE_HealthPotion</code>.</step>
    <step>Disable the option <b>Use Item Level as Effect Level</b>.</step>
    <step>
        <p>Once you are done, your Health Potion Definition should look like this.</p>
        <img src="inv_consumable_item_fragment.png" alt="Health Potion Consumable Fragment" border-effect="line"/>
    </step>
    <tip>
        <p><b>Setting the Charges strategy</b></p>
        <note>You can choose other types of Charges if that makes more sense to you. A <i>Flask</i>, for example, could use a Gameplay Attribute instead.</note> 
    </tip>
</procedure>

## Part 2: Configuring the Gameplay

<procedure title="Configure your Animation Montage" collapsible="true">
    <step>Select the <b>Animation Sequence</b> representing the <b>Activate</b> action. Create an <b>Animation Montage</b> from it and name it <code>M_ConsumePotion</code>.</step>
    <step>Open your Animation Montage and add the <b>Consumable Animation Notify State</b> to the frames where the consumable should be displayed.</step>
    <step>Set the appropriate <b>Mesh Type</b> for your scenario, the <b>Mesh Asset</b>, the <b>Slot Tag</b> in your character and the <b>Attachment Socket</b></step>
    <step>Add any other <b>Slots to Hide</b> as well, in this case, we'll hide the Main Weapon, represented by the tag <code>Equipment.Slot.MainHand</code></step>
    <step>
        <p>Once you are done, your Animation Notify State should be similar to this.</p>
        <img src="inv_consumable_animation_notify.png" alt="Consumable Notify" border-effect="line"/>
        <tip>This Animation Notify is a <b>work-in-progress</b> and in the future it will allow dynamic meshes.</tip>
    </step>
</procedure>

<procedure title="Update the Animation Table" collapsible="true">
    <step>Open the <code>TB_Inventory_Animations</code> table, containing your Inventory Animations.</step>
    <step>Add another row and set the <b>Montage To Play</b> to <code>M_ConsumePotion</code>.</step>
    <step>
        <p>Set the <b>Montage Query</b> to be compatible any items marked as <b>Potions</b>.</p>
        <img src="inv_consumable_animation_query.png" alt="Store Weapon Montage Query" border-effect="line"/>
    </step>
</procedure>

<procedure title="Create the Consume Equipment Ability" collapsible="true">
    <step>In your <b>Content Browser</b>, navigate to your <b>ability folder</b> and create a new <b>Gameplay Ability</b> using <code>UInventoryAbility_ConsumeItem</code> as the parent. Name it <code>GA_Common_Consume</code>.</step>
    <step>
        <p>Open your new ability and configure the <b>Consumable Query</b> to find any <b>Consumable Items</b> in a <b>Consumable Slot</b>.</p>
        <img src="inv_consumable_ability_query.png" alt="Consume Ability Query" border-effect="line"/>
    </step>
    <step>Set <code>TB_Inventory_Animations</code> as the <b>Montage Table</b>.</step>
    <step>Add <code>Ability.Consume</code>.</step>
    <step>
        <p>When you are done, your Ability should look like this:</p>
        <img src="inv_consumable_ability.png" alt="Consume Ability" border-effect="line"/>
    </step>
</procedure>

<procedure title="Execute the Consume Operation" collapsible="true">
    <step>Open your Character Blueprint or any other location where you are handling Player inputs.</step>
    <step>Create a new <b>Consume Operation</b>, using the <b>Inventory Function Library</b> to create the Payload.</step>
    <step>Retrieve the <b>Inventory Manager</b> from the character, using the <b>Inventory Function Library</b></step>
    <step>Using the Inventory Manager, obtain the consumable item using an item query.</step>
    <step>Request the execution of the Consume Fragment Operation to the Inventory Manager.</step>
    <step>Compile and save your Blueprint.</step>
    <note>
        <p><b>Multiplayer Events</b></p>
        <p>The Consume Operation is a Gameplay Event and as such, in multiplayer games, it must be triggered on the Server and Local Client.</p>
        <p>Make sure to account for that in your input handling. The <a href="ipt_overview.md"/> plugin can help you with that!</p>
    </note>
</procedure>

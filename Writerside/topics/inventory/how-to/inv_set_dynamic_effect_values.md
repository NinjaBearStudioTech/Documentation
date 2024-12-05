# Set Dynamic Values to Equipment Gameplay Effects
<primary-label ref="inventory"/>
<secondary-label ref="guide"/>
<secondary-label ref="advanced"/>

In this how-to, we will create an Item Fragment that transfer its values all the way to an Equipment Gameplay Effect.
Please make sure to check related topics at the end for additional details.

<procedure title="Create the Gameplay Effect" collapsible="true">
    <step>In your Content Browser, create a new <b>Gameplay Effect</b> Blueprint, using <code>GameplayEffect</code> as the base class. For this example, we'll name it "<code>GE_SwordDamage</code>".</step>
    <step>Open your new Gameplay Effect Blueprint and, in the Class Defaults tab, add a new <b>Modifier</b>.</step>
    <step>Select the <b>Attribute</b> that you want to modify. For this example, we'll use the <code>BaseDamage</code> Attribute, from <a href = "cbt_overview.md">Ninja Combat</a>.</step>
    <step>In the <b>Modifier Magnitude</b> section, select <code>Set By Caller</code> as the value for <b>Magnitude Calculation Type</b>.</step>
    <step>Set the Data Tag that will be retrieved from the Item Fragment. For this example, we'll use <code>Combat.Data.Damage</code>.</step>
    <step>Set the <b>Duration Policy</b> to <code>Infinite</code>.</step>
    <step>Compile and save your Gameplay Effect Blueprint.</step>
    <img src="inv_set_dynamic_effect_values_001.png" alt="Create the Gameplay Effect" width="800"/>
</procedure>

<procedure title="Set the Gameplay Effect to the Equipment" collapsible="true">
    <step>Open the <b>Equipment Definition Data Asset</b> that will use the <code>GE_SwordDamage</code> Gameplay Effect. In this example, it will be assigned to a Sword.</step>
    <step>Expand the <b>State Configuration</b> for the <code>Activated</code> State and add a new entry to the <b>Gameplay Effects</b> list.</step>
    <step>Set the <code>GE_SwordDamage</code> to the <b>Gameplay Effect Class</b>.</step>
    <step>Optionally, check the <b>Use Item Level as Effect Level</b> option. This is useful if you plan to scale the Gameplay Effect based on the Item Level.</step>
    <step>Save your Equipment Definition Data Asset.</step>
    <img src="inv_set_dynamic_effect_values_002.png" alt="Set the Gameplay Effect to the Equipment" width="800"/>
</procedure>

<procedure title="Create the Item Fragment" collapsible="true">
    <step>In your Content Browser, create a new <b>Item Fragment</b> Blueprint, using <code>NinjaInventoryFragment</code> as the base class. For this example, we'll name it "<code>Fragment_Damage</code>".</step>
    <step>Open your new Item Fragment Blueprint and create a new <b>Variable</b>, name it <code>Magnitudes</code> and set its type to <code>Gameplay Tag</code>.</step>
    <step>In the Variable Details panel, make the new variable a <b>Map</b> container, and set the map's value type to <code>float</code>.</step>
    <step>Mark the variable as <b>Instance Editable</b>. You can also set a <b>Category</b> for it if you like.</step>
    <step>Compile and save your Item Fragment Blueprint.</step>
    <img src="inv_set_dynamic_effect_values_003.png" alt="Create the Item Fragment" width="800"/>
</procedure>

<procedure title="Configure the Item Fragment Class Settings" collapsible="true">
    <step>In the Item Fragment Blueprint, go to the <b>Class Settings</b> tab and set the <b>Blueprint Display Name</b> to <code>Weapon Damage</code>.</step>
    <step>Still in the <b>Class Settings Tab</b>, under <b>Interfaces</b> add the <code>Item Magnitude Value Interface</code> to the list of <b>Implemented Interfaces</b>.</step>
    <step>You should see the <code>Item Magnitude Value Interface</code> added to list of <b>Interfaces</b> on the left, along with its two functions: <code>Get Magnitude for Data Tag</code> and <code>Get All Magnitude Values</code>.</step>
    <step>Compile and save your Item Fragment Blueprint.</step>
    <img src="inv_set_dynamic_effect_values_004.png" alt="Configure the Item Fragment Class Settings" width="800"/>
</procedure>

<procedure title="Implement the Item Magnitude Value Interface" collapsible="true">
    <step>In the Item Fragment Blueprint, double-click the <code>Get Magnitude for Data Tag</code> function, in the list of available Interface Methods. This will create that function with an empty body.</step>
    <step>Implement the function, so it will try to find the Data Tag in the <code>Magnitudes</code> map. Return the float value.</step>
    <step>Create a <code>Branch</code> node connected to the map's output, ensuring that the correct value is only returned if it was actually found.</step>
    <step>If the value was not found, return the <b>Default Value</b> that has been provided to the function.</step>
    <step>Compile and save your Item Fragment Blueprint.</step>
    <img src="inv_set_dynamic_effect_values_005.png" alt="Implement the Item Magnitude Value Interface" width="800"/>
    <step>In the Item Fragment Blueprint, double-click the <code>Get All Magnitude Values</code> function, in the list of available Interface Methods. This will create that function with an empty body.</step>
    <step>Implement the function, return the <code>Magnitudes</code> map.</step>
    <step>Compile and save your Item Fragment Blueprint.</step>
    <img src="inv_set_dynamic_effect_values_006.png" alt="Implement the Item Magnitude Value Interface" width="800"/>
</procedure>

<procedure title="Configure the Item Definition Data" collapsible="true">
    <step>Open the <b>Item Definition Data Asset</b> that will use the new <b>Damage Fragment</b>. In this example, it will be assigned to a Sword.</step>
    <step>Add a new fragment and select the <code>Damage Magnitude</code> Fragment, which is the name defined for the Fragment a few steps before.</step>
    <step>Add a new element to the <b>Magnitudes</b> map, setting the key value to <code>Combat.Data.Damage</code>, which matches the Gameplay Effect.</step>
    <step>Set the value to any value that you want to use to represent the Damage. In this example, it's set to <code>10</code>.</step>
    <step>Save your Item Definition Data Asset.</step>
    <img src="inv_set_dynamic_effect_values_007.png" alt="Configure the Item Fragment Class Settings" width="800"/>
</procedure>

Now you are ready to test your setup. Once the Item is assigned and its Equipment's state is set to Activated, the
Gameplay Effect will be granted, with the value configured in the Item Definition.

<seealso style="cards">
    <category ref="related">
        <a href="inv_items_and_fragments.md" summary="Concepts about Items, Fragments and Operations."/>
        <a href="inv_effects.md" summary="Gameplay Effects and their role in the Inventory System."/>
    </category>
</seealso>
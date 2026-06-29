# Adding Gameplay Attributes
<primary-label ref="integrations"/>
<secondary-label ref="gas-sec"/>
<secondary-label ref="combat-sec"/>
<secondary-label ref="inventory-sec"/>

[**Ninja G.A.S.**](gas_overview.md) provides **Ability Bundles** that can be used to register **Gameplay Attributes**, 
from plugins like [**Ninja Combat**](cbt_overview.md) and [**Ninja Inventory**](inv_overview.md). 

> **Asset Manager**
> 
> Since Ability Bundles are **Primary Data Assets**, make sure to [register them with the **Asset Manager**](asset_manager.md) 
> before getting started.

<procedure title="Create Initialization Tables" collapsible="true" default-state="collapsed">
    <step>
        <p>Download the <b>JSON data</b> for attribute sets you will initialize.</p>
        <p>You can find them in the Gameplay Attribute Pages for each plugin.</p>
    </step>
    <step>
        <p>In your project, create an <b>Attributes</b> folder and drop each JSON file.</p>
        <p>When asked about the <b>Table Structure</b>, select <code>AttributeMetaData</code>.</p>
    </step>
    <step>Save each <b>Data Table</b> with proper names. Optionally edit the attributes as needed.</step>
</procedure>

<procedure title="Add and Initialize Attribute Sets" collapsible="true" default-state="collapsed">
    <step>
        <p>Navigate to the folder configure in your Asset Manager, for the <code>AbilityBundleData</code> data type.</p>
    </step>
    <step>
        <p>Create a new <b>Ability Bundle</b> by clicking <b>Add</b> &rarr; <b>Ninja Bear Studio</b> &rarr; <b>Ninja G.A.S.</b> &rarr; <b>Ability Bundle</b>.</p>
    </step>
    <step>
        <p>In the new Ability Bundle add a new entry to <b>Default Attribute Sets</b>. Set the <b>Attribute Set Classes</b> and their respective <b>Attribute Tables</b>.</p>
    </step>
    <step>
        <p>Navigate to your <b>Ability System Avatar</b> Blueprint, navigate to the <b>Ability System Component</b> and set the Ability Bundle as the <b>Default Ability Setup</b>.</p>
        <note>The Ability System Component must be the one provided by Ninja GAS, <code>NinjaGASAbilitySystemComponent</code>, or a subclass.</note>
    </step>
</procedure>
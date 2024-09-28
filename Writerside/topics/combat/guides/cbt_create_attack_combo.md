# Create an Attack Combo
<primary-label ref="combat"/>
<secondary-label ref="how-to"/>

This how-to will show you how to expand the previous **Light Ability** into a **Combo**.

<procedure title="Create the Animation Montages" collapsible="true">
    <step>Create all Animation Montages for the combo attacks.</step>
    <step>Add the Melee Scan Notify, as done before for the previous attacks.</step>
    <step>Add the Combo Window Notify State to the frames that will allow the next attack.</step>
</procedure>

<procedure title="Create additional Attack abilities" collapsible="true">
    <step>Create all the remaining Abilities, following the same steps from the first one.</step>
    <step>Instead of the original activation tag, <code>Ability.Attack.Primary</code>, organize these attacks to follow the pattern: <code>Ability.Attack.Primary.1</code>, <code>Ability.Attack.Primary.2</code>, <code>Ability.Attack.Primary.3</code> and so on.</step>
    <step>Add all these abilities to your character.</step>
</procedure>

<procedure title="Create your Combo State Tree" collapsible="true">
    <step>Create a new State Tree using the NinjaCombatComboComponentSchema.</step>
</procedure>

<procedure title="Create your Combo Data Asset" collapsible="true">
</procedure>

<procedure title="Create your Combo ability" collapsible="true">
</procedure>

<procedure title="Add the Combo Manager component" collapsible="true">
    <step>
        <p>Add the Combo Manager component to your character</p>
        <img src="cbt_combo_manager_add_component.png" alt="Combo Manager Component" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>Implement the Combat System Interface function to provide the Combo Manager.</p>
        <img src="cbt_combo_manager_implement_getter.png" alt="Combo Manager Component" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

<procedure title="Check your progress" collapsible="true">
</procedure>

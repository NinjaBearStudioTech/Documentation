# Configuring Player Vitals Widget
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

## Player Vitals

ViewModels are instantiated and used by widgets and can even be configured to exchange data between themselves. You can
find a complete list of ViewModels available in Ninja Combat, but here are a few common usage examples:

- Setting **player vital attributes**, using **progress bars** or **text**.
- Displaying **damage applied to enemies**, including accumulating damage applied over time.
- Tracking active **Status Effects** from **Gameplay Effects** applied to the player or to enemies.

<procedure title="Configuring a Player Health Bar" collapsible="true" default-state="expanded">
    <step>
        <p>Create a widget with a <b>progress bar</b> that will be used to represent the player's <b>health</b>.</p>
        <img src="cbt_advanced_ui_health_bar.png" alt="Health Bar" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>In the <b>ViewModels</b> tab, add the <b>Vitals ViewModel</b> to your widget and set its Creation Type to <b>Resolver</b>. Select the <b>Ninja Combat ViewModel Resolver</b> class.</p>
        <img src="cbt_advanced_ui_vitals_view_model.png" alt="Vitals ViewModel" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>ViewModel Panel</b></p>
            <p>ViewModels are added to your widget in the ViewModel panel. If necessary, it can be opened via <code>Window</code>&RightArrow;<code>ViewModels</code>.</p>
        </tip>
    </step>
    <step>In your widget <b>Hierarchy</b> panel, select the <b>Progress Bar</b> component. We will create a <b>View Binding</b> for it next.</step>
    <step>
        <p>In the <b>View Bindings</b> panel, click <b>Add Widget</b>, select the <b>percent</b> property from your Progress Bar, and bind it to the <b>Health Percent</b> property, from the <b>Combat Vitals</b> ViewModel.</p>
        <img src="cbt_advanced_ui_vitals_bindings.png" alt="Vitals Bindings" border-effect="line" thumbnail="true"/>
        <tip>
            <p><b>View Bindings Panel</b></p>
            <p>View Bindings are configured the View Bindings panel. If necessary, it can be opened via <code>Window</code>&RightArrow;<code>View Bindings</code>.</p>
        </tip>
    </step>
</procedure>

> **Creation Type**
>
> If you need to define a different **creation type**, Combat View Models can be initialized to any combatant via the
> `InitializeCombatViewModel` function, introduced by the base ViewModel class in Ninja Combat, `NinjaCombatViewModel`.

You can also use **Conversion Functions** to perform common conversions such as **float to text**. Unreal Engine already
provides many of these functions.

<procedure title="Converting Current and Maximum Health" collapsible="true" default-state="expanded">
    <step>
        <p>In your <b>Health Widget</b> add <b>Text Block</b> components to represent the player's <b>current and maximum health</b>.</p>
        <img src="cbt_advanced_ui_cur_max_health_text.png" alt="Current and Maximum Health" border-effect="line" thumbnail="true"/>
    </step>
    <step>Create a <b>View Binding</b> for the <b>Current Health</b>, but using the <b>To Text(Float)</b> Conversion Function.</step>
    <step>
        <p>Configure the conversion details, binding the <b>Value</b> to the <b>Current Health</b> property, from the <b>Combat Vitals</b> ViewModel.</p>
        <img src="cbt_advanced_ui_conversion_functions.png" alt="Conversion Functions" border-effect="line" thumbnail="true"/>
    </step>
    <step>Repeat the steps for the <b>Maximum Health</b> Text Block, binding it to the <b>Max Health Total</b> property, from the <b>Combat Vitals</b> ViewModel.</step>
</procedure>

> **Binding to Functions**
>
> Similarly to the conversion functions above, you can bind ViewModel data to any **Callable function** with an
> **input parameter matching the ViewModel’s property type**.

## Enemy Vitals
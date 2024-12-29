# Track Player Attributes
<secondary-label ref="guide"/>

The combat system provides **Viewmodels** to support your **user interface**. Let's get started with that topic, by
creating some progress bars that will track the player's main attributes: **Health**, **Stamina**, and **Magic**.

<procedure title="Review your Player attributes" collapsible="true">
    <step>Open your <b>Combat Attribute Data Table</b> for the Player. This was configured before, while configuring GAS.</step>
    <step>Check your <b>Health</b> <b>Stamina</b>, and <b>Magic</b>, to ensure they have valid values.</step>
</procedure>

<procedure title="Create the Player Attributes Widget" collapsible="true">
    <step>Create a new widget, based on <code>NinjaCombatBaseWidget</code>.</step>
    <step>In the <b>Designer</b> tab, add a <b>Vertical Box</b> and three <b>Progress Bars</b>, with <b>Size</b> boundaries.</step>
    <step>
        <p>In the <b>Viewmodels</b> tab, add a <code>ViewModel_CombatVitals</code> entry. In the <b>Details</b> panel, set the <b>Creation Type</b> to <b>Create Instance</b>.</p>
        <img src="p02g03_widget_design.png" alt="Widget Design" thumbnail="true" border-effect="line" width="600"/>
        <tip>Feel free to create any design that is appropriate for your game, but make sure to use a Progress Bar for now.</tip>  
        <tip>If you cannot see the Viewmodel or View Bindings tab, enable them in the <b>Window</b> menu.</tip>
    </step>
    <step>
        <p>In the <b>View Bindings</b> tab, set the following bindings</p>
        <ul>
            <li><b>Health Bar</b>: HealthBar::Progress Value &larr; ViewModel_CombatVitals::Health Percent</li>
            <li><b>Stamina Bar</b>: StaminaBar::Progress Value &larr; ViewModel_CombatVitals::Stamina Percent</li>
            <li><b>Magic Bar</b>: MagicBar::Progress Value &larr; ViewModel_CombatVitals::Magic Percent</li>
        </ul>
        <img src="p02g03_view_bindings.png" alt="View Bindings" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>
        <p>Go to the <b>Graph</b> tab, and implement the <code>Construct</code> event, setting the <b>Player Pawn</b> as the <b>Combat Actor</b>.</p>
        <img src="p02g03_player_widget_graph.png" alt="Widget Graph" thumbnail="true" border-effect="line" width="600"/>
    </step>
</procedure>

<procedure title="Create the Gameplay Widget" collapsible="true">
    <step>Create a new User Widget that will be used for the main Gameplay UI.</step>
    <step>Add the <b>Player Attributes Widget. In this example it will be anchored in the top-left corner, with a margin.</b></step>
    <img src="p02g03_gameplay_widget.png" alt="Gameplay Widget" thumbnail="true" border-effect="line" width="600"/>
</procedure>

<procedure title="Create the Player HUD" collapsible="true">
    <step>Create a new <b>HUD</b>, extending the <code>HUD</code> class.</step>
    <step>
        <p>Implement the <code>BeginPlay</code> event as follows.</p>
        <img src="p02g03_hud_graph.png" alt="HUD graph" thumbnail="true" border-effect="line" width="600"/>
    </step>
    <step>Add the new HUD to your <b>Game Mode</b>.</step>
</procedure>

<procedure title="Test everything" collapsible="true">
    <step>Press <b>Play</b> and notice your progress bars are filled based on the attribute values.</step>
    <step>Modify your initial health, magic or stamina and see these changes in your UI.</step>
</procedure>
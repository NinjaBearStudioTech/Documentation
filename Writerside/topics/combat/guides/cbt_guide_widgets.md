# Display Player and Enemy Vitals
<primary-label ref="combat"/>
<secondary-label ref="guide"/>

Show the player's health on the HUD and put a second health bar above a practice opponent. Both widgets can use the same design. Each needs its own combatant as the data source.

## Player Vitals

<procedure title="Bind the player health bar">
    <step><p>Create a Widget Blueprint based on <code>NinjaCombatBaseWidget</code>. Add a Progress Bar. In the ViewModels panel add the <b>Combat Vitals</b> ViewModel, choose <b>Resolver</b> as the creation type, and select the <b>Ninja Combat ViewModel Resolver</b>.</p></step>
    <step><p>Bind <b>Health Percent</b> to the bar's Percent. For a numerical display, bind current health and maximum health total to Text Blocks using a numeric-to-text conversion. Create the HUD widget with the player controller as its owning player and add it to the viewport.</p></step>
</procedure>

<img src="cbt_advanced_ui_vitals_bindings.png" alt="Health Percent bound to the progress bar" width="650" border-effect="line"/>

<procedure title="Show the enemy health bar">
    <step><p>Add <code>NinjaCombatWidgetComponent</code> to the opponent. Set its widget class to the vitals widget and position it above the mesh. The component supplies the actor it belongs to.</p></step>
    <step><p>For a target panel attached to the player HUD, call <code>SetCombatActor</code> on the widget with the selected opponent. When selection changes, pass the new actor or clear the selection and hide the panel.</p></step>
</procedure>

For a manually created ViewModel, call `InitializeCombatViewModel` with the actor to observe. A custom combat widget can implement the **Combat Actor Aware Interface** in Blueprint or override `SetCombatActor_Implementation` in C++. Keep the parent call when extending the base widget so its ViewModels receive the change. For a new attribute in a C++ ViewModel, override `BindAttributes` and use `BindAttribute` to connect your value to changes on the observed ability system.

## Try It in Play

Damage the opponent while the player stays healthy. Only the overhead bar should fall. Then damage the player and check the HUD. If both bars move together, inspect which actor was supplied to the enemy widget.

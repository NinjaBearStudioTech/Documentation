# Combo Inputs
<primary-label ref="combat"/>

The Combo Ability expects two types of input: the usual **activation action** and a **gameplay event** to advance the combo.

<tabs group="sample">
    <tab title="Blueprint" group-key="bp">
        <img src="cbt_combo_input_blueprint.png" alt="Combo Input" thumbnail="true" border-effect="line"/>
    </tab>
    <tab title="C++" group-key="cpp">
        <code-block lang="c++" src="cbt_combo_input.cpp" />
    </tab>
</tabs>

In the example above:

1. The input first checks if the **combo window** is open, using a specific **Gameplay Tag**.
2. If the window is open, a **gameplay event** is sent to advance the combo.
3. The event’s **payload** includes the **Input Action** (as an optional object).
4. If the window is not open, the input simply **activates** the Combo Ability as usual.

The **Event Tag** you send depends on the **Event Mode** configured in your Combo Ability:

- **GameplayTag Mode**:  
  Send the exact **Gameplay Tag** used by your State Tree transitions (e.g. `Combat.Event.Combo.Attack.Primary`).  
  You do **not** need to send the Input Action in this mode.

- **InputAction Mode**:  
  Always send the gameplay event with the tag `Combat.Event.Combo.Attack`.  
  Include the **Input Action** in the payload. The Combo Ability will map it to a transition tag defined in the State Tree.

> **Ninja Input Integration**
>
> Ninja Input provides built-in input handlers that simplify this process, automatically sending the correct Gameplay 
> Event for each configured action.
{style="tip"}
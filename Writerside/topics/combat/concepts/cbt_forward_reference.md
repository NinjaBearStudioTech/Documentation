# Forward Reference
<primary-label ref="combat"/>

Some aspects of the Combat System, such as the **Evade Ability** may need a global forward reference to function. This
can be any component that always points forward.

This component can be any **Scene Component**, provided by the `GetForwardReference` function, from the Combat Manager
Interface. You do not need to deliberately provide a component, since the Combat Component can create one. However, if
you are using **[](ipt_overview.md)**, then make sure to check the [Input Integration](cbt_integration_input.md#forward-reference)
since Input has similar requirements.
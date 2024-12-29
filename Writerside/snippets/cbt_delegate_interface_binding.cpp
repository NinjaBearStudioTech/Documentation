if (UNinjaCombatFunctionLibrary::IsValidDamageManagerComponent(DamageManager))
{
    // Create the Delegate, binding to the object ("this") and using a function compatible with the signature.
    // All signatures can be found in the NinjaCombatDelegates.h class.
    //
    FOwnerDiedDelegate OwnerDiedDelegate;
    OwnerDiedDelegate.BindDynamic(this, &ThisClass::HandleCombatTargetDeath);

    // Binding to the delegate is done via the appropriate interface, invoked on the target actor component.
    // All interfaces related to their delegates can be found in the documentation site.
    //
    ICombatDamageManagerInterface::Execute_BindToOwnerDiedDelegate(DamageManager, OwnerDiedDelegate);

    // Unbinding is done passing the original object bound to the function ("this").
    // Again, all interfaces can be found in the documentation site.
    //
    ICombatDamageManagerInterface::Execute_UnbindFromOwnerDiedDelegate(DamageManager, this);
}
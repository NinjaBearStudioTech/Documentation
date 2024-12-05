void UComboInputHandler::HandleInputAction(const UInputAction* Action)
{
    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
    if (!IsValid(AbilityComponent))
    {
        return;
    }

    if (AbilityComponent->HasMatchingGameplayTag(Tag_Combat_State_ComboWindow))
    {
        AdvanceCombo(Action);
    }
    else
    {
        StartCombo();
    }
}

void UComboInputHandler::StartCombo()
{
    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
    if (!IsValid(AbilityComponent))
    {
        return;
    }

    // "ActivateComboTags" is a tag container used to activate the Combo Ability.
    // It should match the "Ability Activation" tags container in the Gameplay Ability.
    //
    AbilityComponent->TryActivateAbilitiesByTag(ActivateComboTags);
}

void UComboInputHandler::AdvanceCombo(const UInputAction* Action)
{
    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
    if (!IsValid(AbilityComponent))
    {
        return;
    }

    FGameplayEventData* Payload = new FGameplayEventData();
    Payload->Instigator = GetOwner();
    Payload->Target = GetOwner();
    Payload->EventTag = AdvanceComboTags;
    Payload->OptionalObject = Action;

    // "AdvanceComboTags" is a tag container used to advance the combo to the
    // next attack. It should match the event configuration in the combo ability and
    // indicate a valid event in the Combo State Tree.
    //
    AbilityComponent->HandleGameplayEvent(AdvanceComboTags, Payload);
}
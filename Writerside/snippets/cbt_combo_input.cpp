void UInputHandler_CombatCombo::HandleTriggeredEvent_Implementation(UNinjaInputManagerComponent* Manager, const FInputActionValue& Value, const UInputAction* InputAction, const float ElapsedTime) const
{
    const AActor* Pawn = IsValid(Manager) ? Manager->GetPawn() : nullptr;
    const UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn);

    if (!IsValid(AbilityComponent))
    {
        return;
    }

    if (AbilityComponent->HasMatchingGameplayTag(ComboStateTag))
    {
        AdvanceCombo(Pawn, InputAction);
    }
    else
    {
        StartCombo(Pawn);
    }
}

void UComboInputHandler::StartCombo()
{
    if (!bHandlesActivation || ActivationTags.IsEmpty())
    {
        return;	
    }
	
    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);
    if (!IsValid(AbilityComponent))
    {
        return;
    }

    // "ActivationTags" is a tag container used to activate the Combo Ability.
    // It should match the "Ability Activation" tags container in the Gameplay Ability.
    //
    AbilityComponent->TryActivateAbilitiesByTag(ActivationTags);
}

void UComboInputHandler::AdvanceCombo(const AActor* Owner, const UInputAction* InputAction)
{
    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);
    if (!IsValid(AbilityComponent))
    {
        return;
    }

    FGameplayEventData* Payload = new FGameplayEventData();
    Payload->Instigator = Owner;
    Payload->Target = Owner;
    Payload->EventTag = AdvancementTag;
    Payload->OptionalObject = InputAction;

    // "AdvancementTag" is a gameplay tag used to advance the combo to the
    // next attack. It should match the event configuration in the combo ability and
    // indicate a valid event in the Combo State Tree.
    //
    AbilityComponent->HandleGameplayEvent(AdvancementTag, Payload);
}
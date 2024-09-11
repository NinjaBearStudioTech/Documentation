void UInputHandler_SampleActivation::HandleTriggeredEvent_Implementation(UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, const UInputAction* InputAction, float ElapsedTime) const
{
    UAbilitySystemComponent* ASC = Manager->GetAbilitySystemComponent();
    ASC->TryActivateAbilitiesByTag(AbilityTags, true);
}
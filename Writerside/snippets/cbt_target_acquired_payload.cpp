void APluginLabsCharacter::LockOnTarget(AActor* NewTarget)
{
    // The Native Gameplay Tag is provided by "NinjaCombatTags.h".
    const FGameplayTag EventTag = Tag_Combat_Event_Target_Acquired;

    UAbilitySystemComponent* AbilityComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(this);
    if (IsValid(AbilityComponent))
    {
        FGameplayEventData Payload;
        Payload.EventTag = EventTag;
        Payload.Instigator = this;
        Payload.Target = this;
        Payload.OptionalObject = NewTarget;
        AbilityComponent->HandleGameplayEvent(EventTag, &Payload);
    }
}
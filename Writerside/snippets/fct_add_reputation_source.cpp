void APluginLabsCharacter::AddReputationFromSource(const UObject* Source, FGameplayTag EventTag) const
{
    FactionManager->AddReputationFromSource(Source, EventTag);
}
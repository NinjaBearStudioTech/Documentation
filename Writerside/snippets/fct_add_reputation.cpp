void APluginLabsCharacter::AddReputation(const UNinjaFactionDataAsset* FactionData, int32 Reputation) const
{
    FactionManager->AddReputation(FactionData, Reputation, this, Tag_Factions_Event_Generic);
}
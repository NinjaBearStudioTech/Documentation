#include "FactionDatabase_DataList.h"

void UFactionDatabase_DataList::GetFactions_Implementation(TArray<UNinjaFactionDataAsset*>& OutFactions) const
{
    // Easy-peasy! ;)
    OutFactions = Factions;
}
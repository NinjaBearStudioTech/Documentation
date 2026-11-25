#include "Components/NinjaFactionComponent.h"
#include "NinjaFactionTags.h"

void AwardWatchReputation(UNinjaFactionComponent& PlayerFactions,
    const UNinjaFactionDataAsset& TownWatch, const UObject& QuestGiver)
{
    PlayerFactions.AddReputation(&TownWatch, 12, &QuestGiver, Tag_Factions_Event_QuestCompleted);
}

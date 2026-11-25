#include "Components/NinjaFactionComponent.h"
#include "NinjaFactionTags.h"

void AwardQuestRewards(UNinjaFactionComponent& PlayerFactions, const UObject& QuestGiver)
{
    PlayerFactions.AddReputationFromSource(&QuestGiver, Tag_Factions_Event_QuestCompleted);
}

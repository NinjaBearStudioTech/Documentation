#pragma once

#include "CoreMinimal.h"
#include "NinjaFactionDatabase.h"
#include "FactionDatabase_DataList.generated.h"

UCLASS(DisplayName = "Faction Database: Data List")
class PLUGINLABS_API UFactionDatabase_DataList : public UNinjaFactionDatabase
{

    GENERATED_BODY()

public:

    // -- Begin Faction Database implementation
    virtual void GetFactions_Implementation(TArray<UNinjaFactionDataAsset*>& OutFactions) const override;
    // -- End Faction Database implementation

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Factions")
    TArray<UNinjaFactionDataAsset*> Factions;

};
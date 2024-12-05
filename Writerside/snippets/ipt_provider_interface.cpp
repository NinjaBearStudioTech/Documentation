#include "GameFramework/APluginLabsCharacter.h"
#include "Data/NinjaInputSetupDataAsset.h"

TArray<UNinjaInputSetupDataAsset*> APluginLabsCharacter::GetAddedSetups_Implementation() const
{
    return CharacterInputs;
}

TArray<UNinjaInputSetupDataAsset*> APluginLabsCharacter::GetRemovedSetups_Implementation() const
{
    return CharacterInputs;
}

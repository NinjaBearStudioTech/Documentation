#include "GameFramework/APluginLabsCharacter.h"
#include "Data/NinjaInputSetupDataAsset.h"

TArray<UNinjaInputSetupDataAsset*> APluginLabsCharacter::GetInputSetups_Implementation() const
{
    return CharacterInputs;
}


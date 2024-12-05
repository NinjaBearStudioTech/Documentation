#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InputSetupProviderInterface"
#include "PluginLabsController.generated.h"

class NinjaInputSetupDataAsset;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ACharacter, public IInputSetupProviderInterface
{

    GENERATED_BODY()

public:

    // -- Begin Input Setup Provider implementation
    virtual TArray<UNinjaInputSetupDataAsset*> GetAddedSetups_Implementation() const override;
    virtual TArray<UNinjaInputSetupDataAsset*> GetRemovedSetups_Implementation() const override;
    // -- End Input Setup Provider implementation

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Setup")
    TArray<UNinjaInputSetupDataAsset*> CharacterInputs;

};

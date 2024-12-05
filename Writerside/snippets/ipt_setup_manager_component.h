#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PluginLabsController.generated.h"

class UNinjaInputManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsController : public APlayerController
{

    GENERATED_BODY()

public:

    APluginLabsController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
    TObjectPtr<UNinjaInputManagerComponent> InputManager;

};

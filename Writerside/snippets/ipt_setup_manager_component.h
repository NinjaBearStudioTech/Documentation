#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NBSPlayerController.generated.h"

class UNinjaInputManagerComponent;

UCLASS()
class NBSTECH_API ANBSPlayerController : public APlayerController
{
	
    GENERATED_BODY()

public:

    ANBSPlayerController(const FObjectInitializer& ObjectInitializer);
	
private:

    /** Manages player input, using Enhanced Input/Ninja Input. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess=true))
    TObjectPtr<UNinjaInputManagerComponent> InputManager;
	
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PluginLabsPlayerController.generated.h"

class UNinjaInputManagerComponent;

UCLASS()
class PLUGINLABS_API APluginLabsPlayerController : public APlayerController
{
	
	GENERATED_BODY()

public:

    /** A custom way to open and close the Input Buffer. */
    UFUNCTION(BlueprintCallable, Category = "Custom Buffer Setup")
    void SetBufferState(bool bOpen);

private:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
    TObjectPtr<UNinjaInputManagerComponent> InputManager;

}
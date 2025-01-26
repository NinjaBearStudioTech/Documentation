// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "UInputHandler_LookSample.generated.h"

UCLASS(meta = (DisplayName = "Sample: Look"))
class PLUGINLABS_API UInputHandler_LookSample : public UNinjaInputHandler
{

	GENERATED_BODY()

public:

	UInputHandler_LookSample();

protected:

	virtual void HandleOngoingEvent_Implementation(UNinjaInputManagerComponent* Manager, const FInputActionValue& Value,
		const UInputAction* InputAction, float ElapsedTime) const override;

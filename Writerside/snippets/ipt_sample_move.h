// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "UInputHandler_MoveSample.generated.h"

UCLASS(meta = (DisplayName = "Sample: Move"))
class PLUGINLABS_API UInputHandler_MoveSample : public UNinjaInputHandler
{

	GENERATED_BODY()

public:

	UInputHandler_MoveSample();

protected:

	virtual void HandleOngoingEvent_Implementation(UNinjaInputManagerComponent* Manager, const FInputActionValue& Value,
		const UInputAction* InputAction, float ElapsedTime) const override;
// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "UInputHandler_CrouchSample.generated.h"

UCLASS(meta = (DisplayName = "Sample: Crouch"))
class PLUGINLABS_API UInputHandler_CrouchSample : public UNinjaInputHandler
{

	GENERATED_BODY()

public:

	UInputHandler_CrouchSample();

protected:

	virtual void HandleTriggeredEvent_Implementation(UNinjaInputManagerComponent* Manager, const FInputActionValue& Value,
		const UInputAction* InputAction, float ElapsedTime) const override;

// Ninja Bear Studio Inc., all rights reserved.
#include "InputHandlers/InputHandler_LookSample.h"

#include "InputAction.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/Pawn.h"

UInputHandler_LookSample::UInputHandler_LookSample()
{
	TriggerEvents.Add(ETriggerEvent::Ongoing);
}

void UInputHandler_LookSample::HandleOngoingEvent_Implementation(UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, const UInputAction* InputAction, float ElapsedTime) const
{
    APawn* Pawn = Manager->GetPawn()
	FVector2D InputValue = Value.Get<FVector2D>();

    Pawn->AddControllerYawInput(InputValue[0]);
    Pawn->AddControllerPitchInput(InputValue[1]);
}

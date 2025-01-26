// Ninja Bear Studio Inc., all rights reserved.
#include "InputHandlers/InputHandler_MoveSample.h"

#include "InputAction.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/Pawn.h"

UInputHandler_MoveSample::UInputHandler_MoveSample()
{
	TriggerEvents.Add(ETriggerEvent::Ongoing);
}

void UInputHandler_MoveSample::HandleOngoingEvent_Implementation(UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, const UInputAction* InputAction, float ElapsedTime) const
{
    APawn* Pawn = Manager->GetPawn()
	FVector2D InputValue = Value.Get<FVector2D>();
	InputValue = InputValue.GetSafeNormal();

    const FVector ForwardDirection = Manager->GetForwardVector();
    Pawn->AddMovementInput(ForwardDirection, InputValue[1]);

    const FVector RightDirection = Manager->GetRightVector();
    Pawn->AddMovementInput(RightDirection, InputValue[0]);
}

// Ninja Bear Studio Inc., all rights reserved.
#include "InputHandlers/InputHandler_CrouchSample.h"

#include "InputAction.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

UInputHandler_CrouchSample::UInputHandler_CrouchSample()
{
	TriggerEvents.Add(ETriggerEvent::Triggered);
}

void UInputHandler_LookSample::HandleTriggeredEvent_Implementation(UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value, const UInputAction* InputAction, float ElapsedTime) const
{
	ACharacter* OwningCharacter = Cast<ACharacter>(Manager->GetPawn());
	const bool bShouldCrouch = Value.Get<bool>();

	if (!IsValid(OwningCharacter))
	{
	    return;
	}

	if (bShouldCrouch && OwningCharacter->CanCrouch())
	{
	    OwningCharacter->Crouch();
	}
    else if (!bShouldCrouch && OwningCharacter->bIsCrouched)
    {
        OwningCharacter->UnCrouch();
    }
}

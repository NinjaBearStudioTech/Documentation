// Ninja Bear Studio Inc., all rights reserved.
#include "Input/Handlers/InputHandler_ManageFireIntent.h"

#include "NinjaCombatFirearmFunctionLibrary.h"
#include "Components/NinjaCombatFirearmComponent.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/Pawn.h"

UInputHandler_ManageFireIntent::UInputHandler_ManageFireIntent()
{
    TriggerEvents.Add(ETriggerEvent::Triggered);
}

void UInputHandler_ManageFireIntent::HandleTriggeredEvent_Implementation(UNinjaInputManagerComponent* Manager,
    const FInputActionValue& Value, const UInputAction* InputAction, const float ElapsedTime) const
{
    UNinjaCombatFirearmComponent* FirearmComponent = UNinjaCombatFirearmFunctionLibrary::FindFirearmComponent(Manager->GetPawn(), EquippedFirearmQuery);
    if (!IsValid(FirearmComponent))
    {
        return;
    }
	
    const bool bIntent = Value.Get<bool>();
    if (bIntent)
    {
        FirearmComponent->TryOpenFire();	
    }
    else
    {
        FirearmComponent->TryCeaseFire();
    }
}

// Ninja Bear Studio Inc., all rights reserved.
#include "Input/Handlers/InputHandler_CombatTargetConfirm.h"

#include "NinjaCombatFunctionLibrary.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Components/NinjaInputManagerComponent.h"
#include "Interfaces/Components/CombatTargetManagerInterface.h"

UInputHandler_CombatTargetConfirm::UInputHandler_CastTargetConfirm()
{
    AbilityTargetingOperation = EInputAbilityTargeting::TargetingActor; 
}

AGameplayAbilityTargetActor* UInputHandler_CombatTargetConfirm::GetAbilityTargetActor_Implementation(const UNinjaInputManagerComponent* Manager) const
{
    if (!IsValid(Manager))
    {
        return nullptr;
    }
	
    const UActorComponent* TargetManager = UNinjaCombatFunctionLibrary::GetTargetManagerComponent(Manager->GetOwner());
    if (!UNinjaCombatFunctionLibrary::IsValidTargetManagerComponent(TargetManager))
    {
        return nullptr;
    }
	
    return ICombatTargetManagerInterface::Execute_GetAbilityTargetActor(TargetManager);
}

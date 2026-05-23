// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "Input/Handlers/InputHandler_AbilityTargeting.h"
#include "InputHandler_CombatTargetConfirm.generated.h"

/**
 * Confirms cast targeting through the Targeting Actor provided by Ninja Combat.
 */
UCLASS(Abstract)
class TOPDOWNINPUT_API UInputHandler_CombatTargetConfirm : public UInputHandler_AbilityConfirm
{
	
    GENERATED_BODY()
	
public:

    UInputHandler_CombatTargetConfirm();
	
    virtual AGameplayAbilityTargetActor* GetAbilityTargetActor_Implementation(
        const UNinjaInputManagerComponent* Manager) const override;
	
};

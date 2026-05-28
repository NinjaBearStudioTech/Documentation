// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Input/Handlers/InputHandler_AbilityTargeting.h"
#include "InputHandler_CombatTargetConfirm.generated.h"

UCLASS(Abstract, DisplayName = "Combat Target Confirm")
class UInputHandler_CombatTargetConfirm : public UInputHandler_AbilityConfirm
{
	
    GENERATED_BODY()
	
public:

    UInputHandler_CombatTargetConfirm();
	
    virtual AGameplayAbilityTargetActor* GetAbilityTargetActor_Implementation(
        const UNinjaInputManagerComponent* Manager) const override;
	
};

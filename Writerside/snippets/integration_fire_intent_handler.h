// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "InputHandler_ManageFireIntent.generated.h"

UCLASS(Abstract, DisplayName = "Manage Fire Intent")
class UInputHandler_ManageFireIntent : public UNinjaInputHandler
{
	
    GENERATED_BODY()
	
public:

    UInputHandler_ManageFireIntent();
    
    virtual AGameplayAbilityTargetActor* GetAbilityTargetActor_Implementation(
        const UNinjaInputManagerComponent* Manager) const override;
    
protected:
	
    /** Query used to retrieve the equipped firearm. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Manage Fire Intent")
    FGameplayTagQuery EquippedFirearmQuery;
	
};

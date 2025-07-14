// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/EquipmentSystemInterface.h"
#include "NBSPlayerCharacter.generated.h"

class UNinjaEquipmentManagerComponent;

UCLASS()
class NBSTECH_API ANBSPlayerCharacter : public ACharacter, public IEquipmentSystemInterface
{
	
    GENERATED_BODY()

public:

    ANBSPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    // -- Begin EquipmentSystem implementation
    virtual UNinjaEquipmentManagerComponent* GetEquipmentManager_Implementation() const override;
    // -- End EquipmentSystem implementation
	
private:

    /** Equipment Manager component. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaEquipmentManagerComponent> EquipmentManager;
	
};

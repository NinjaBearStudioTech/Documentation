// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASCharacter.h"
#include "Interfaces/CombatSystemInterface.h"
#include "NBSCharacter.generated.h"

class UNinjaCombatManagerComponent;

UCLASS(Abstract)
class NBSTECH_API ANBSCharacter : public ANinjaGASCharacter, public ICombatSystemInterface
{
	
    GENERATED_BODY()

public:

    ANBSCharacter(const FObjectInitializer& ObjectInitializer);

    // -- Begin CombatSystem implementation
    virtual UNinjaCombatManagerComponent* GetCombatManager_Implementation() const override;
    virtual USceneComponent* GetCombatForwardReference_Implementation() const override;
    virtual USkeletalMeshComponent* GetCombatMesh_Implementation() const override;
    virtual UAnimInstance* GetCombatAnimInstance_Implementation() const override;
    // -- End CombatSystem implementation
	
private:

    /** Forward Reference (Input and Combat integration). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UArrowComponent> ForwardReference;
	
    /** Combat Manager component. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaCombatManagerComponent> CombatManager;
	
};

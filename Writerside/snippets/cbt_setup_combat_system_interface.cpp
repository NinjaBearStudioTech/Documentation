// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/NBSCharacter.h"

#include "NinjaCombatTags.h"
#include "Components/ArrowComponent.h"
#include "Components/NinjaCombatManagerComponent.h"

ANBSCharacter::ANBSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ForwardReference = CreateDefaultSubobject<UArrowComponent>("ForwardReference");
    ForwardReference->ComponentTags.Add(Tag_Combat_Component_ForwardReference.GetTag().GetTagName());
    ForwardReference->SetVisibleFlag(false);
    ForwardReference->SetUsingAbsoluteRotation(true);
    ForwardReference->SetWorldRotation(FRotator::ZeroRotator);
    ForwardReference->SetArrowColor(FLinearColor::Green);
    ForwardReference->SetupAttachment(GetRootComponent());
	
    CombatManager = CreateDefaultSubobject<UNinjaCombatManagerComponent>("CombatManager");
}

UNinjaCombatManagerComponent* ANBSCharacter::GetCombatManager_Implementation() const
{
    return CombatManager;
}

USceneComponent* ANBSCharacter::GetCombatForwardReference_Implementation() const
{
    return ForwardReference;
}

USkeletalMeshComponent* ANBSCharacter::GetCombatMesh_Implementation() const
{
    return GetMesh();
}

UAnimInstance* ANBSCharacter::GetCombatAnimInstance_Implementation() const
{
    return GetMesh()->GetAnimInstance();
}

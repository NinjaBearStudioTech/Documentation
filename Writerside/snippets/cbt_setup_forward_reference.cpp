#include "Components/ArrowComponent.h"

ANBSCharacter::ANBSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ForwardReference = CreateDefaultSubobject<UArrowComponent>("ForwardReference");
    ForwardReference->ComponentTags.Add(Tag_Combat_Component_ForwardReference.GetTag().GetTagName());
    ForwardReference->SetVisibleFlag(false);
    ForwardReference->SetUsingAbsoluteRotation(true);
    ForwardReference->SetWorldRotation(FRotator::ZeroRotator);
    ForwardReference->SetArrowColor(FLinearColor::Green);
    ForwardReference->SetupAttachment(GetRootComponent());
}

#include "Components/ArrowComponent.h"
#include "Components/NinjaInputManagerComponent.h"

ANinjaFrameworkCharacter::ANinjaFrameworkCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    const FName ForwardReferenceTag = Tag_Input_Component_ForwardReference.GetTag().GetTagName();
    ForwardReference = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardReference"));
    ForwardReference->ComponentTags.Add(ForwardReferenceTag);
    ForwardReference->SetVisibleFlag(false);
    ForwardReference->SetUsingAbsoluteRotation(true);
    ForwardReference->SetWorldRotation(FRotator::ZeroRotator);
    ForwardReference->SetArrowColor(FLinearColor::Green);
    ForwardReference->SetAutoActivate(true);
    ForwardReference->SetupAttachment(GetRootComponent());
}
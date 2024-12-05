#include "Components/ArrowComponent.h"
#include "Components/NinjaInputManagerComponent.h"

ANinjaFrameworkCharacter::ANinjaFrameworkCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ForwardReference = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardReference"));
    ForwardReference->ComponentTags.Add(UNinjaInputManagerComponent::ForwardReferenceTag);
    ForwardReference->SetVisibleFlag(false);
    ForwardReference->SetUsingAbsoluteRotation(true);
    ForwardReference->SetWorldRotation(FRotator::ZeroRotator);
    ForwardReference->SetArrowColor(FLinearColor::Green);
    ForwardReference->SetAutoActivate(true);
    ForwardReference->SetupAttachment(GetRootComponent());
}
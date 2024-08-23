#include "Components/NinjaInputManagerComponent.h"
#include "Data/NinjaInputSetupDataAsset.h"

void ANinjaLabsItem::BeginPlay()
{
    Super::BeginPlay();
    GetOwnerInputManager()->AddInputSetupData(ItemSetupData);
}

void ANinjaLabsItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetOwnerInputManager()->RemoveInputSetupData(ItemSetupData);
    Super::EndPlay(EndPlayReason);
}
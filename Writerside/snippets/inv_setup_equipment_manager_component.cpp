#include "Components/NinjaEquipmentManagerComponent.h"

ANBSPlayerCharacter::ANBSPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    EquipmentManager = CreateDefaultSubobject<UNinjaEquipmentManagerComponent>(TEXT("EquipmentManager"));
}

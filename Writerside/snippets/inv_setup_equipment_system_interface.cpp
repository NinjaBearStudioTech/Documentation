// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/NBSPlayerCharacter.h"

#include "Components/NinjaEquipmentManagerComponent.h"

ANBSPlayerCharacter::ANBSPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    EquipmentManager = CreateDefaultSubobject<UNinjaEquipmentManagerComponent>(TEXT("EquipmentManager"));
}

UNinjaEquipmentManagerComponent* ANBSPlayerCharacter::GetEquipmentManager_Implementation() const
{
    return EquipmentManager;
}

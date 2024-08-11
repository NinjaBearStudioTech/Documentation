// Ninja Bear Studio Inc., all rights reserved.
#include "GameFramework/PluginLabsWeaponActor.h"

#include "NinjaCombatTags.h"
#include "Net/UnrealNetwork.h"

APluginLabsWeaponActor::APluginLabsWeaponActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bReplicates = true;
    WeaponTags = FGameplayTagContainer::EmptyContainer;

	static const FName ScanSourceTag = Tag_Combat_Component_MeleeScanSource.GetTag().GetTagName();
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->bCastDynamicShadow = true;
	WeaponMesh->bLightAttachmentsAsGroup = true;
	WeaponMesh->ComponentTags.Add(ScanSourceTag);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void APluginLabsWeaponActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, WeaponTags);
}


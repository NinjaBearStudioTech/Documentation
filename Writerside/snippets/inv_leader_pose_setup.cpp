APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
    GetMesh()->bLightAttachmentsAsGroup = true;

	Head = CreateFollowerMesh(Head, "Head", Tag_Crucible_Slot_Head);
	Helm = CreateFollowerMesh(Head, "Helm", Tag_Crucible_Slot_Helm);
	Chest = CreateFollowerMesh(Head, "Chest", Tag_Crucible_Slot_Chest);
	Bracers = CreateFollowerMesh(Head, "Bracers", Tag_Crucible_Slot_Bracers);
	Legs = CreateFollowerMesh(Head, "Legs", Tag_Crucible_Slot_Legs);
	Boots = CreateFollowerMesh(Head, "Boots", Tag_Crucible_Slot_Boots);
	Hands = CreateFollowerMesh(Head, "Hands", Tag_Crucible_Slot_Hands);
}

USkeletalMeshComponent* APluginLabsCharacter::CreateFollowerMesh(USkeletalMeshComponent* LeaderMesh, FName MeshName, FGameplayTag SlotTag)
{
    USkeletalMeshComponent* FollowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(MeshName);
    FollowerMesh->bUseBoundsFromLeaderPoseComponent = true;
    FollowerMesh->bUseAttachParentBound = true;
    FollowerMesh->bLightAttachmentsAsGroup = false;
    FollowerMesh->bComponentUseFixedSkelBounds = false;
    FollowerMesh->ComponentTags.Add(SlotTag.GetTagName());
    FollowerMesh->SetLeaderPoseComponent(LeaderMesh);
    FollowerMesh->SetupAttachment(LeaderMesh);
    return FollowerMesh;
}
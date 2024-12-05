public:

    APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Head;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Helm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Chest;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Bracers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Legs;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Boots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> Hands;

    /** Support function to create follower meshes IN THE CONSTRUCTOR. */
    USkeletalMeshComponent* CreateFollowerMesh(USkeletalMeshComponent* LeaderMesh, FName MeshName, FGameplayTag SlotTag);

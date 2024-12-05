public:

    APluginLabsWeaponActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Actor implementation
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// -- End Actor implementation

protected:

	/** Tags used to identify this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Replicated)
	FGameplayTagContainer WeaponTags;

private:

    /** Weapon that represents the mesh. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<UStaticMeshComponent> WeaponMesh;

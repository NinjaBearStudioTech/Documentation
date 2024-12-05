public:

    APluginLabsWeaponActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Actor implementation
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// -- End Actor implementation

protected:

	/** Tags used to identify this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", Replicated)
	FGameplayTagContainer WeaponTags;

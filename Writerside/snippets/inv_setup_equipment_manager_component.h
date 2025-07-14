public:

    ANBSPlayerCharacter(const FObjectInitializer& ObjectInitializer);

private:

    /** Equipment Manager component. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaEquipmentManagerComponent> EquipmentManager;
	
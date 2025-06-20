public:

    ANBSPlayerState(const FObjectInitializer& ObjectInitializer);

private:

    /** Inventory Manager component. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaInventoryManagerComponent> InventoryManager;
	
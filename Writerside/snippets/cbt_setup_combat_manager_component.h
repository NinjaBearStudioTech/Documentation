public:

    ANBSCharacter(const FObjectInitializer& ObjectInitializer);

private:

    /** Combat Manager component. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaCombatManagerComponent> CombatManager;
	
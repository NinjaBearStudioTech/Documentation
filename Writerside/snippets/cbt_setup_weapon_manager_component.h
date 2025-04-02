public:

    /** Name that can be used with FObjectInitializer to override the default class. */
    static FName WeaponManagerName;

    ANBSCharacter(const FObjectInitializer& ObjectInitializer);
    
    // -- Begin CombatSystem implementation
    virtual UActorComponent* GetWeaponManagerComponent_Implementation() const override;
    // -- End CombatSystem implementation

private:

    /** Base Weapon Manager for the character. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UNinjaCombatBaseWeaponManagerComponent> WeaponManager;

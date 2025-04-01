public:

    ANBSCharacter(const FObjectInitializer& ObjectInitializer);

private:

    /** Forward Reference (Input and Combat integration). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UArrowComponent> ForwardReference;
	
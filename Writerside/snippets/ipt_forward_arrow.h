public:

    APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    TObjectPtr<UArrowComponent> ForwardReference;
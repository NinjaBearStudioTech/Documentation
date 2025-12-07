UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
FName OffHandTargetBoneName = TEXT("hand_r");

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offhand Placement")
bool bHasOffhandTransform = false;
	
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offhand Placement")
float OffhandAlpha = 0.f;
	
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offhand Placement")
FTransform OffhandTransform = FTransform::Identity;

UFUNCTION(BlueprintCallable, Category = "Animation")
void UpdateOffhandValues();
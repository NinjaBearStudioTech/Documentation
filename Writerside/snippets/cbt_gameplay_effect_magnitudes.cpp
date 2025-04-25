void UMyCombatAbility::GetAdditionalCombatMagnitudes_Implementation(const AActor* DamageSource, const UGameplayEffect* Effect, TMap<FGameplayTag, float>& OutMagnitudes)
{
    const float ExtraData = Effect->FindComponent<UMyCustomDataComponent>()->GetSomeExtraData();
    OutMagnitudes.Add("Combat.Data.MyCustomData", ExtraData);
}
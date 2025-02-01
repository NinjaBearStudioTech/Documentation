float AIntegratedEquipmentWeaponActor::GetHitEffectLevel_Implementation() const
{
	// Consider the fallback level as the default effect set in the class.
	float ItemLevel = Super::GetHitEffectLevel_Implementation();

	if (!bUseItemLevelAsEffectLevel)
	{
		return ItemLevel;
	}

	if (IsValid(EquipmentReceiver) && EquipmentReceiver->Implements<UEquipmentActorInterface>())
	{
		const UNinjaEquipment* Equipment = IEquipmentActorInterface::Execute_GetEquipment(EquipmentReceiver);
		if (!IsValid(Equipment))
		{
			return ItemLevel;
		}

		const UNinjaInventoryItem* Item = Equipment->GetItem();
		check(IsValid(Item));

		const UItemFragment_Level* LevelFragment = Item->FindFragment<UItemFragment_Level>();
		if (IsValid(LevelFragment))
		{
			ItemLevel = LevelFragment->GetLevel(Item);
		}
	}

	return ItemLevel;
}

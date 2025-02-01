// ...
UCLASS(Abstract, Blueprintable)
class PLUGINLABS_API AIntegratedEquipmentWeaponActor : public ANinjaCombatWeaponActor
{

    // ...
	virtual float GetHitEffectLevel_Implementation() const override;
    // ...

};

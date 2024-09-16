APluginLabsCharacter::APluginLabsCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNinjaCombatCharacterMovementComponent>(CharacterMovementComponentName))
{
    // ...
}
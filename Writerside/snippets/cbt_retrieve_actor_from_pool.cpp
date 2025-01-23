#include "NinjaCombatActorPoolFunctionLibrary.h"

void APluginLabsCharacter::ActivateActor()
{
    AActor* PoolableActor = UNinjaCombatActorPoolFunctionLibrary::TryGetActorFromPool(RequestOwner, DesiredClass);
	if (IsValid(PoolableActor))
	{
		// The actor was spawned.
	}
	else
	{
		// The pool does not have an instance available.
	}
}
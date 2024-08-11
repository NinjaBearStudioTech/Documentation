// Ninja Bear Studio Inc., all rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CombatWeaponInterface.h"
#include "PluginLabsWeaponActor.generated.h"

UCLASS(Abstract)
class PLUGINLABS_API APluginLabsWeaponActor : public AActor, public ICombatWeaponInterface
{
	
	GENERATED_BODY()

};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatPoolProviderInterface.h"
#include "PluginLabsCharacter.generated.h"

class UNinjaCombatActorPoolComponent;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ACharacter, public ICombatPoolProviderInterface
{

	GENERATED_BODY()

public:

	APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Pool Provider interface.
	virtual UNinjaCombatActorPoolComponent* GetActorPool_Implementation() const override;
	// -- End Pool Provider interface.


private:

	/** Pool of actors that are frequently used. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaCombatActorPoolComponent> ActorPool;

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/FactionMemberInterface.h"
#include "PluginLabsPlayerState.generated.h"

class UNinjaFactionComponent;

UCLASS()
class PLUGINLABS_API APluginLabsCharacter : public ACharacter, public IFactionMemberInterface,
{

    GENERATED_BODY()

public:

    APluginLabsCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// -- Begin Faction Member implementation
	virtual UNinjaFactionComponent* GetFactionComponent_Implementation() const override;
	// -- End Faction Member implementation

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNinjaFactionComponent> FactionManager;

};
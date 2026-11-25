#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaFactionAttitudeSolver.h"
#include "FactionSolver_ChaoticSolver.generated.h"

UCLASS(DisplayName = "Faction Attitude Solver: Chaotic Solver")
class PLUGINLABS_API UFactionSolver_ChaoticSolver : public UNinjaFactionAttitudeSolver
{

    GENERATED_BODY()

public:

    // -- Begin Faction Attitude Solver implementation
    virtual ETeamAttitude::Type SolveAttitude_Implementation(const AActor* Source, const AActor* Target) const override;
    // -- End Faction Attitude Solver implementation

};

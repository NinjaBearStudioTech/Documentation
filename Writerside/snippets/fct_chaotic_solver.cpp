#include "FactionSolver_ChaoticSolver.h"

ETeamAttitude::Type UFactionSolver_ChaoticSolver::SolveAttitude_Implementation(const AActor* Source, const AActor* Target) const
{
    // Yikes! o.O
    return FMath::RandBool() ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}
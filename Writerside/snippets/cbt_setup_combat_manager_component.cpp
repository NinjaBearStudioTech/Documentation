#include "Components/NinjaCombatManagerComponent.h"

ANBSCharacter::ANBSCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    CombatManager = CreateDefaultSubobject<UNinjaCombatManagerComponent>("CombatManager");
}

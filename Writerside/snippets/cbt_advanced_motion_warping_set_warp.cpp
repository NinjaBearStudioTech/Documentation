void ASampleCharacter::WarpToActor(AActor* Actor)
{
    FCombatWarpContext WarpContext;
    WarpContext.WarpTarget = Actor;
    WarpContext.bHandled = true;

    const FInstancedStruct InstancedStruct = FInstancedStruct::Make(WarpContext);
    ICombatMotionWarpingInterface::Execute_SetCombatWarpTarget(MotionWarping, WarpName, InstancedStruct);
}

void ASampleCharacter::ExecuteTargetingAndWarp(AActor* Actor)
{
    FCombatWarpContext_TargetingPreset WarpContext;
    WarpContext.WarpTargetingPreset = MotionWarpingTargetPreset;
    WarpContext.bTrackTarget = true;

    const FInstancedStruct InstancedStruct = FInstancedStruct::Make(WarpContext);
    ICombatMotionWarpingInterface::Execute_SetCombatWarpTarget(MotionWarping, WarpName, InstancedStruct);
}
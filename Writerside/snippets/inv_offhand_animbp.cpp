void UCustomAnimInstance::UpdateOffhandValues()
{
    if (IsValid(EquipmentManager))
    {
        if (EquipmentManager->GetActiveOffhandTransformInBoneSpace(OffHandTargetBoneName, OffhandTransform))
        {
            bHasOffhandTransform = true;
            OffhandAlpha = 1.f;
            return;	
        }
    }
	
    bHasOffhandTransform = false;
    OffhandAlpha = 0.f;
    OffhandTransform = FTransform::Identity;
}
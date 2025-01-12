# Setup
<primary-label ref="interaction"/>

## Ability System

The **Ability System Component** is a prerequisite for the system to operate. Ensure that actors using the Interaction
Manager Component also have an **Ability System Component** and implement the `AbilitySystemInterface`.

Usually, both Interaction Abilities should also be granted by default. To know more about them, make sure to review the 
[Abilities](int_abilities.md).

## Collision Channels

You may want to create dedicated trace and object channels for the interaction. You can do that by adding the following
lines to your `DefaultEngine.ini` file, located in your `Config` folder.

```ini
[/Script/Engine.CollisionProfile]
+Profiles=(Name="Interactable",CollisionEnabled=QueryAndPhysics,bCanModify=True,ObjectTypeName="InteractionObject",CustomResponses=((Channel="WorldStatic",Response=ECR_Ignore),(Channel="WorldDynamic",Response=ECR_Ignore),(Channel="Pawn",Response=ECR_Ignore),(Channel="Visibility",Response=ECR_Ignore),(Channel="Camera",Response=ECR_Ignore),(Channel="PhysicsBody",Response=ECR_Ignore),(Channel="Vehicle",Response=ECR_Ignore),(Channel="Destructible",Response=ECR_Ignore),(Channel="InteractionScan"),(Channel="Projectile",Response=ECR_Ignore),(Channel="InteractionObject",Response=ECR_Overlap)),HelpMessage="Actors that can receive interactions.")
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="InteractionScan")
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel2,DefaultResponse=ECR_Ignore,bTraceType=False,bStaticObject=False,Name="InteractionObject")
```

> **Double-check your Game Trace Channels**
>
> The Trace Channels from the sample above might already be in use for other purposes in your game. Double-check that
> they are not conflicting with anything else to avoid odd collision issues.
>
> Also make sure that you are not duplicating the Collision Profile category itself.
{style="warning"}
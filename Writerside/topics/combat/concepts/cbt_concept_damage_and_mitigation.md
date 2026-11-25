# Damage, Defense, and Recovery
<primary-label ref="combat"/>

When a hit connects, the attack's Gameplay Effect supplies the damage calculation. **Defense Data** on the target decides how much gets through. **Damage Data** decides what happens after the result is known. This lets a training dummy, a shield bearer, and a boss react differently to the same hit.

| What you want to change | Where to change it |
| --- | --- |
| How hard a move hits | Start with the attacker's Base Damage or supply an override on the hit effect. |
| What a shield or armor absorbs | Configure the ordered **Mitigation Pipeline** in Defense Data. Put checks that cancel a hit, such as invulnerability, before reductions that spend resources. |
| Whether a surviving hit interrupts a move | Set poise and the attack's poise consumption. Configure the stagger outcome and grant the corresponding ability. A routine hit can play a hit reaction without causing a stagger. |
| Whether a fatal hit kills or downs the defender | Order eligible survival or knockdown outcomes before Death. Grant the abilities that perform the desired reactions. |
| Which impact the player sees or hears | Set the damage cosmetics and animation provider. A cosmetic can respond to the resolved hit without changing health. |

## Scale a Single Move

For a heavy follow-up, add a calculation modifier to the hit effect's damage execution. Use `Combat.Data.Damage.Multiplier` with a scalable float magnitude of 1.5. Test against a target with the same defenses as before so you can see the difference from the normal move.

## Respond to the Outcome

Bind to `BindToDamageReceivedDelegate` on the damage manager for feedback on an individual character. Use `BindToOwnerDiedDelegate` when gameplay should stop and `BindToOwnerFinishedDyingDelegate` when the death presentation can be cleaned up. The [damage guide](cbt_guide_damage_pipeline.md) shows a surviving and a fatal hit. For alternatives, see [defensive moves](cbt_guide_block.md) and [knockdown and recovery](cbt_guide_knockdown.md).

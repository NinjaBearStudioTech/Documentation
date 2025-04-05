# Stagger Ability
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Triggers whenever the owner is <b>staggered</b>, so it can apply any additional logic.</li>        
        <li>This is <b>not</b> the hit reaction! The Hit Reaction is played along with this ability.</li>
    </ul>
</tldr>

The main purpose of the **Stagger Ability** is to **cancel other abilities** that should be interrupted when the avatar 
is staggered. By default, this ability will activate when the **Stagger Gameplay Effect** is applied.

## Ability Activation

The **Stagger Gameplay Effect** can be applied by any incoming **damage effect** that adds **poise damage**. If this
effect is applied, the Gameplay Tag denoting the Stagger State will activate the Gameplay Ability.

Similarly, the Stagger Ability **ends** when the Stagger Effect is **removed** from the avatar.

> The Stagger Ability should always be **granted by default**, to any character that can be staggered.
{style=note}

## Ability Interruption

Since the main purpose of this Gameplay Ability is to **interrupt** and **block** other Gameplay Abilities during the 
Stagger state, you should add any relevant Gameplay Tags to the **ActivationBlockedTags** and **BlockAbilitiesWithTag**
Gameplay Tag Containers.

By default, the Stagger Ability will cancel **attacks**, **casts**, **combos**, **evades** and **opportunity attacks**.

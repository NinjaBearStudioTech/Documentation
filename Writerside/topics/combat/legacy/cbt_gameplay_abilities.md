# Gameplay Abilities
<primary-label ref="combat"/>

The Combat System provides several Gameplay Abilities that can be configured or extended to implement common combat-related
functionalities.

**[Attack](cbt_overview.md)**
: This Gameplay Ability can be used to implement **Melee** and **Ranged** attacks, including the option to have both
attack types in the same ability.

**[Block](cbt_overview.md)**
: Applies the **Block** Gameplay Effect, which enhances the **defense** for a character and may trigger certain logic
in other parts of the system, such as **Animation** and **Movement** modules.

**[Cast](cbt_overview.md)**
: This flexible Gameplay Ability can be used to create multiple types of "spells". These can be **instant** or **targeted**,
and applied on the **caster** or other **selected targets**.

**[Combo](cbt_overview.md)**
: Orchestrates other Abilities, such as **attacks** or **casts** so they can be executed in sequence, as long as certain
pre-conditions are met, such as certain inputs pressed within a **combo window**.

**[Death](cbt_overview.md)**
: Usually triggered when the character dies, this Gameplay Ability will play appropriate animations that can be related
to the source of fatal damage, and execute any final logic before the owning Actor is destroyed.

**[Evade](cbt_overview.md)**
: This Gameplay Ability plays animations that represent evasive maneuvers, such as **dodges**, **rolls** and **sidesteps**.
Supports both directional inputs and default movements, and can be easily adjusted to create **invincibility frames**.

**[Hit Reaction](cbt_overview.md)**
: Hit Reactions are triggered after each valid hit, so they can execute any necessary logic and play relevant animations,
that can be selected based on different damage types and incoming hit directions.

**[Opportunity Attacks](cbt_overview.md)**
: Attacks that can only be performed under certain circumstances and require animations to be **synchronized**
between the attacker and victim can be created using this Gameplay Ability. It also supports **camera animations** for
an extra cinematic flavour.

**[Stagger](cbt_overview.md)**
: This Gameplay Ability is triggered whenever a **Stagger Gameplay Effect** is applied, so it can perform any relevant
logic that must be implemented **in addition** to the Hit Reaction.

**[Target Lock](cbt_overview.md)**
: Uses the **Gameplay Targeting System** to select a target from a list of eligible candidates. Locking on a target can
lead to other changes in other systems, such as **Animation** and **Movement** modules.


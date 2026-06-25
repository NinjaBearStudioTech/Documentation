# User Interface
<primary-label ref="combat"/>

Representing combat data in the user interface is a common requirement for many games. Ninja Combat exposes relevant
data using **UMG ViewModels**, **Widget Components**, and **Gameplay Effect UI Components**.

This approach avoids requiring a specific **Widget hierarchy**, allowing greater flexibility when choosing your own
widget design and UI frameworks.

## UMG ViewModels

ViewModels are objects provided by Unreal Engine that follow the **MVVM Pattern**, which proposes a separation between
the **view layer** (your *widgets*) and the **model layer** (the *gameplay framework*).

In this design pattern, each layer does not directly reference the other. Collecting, transforming, and exchanging
information between both layers is the responsibility of the **ViewModel** object.

Another advantage of ViewModels is that they are **reactive**. Widgets are updated when ViewModels broadcast an update,
which is different from traditional **UMG Property Binding**, which collects information every frame, even when nothing
has changed.

### Combat Resolver

As mentioned above, combat widgets should be initialized using the **Ninja Combat ViewModel Resolver** class. This class
collects the current Widget Owner, the player, and sets it on Combat ViewModels, so they can perform any required
initialization.

## Widget Component

In cases where the ViewModel should be initialized for another combatant, such as an enemy for an overhead widget, you
can use the provided `NinjaCombatWidgetComponent`.

Once the component's widget is initialized, it calls `InitializeCombatViewModel` on all hosted ViewModels, passing
the component's owner so the ViewModels can initialize for that actor.

## ViewModel Reference

Ninja Combat includes a collection of ViewModels that can be used in your project. They all follow the same MVVM
structure and can be extended to support additional combat data.

### Combat Vitals

The Combat Vitals ViewModel exposes the character's primary resources, such as Health, Stamina, and Mana, including
their current values, maximum totals, and percentages.

| Property          | Description                                                      |
|-------------------|------------------------------------------------------------------|
| Is Dead           | Indicates whether the character has died, when Health reaches 0. |
| Health            | Current Health.                                                  |
| Health Percent    | Health percent in the [0, 1] range. Useful for Progress Bars.    |
| Max Health Total  | Total Health, including bonuses.                                 |
| Stamina           | Current Stamina.                                                 |
| Stamina Percent   | Stamina percent in the [0, 1] range. Useful for Progress Bars.   |
| Max Stamina Total | Total Stamina, including bonuses.                                |
| Mana              | Current Mana.                                                    |
| Mana Percent      | Mana percent in the [0, 1] range. Useful for Progress Bars.      |
| Max Mana Total    | Total Mana, including bonuses.                                   |

### Combo State

Exposes information about the combo state for the owning combatant.

| Property        | Description                                             |
|-----------------|---------------------------------------------------------|
| In Combo Window | Indicates whether the character's combo window is open. |
| Combo Count     | Current Combo Count.                                    |

### Damage

Exposes information about the last damage received and additional details about it. You can display Last Damage Received
as-is, or bind it to a **function** to accumulate damage over time.

| Property                | Description                                              |
|-------------------------|----------------------------------------------------------|
| Received Blocked Hit    | Indicates whether the last hit was blocked.              |
| Received Breaker Hit    | Indicates whether the last hit broke the blocking state. |
| Received Critical Hit   | Indicates whether the last hit was a critical hit.       |
| Received Fatal Hit      | Indicates whether the last hit was fatal.                |
| Received Staggering Hit | Indicates whether the last hit was staggering.           |
| Last Damage Received    | Amount of damage applied by the last hit.                |

### Poise and Stagger

Exposes information about poise and stagger. You can also track the Stagger state using the **Status Effect** ViewModel,
which might be a better choice if you do not need to expose any information about *poise*.

| Property                | Description                                             |
|-------------------------|---------------------------------------------------------|
| Is Staggered            | Indicates whether the character is currently staggered. |
| Poise                   | Current Poise value available in the Attribute Set.     |
| Poise Damage            | Current Poise Damage applied.                           |
| Poise Recovery          | Amount of Poise recovered.                              |
| Poise Recovery Interval | How quickly Poise is recovered.                         |
| Poise Percent           | Percentage of Poise remaining before a stagger occurs.  |
| Stagger Duration        | Duration of the stagger effect.                         |

### Status Effects

Provides a list of Status Effects assigned to the owner's Ability System Component. Entries are of the `FActiveGameplayEffect`
type and include any Gameplay Effect that contains a UI Data Component of type `GameplayEffectUIData_CombatStatus`.

`GameplayEffectUIData_CombatStatus` can expose information such as icon, display name, and remaining time, depending
on how it is configured. You can access this data in your widget and render it as needed.

| Property              | Description                                                        |
|-----------------------|--------------------------------------------------------------------|
| Active Status Effects | Provides all status effects relevant to the Combat User Interface. |

### Target Lock

Indicates whether the current target is targeted by the HUD owner, usually the Player. This is useful for enemies showing
an indication that they are locked by the current player.

| Property               | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| Is Locked By HUD Owner | Indicates whether the combatant is the locked target for the HUD owner. |

<seealso style="cards">
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/unreal-engine/umg-viewmodel-for-unreal-engine" summary="Use Viewmodels to populate your custom user interfaces with data.">UMG ViewModel Reference</a>
    </category>
</seealso>

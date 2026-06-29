# User Interface
<primary-label ref="combat"/>
<secondary-label ref="advanced"/>

Representing combat data in the user interface is a common requirement for many games. Ninja Combat exposes relevant 
data using **UMG ViewModels**, **Widget Components** and **Gameplay Effect UI Components**.

This approach reduces the requirement on having any specific **Widget hierarchy**, allowing greater flexibility when
choosing your own widget design and frameworks.

## UMG ViewModels
ViewModels are a type of object provided by Unreal Engine, following the **VMMV Pattern**, which proposes a separation 
of the **view layer** - your _widgets_ - from the **model layer** - the _game_.

In that design pattern, each layer does not directly reference the other. Collecting and transforming information, and 
exchanging it between both layers, is the responsibility of the **ViewModel** object. 

Another advantage of ViewModels is the fact that they are **reactive**. Widgets are updated when ViewModels broadcast an
update, which is different from the traditional **UMG Property Binding** that collects information on each frame, even
if nothing has changed.

### Combat Resolver
As mentioned above, combat widgets should be initialized using the **Ninja Combat ViewModel Resolver** class. This class
will collect the current Widget Owner - the player - and set it to Combat ViewModels, so they can perform any 
initialization task needed.

## Widget Component
In cases where the ViewModel should be initialized to another combatant, such as an enemy for an overhead widget, you 
can use the provided `NinjaCombatWidgetComponent`.

Once the component's widget is initialized, it will call `InitializeCombatViewModel` on all hosted ViewModels, passing
the component's owner, so the ViewModels can initialize to that new actor.

## ViewModel Reference
Ninja Combat includes a collection of ViewModels that can be used in your project. They are all created following the 
same MVVM structure and can be extended to support additional combat data.

### Combat Vitals
The Combat Vitals ViewModel exposes the character’s primary resources (Health, Stamina, Magic), including their current 
values, maximum totals, and percentages.

| Property          | Description                                                       |
|-------------------|-------------------------------------------------------------------|
| Is Dead           | Indicates whether the character has died (when health reaches 0). |
| Health            | Current Health.                                                   |
| Health Percent    | Health percent in [0, 1] range. Useful for Progress Bars.         |
| Max Health Total  | Total Health, including bonuses.                                  |
| Stamina           | Current Stamina.                                                  |
| Stamina Percent   | Stamina percent in [0, 1] range. Useful for Progress Bars.        |
| Max Stamina Total | Total Stamina, including bonuses.                                 |
| Magic             | Current Magic.                                                    |
| Magic Percent     | Magic percent in [0, 1] range. Useful for Progress Bars.          |
| Max Magic Total   | Total Magic, including bonuses.                                   |

### Combo State
Exposes information about the combo state for the owning combatant.

| Property         | Description                                               |
|------------------|-----------------------------------------------------------|
| In Combo Window  | Informs if the character's combo window is open.          |
| Combo Count      | Current Combo Count.                                      |

### Damage
Exposes information about the last damage received and additional details about it. You can display Last Damage Received 
as-is, or bind it to a **function** to accumulate damage over time.

| Property                | Description                                            |
|-------------------------|--------------------------------------------------------|
| Received Blocked Hit    | Informs if the last hit was blocked.                   |
| Received Breaker Hit    | Informs if the last hit has broken the blocking state. |
| Received Critical Hit   | Informs if the last hit was a critical hit.            |
| Received Fatal Hit      | Informs if the last hit was fatal.                     |
| Received Staggering Hit | Informs if the last hit was staggering.                |
| Last Damage Received    | Amount of damage applied from the last hit.            |

### Poise and Stagger
Exposes information about poise and stagger. You can also track the Stagger state using the **Status Effect** view 
model, which might be a better choice, if you don't need to expose any information about _poise_.

| Property                | Description                                                |
|-------------------------|------------------------------------------------------------|
| Is Staggered            | Indicates if the character is currently staggered.         |
| Poise                   | The current Poise value available in the Attribute Set.    |
| Poise Damage            | Current Poise Damage applied.                              |
| Poise Recovery          | How much poise is recovered.                               |
| Poise Recovery Interval | How fast poise is recovered.                               |
| Poise Percent           | The percentage of poise remaining before a stagger occurs. |
| Stagger Duration        | Duration of the stagger effect.                            |

### Status Effects
Provides a list of Status Effects assigned to the owner's Ability System Component. Entries are the `FActiveGameplayEffect`
type and will include any Gameplay Effect that contains a UI Data Component of type `GameplayEffectUIData_CombatStatus`.

The `GameplayEffectUIData_CombatStatus` can expose information such as icon, display name, and remaining time, depending 
on how it's configured. You can access this data in your widget and render it as needed.

| Property              | Description                                                        |
|-----------------------|--------------------------------------------------------------------|
| Active Status Effects | Provides all status effects relevant to the Combat User Interface. |

### Target Lock
Informs if the current target is targeted by the HUD owner (the Player). Useful for enemies showing some indication
that they are locked by the current player.

| Property               | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| Is Locked By HUD Owner | Informs if the combatant is the locked target for the HUD/widget owner. |

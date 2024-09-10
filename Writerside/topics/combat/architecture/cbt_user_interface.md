# User Interface
<primary-label ref="combat"/>

<tldr>
    <ul>
      <li>It is likely that games will need to access a combatant's Attributes to render the User Interface. These can be accessed via UMG Viewmodels</li>
      <li>Damage inputs and status effects are also commonly displayed in User Interfaces and can be accessed as well.</li>
      <li>To simplify their usage, a base (optional) widget is available to provide a function to set the owner of the backend Ability System Component.</li>
    </ul>
</tldr>

The Combat System provides a useful set of **Widgets** and **UMG Viewmodels** to expose relevant combat information to 
the player's User Interface.

## Widgets

The `NinjaCombatBaseWidget` is an optional, non-intrusive base Widget class that implements the `CombatActorAware` interface.

This interface has two functions - a _getter_ and a _setter_ for a Combat Actor, which in this context is the owner of
the Combat System Component and Ability System Component.

Once the _setter_ function is called, any UMG Viewmodels assigned to this widget will also receive the Combat Actor and
can bind to the appropriate components, so they can react to changes in the backend data.

## UMG Viewmodels

All UMG Viewmodels in the Combat System extend from `NinjaCombatViewModel`, which is also an implementation of the
`CombatActorAware` interface.

When a Combat Actor is set, each Viewmodel will bind to any relevant components, such as the Ability System Component, 
and start broadcasting changes the Widget hosting them.

### Combat Vitals

Exposes information related to a character's health.

| Property          | Description                                                |
|-------------------|------------------------------------------------------------|
| Is Dead           | Informs if the character has died (health == 0).           |
| Health            | Current Health.                                            |
| Health Percent    | Health percent in [0, 1] range. Useful for Progress Bars.  |
| Max Health Total  | Total Health, including bonuses.                           |
| Stamina           | Current Stamina.                                           |
| Stamina Percent   | Stamina percent in [0, 1] range. Useful for Progress Bars. |
| Max Stamina Total | Total Stamina, including bonuses.                          |
| Magic             | Current Magic.                                             |
| Magic Percent     | Magic percent in [0, 1] range. Useful for Progress Bars.   |
| Max Magic Total   | Total Magic, including bonuses.                            |

### Combo State

Exposes information about a combo.

| Property         | Description                                               |
|------------------|-----------------------------------------------------------|
| In Combo Window  | Informs if the character's combo window is open.          |
| Combo Count      | Current Combo Count.                                      |

### Damage

Exposes information about the last damage received, which you can also accumulate in your widget.

| Property                | Description                                           |
|-------------------------|-------------------------------------------------------|
| Received Blocked Hit    | Informs if the last hit was blocked.                  |
| Received Breaker Hit    | Informs if the last hit has broke the blocking state. |
| Received Critical Hit   | Informs if the last hit was a critical hit.           |
| Received Fatal Hit      | Informs if the last hit was fatal.                    |
| Received Staggering Hit | Informs if the last hit was staggering.               |
| Last Damage Received    | Amount of damage applied from the last hit.           |

### Poise and Stagger

| Property                | Description                                        |
|-------------------------|----------------------------------------------------|
| Is Staggered            | Indicates if the character is currently staggered. |
| Poise                   | Poise available in the Attribute Set.              |
| Poise Damage            | Current Poise Damage applied.                      |
| Poise Recovery          | How much poise is recovered.                       |
| Poise Recovery Interval | How fast poise is recovered.                       |
| Poise Percent           | Percent value for the current poise damage.        |
| Stagger Duration        | Duration of the stagger effect.                    |
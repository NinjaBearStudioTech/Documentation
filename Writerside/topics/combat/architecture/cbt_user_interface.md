# User Interface
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Most games will need to display a combatant's Attributes in the UI, which can be accessed via UMG Viewmodels.</li>
        <li>Damage inputs and status effects are also commonly displayed in User Interfaces and can be accessed as well.</li>
        <li>To simplify usage of these elements, a base (optional) widget is available to provide a function to set the owner of the backend Ability System Component.</li>
        <li>A Widget Component is also available, to automatically set Combat Actors different from the player.</li>
    </ul>
</tldr>

The Combat System provides a useful set of **Widgets** and **UMG Viewmodels** to expose relevant combat information to
the player's User Interface.

## Widgets

The `NinjaCombatBaseWidget` is an optional, non-intrusive base Widget class that implements the `CombatActorAware` interface.

This interface has two functions—a _getter_ and a _setter_ to assign and retrieve the Combat Actor (i.e., the character 
the widget represents). The Combat Actor is the owner of the Combat System Component and Ability System Component.

Once the _setter_ function is called, any UMG Viewmodels assigned to this widget will also receive the Combat Actor and
can bind to the appropriate components to react dynamically to changes in the backend data.

<img src="cbt_ui_combat_actor_widget.png" alt="Setting a Combat Actor" thumbnail="true" border-effect="line"/>

## Widget Component

The `NinjaCombatWidgetComponent` is a Widget Component you can attach to actors in the game world. It allows those actors 
to display their Combat Attributes, such as health, directly to the player.

This Widget Component sets the **Component Owner** as the **Combat Actor** to any widget added to it, which implements 
the `CombatActorAware` interface.

## UMG Viewmodels

All UMG Viewmodels in the Combat System extend from `NinjaCombatViewModel`, which is also an implementation of the
`CombatActorAware` interface.

When a Combat Actor is set, each Viewmodel will bind to any relevant components, such as the Ability System Component,
and start broadcasting changes to the hosting Widget.

To get started with the Combat Viewmodels, add a Viewmodel to your widget. For this example, we are using the Combat
Vitals View Model, which provides details about the owner's main attributes: health, stamina, and magic.

<img src="cbt_ui_viewmodel_add.png" alt="Adding the Combat Vitals Viewmodel" thumbnail="true" border-effect="line"/>

> **Viewmodel Window**
>
> To configure viewmodels, you will need the Viewmodel Window, which can be opened in `Window > Viewmodels`.

Next, you must define when the Viewmodel instance is created. For this, you have a few options, and you can read more
about them in the [official documentation][1]. For this example, we will create the Viewmodel when the Widget instance
is created.

<img src="cbt_ui_viewmodel_initialization.png" alt="Creating the Combat Vitals Viewmodel" thumbnail="true" border-effect="line"/>

The next step is to configure the **bindings** between certain Widget elements and the Viewmodel data. In this example,
we are connecting the **percent** value, for each one of the three vital attributes, to their respective progress bar
values.

<img src="cbt_ui_viewmodel_bindings.png" alt="Viewmodel Bindings" thumbnail="true" border-effect="line"/>

> **View Bindings Window**
>
> If you cannot see the View Bindings window, open it in `Window > View Bindings`.

Finally, we need to initialize the data by providing the Combat Actor that owns the Attribute System. There are two
ways to do that.

First, by setting the Widget's parent class to `NinjaCombatBaseWidget` and setting the actor to the widget. This also
initializes all Viewmodels added to the widget. A sample for this was provided in the [Widget](cbt_user_interface.md#widgets)
section above.

Alternatively, you can set the Combat Actor to the Viewmodel itself, using the same interface call.

<img src="cbt_ui_combat_actor_viewmodel.png" alt="Setting a Combat Actor" thumbnail="true" border-effect="line"/>

> **Viewmodel Initialization**
>
> When initializing the Viewmodel directly, make sure to do so after the Viewmodel is created.
>
> For example, when setting the **Creation Type** to **Create Instance**, the Viewmodel is created between the
> `PreConstruct` and `Construct` functions in the Widget.

### Combat Vitals

Exposes information related to a character's health.

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

Exposes information about a combo.

| Property         | Description                                               |
|------------------|-----------------------------------------------------------|
| In Combo Window  | Informs if the character's combo window is open.          |
| Combo Count      | Current Combo Count.                                      |

### Damage

Exposes information about the last damage received, which can be accumulated in your widget to display cumulative damage.

| Property                | Description                                            |
|-------------------------|--------------------------------------------------------|
| Received Blocked Hit    | Informs if the last hit was blocked.                   |
| Received Breaker Hit    | Informs if the last hit has broken the blocking state. |
| Received Critical Hit   | Informs if the last hit was a critical hit.            |
| Received Fatal Hit      | Informs if the last hit was fatal.                     |
| Received Staggering Hit | Informs if the last hit was staggering.                |
| Last Damage Received    | Amount of damage applied from the last hit.            |

### Poise and Stagger

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

| Property              | Description                                                        |
|-----------------------|--------------------------------------------------------------------|
| Active Status Effects | Provides all status effects relevant to the Combat User Interface. |

### Target Lock

| Property               | Description                                                             |
|------------------------|-------------------------------------------------------------------------|
| Is Locked By HUD Owner | Informs if the combatant is the locked target for the HUD/widget owner. |

<seealso style="cards">
    <category ref="related">
        <a href="cbt_attributes.md" summary="Details about the Damage and Defense design."/>
    </category>
    <category ref="external">
        <a href="https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel" summary="Official documentation for UMG Viewmodels.">UMG Viewmodels</a>
    </category>
</seealso>

[1]: https://dev.epicgames.com/documentation/en-us/unreal-engine/umg-viewmodel

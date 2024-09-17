# Poise and Stagger
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li>Poise is represented by <b>Gameplay Attributes</b>: <code>Poise</code>, <code>PoiseDamage</code> and <code>PoiseRecovery</code>.</li>
        <li>Poise starts at <code>zero</code> and can be filled by attacks using the <code>DamagePoise</code> <b>Combat Effect</b>.</li>
        <li>Once Poise reaches the <b>maximum value</b>, the character is <b>Staggered</b>.</li>
        <li>Poise can be automatically recovered, also via the <code>ReplenishPoise</code> <b>Combat Effect</b>.</li>
        <li>Stagger is represented by the <code>Stagger</code> <b>Combat Ability</b>, activated via the <code>Staggered</code> <b>Combat Effect</b>.</li>
        <li>All details about the Poise and Stagger are accessible to the UI via the <code>PoiseAndStagger</code> <b>View Model</b>.</li>
        <li>Poise and Stagger is an <b>optional</b> feature, you are not required to use it.</li>
    </ul>
</tldr>

Everytime damage is inflicted, you can optionally apply **Poise Damage** to the target. Once this damage reaches the 
Poise threshold, the target is **Staggered**.

This feature is configured via **Attributes**, **Gameplay Effects** and the **Stagger Ability**.

## Managing Poise

Poise is managed by the following **Gameplay Attributes**, introduced by the **[Combat Attribute Set](cbt_attributes.md)**.

1. **Poise**: The **threshold** of when a character will **stagger**.
2. **Poise Damage**: Current amount of damage inflicted to the Poise. Once it reaches the _threshold_, the character will **stagger**.
3. **Poise Recovery**: How much of the Poise Damage is **recovered**, after a period of time without taking more **damage**.
4. **Poise Recovery Interval**: Interval between an attack and recovery to resume.

> **Usual Poise Values**
> 
> It's common to set **Poise** and **Poise Recovery** to the same value, so the character can fully recover right away, 
> but you can adjust these values to fit your design.
> 
> As for the **Poise Damage**, an initial value of zero would be common, unless you need a character to have a predefined 
> tendency to be quickly staggered. 

During gameplay, these values are affected via **Gameplay Effects**. The Combat System provides the following Gameplay 
Effects to manage Poise:

| Gameplay Effect       | Description                                                                                                                      |
|-----------------------|----------------------------------------------------------------------------------------------------------------------------------|
| `DamagePoise`         | Applies an amount of damage to the target's **Poise**. Commonly used in conjunction with **Melee** or **Ranged** damage effects. |
| `RecoverPoise`        | Periodically recovers **Poise**, by the amount set in the **Poise Recovery** attribute.                                          |
| `CancelPoiseRecovery` | Temporarily **interrupts recovery**. Usually applied in conjunction with **Damage Poise**.                                       |

> **Melee and Ranged Damage**
> 
> The Gameplay Effects provided by the Combat System for **Melee** and **Ranged** are subclasses of the **Damage Poise**
> Gameplay Effect, so they are already configured to apply Poise Damage.

## The Stagger State

Once a Combatant's **Poise Damage** reaches the threshold represented by the **Poise** attribute, they will enter the
**Stagger** state.

During this state, a Combatant will not be able to perform any action, becoming highly **vulnerable** for its duration, 
which is defined by the <code>StaggerDuration</code> Gameplay Attribute, introduced by the **[Combat Attribute Set](cbt_attributes.md)**.

The state is represented by the **Staggered Gameplay Effect**. The addition or removal of the related **Gameplay Tags**
will activate and cancel the **Stagger Ability**, which will execute the following:

1. Interrupt any ongoing actions.
2. Block any new actions for the duration of the state.
3. Cancel Poise Recovery.

### Looping Animation

For the Stagger State, it is recommended that you use an Animation Montage with a Looping section configured. This is
useful since the duration of the Stagger State is **dynamic**. 

The **Animation Instance** provided by the Combat System, `NinjaCombatAnimInstance` already tracks this state, which is
exposed by the `bStaggered` property.

<img src="cbt_stagger_anim_instance.png" alt="Animation State for Stagger" thumbnail="true" border-effect="line"/>

## Gameplay Effects

The Combat System provides many **Gameplay Effects** used to implement Poise and Stagger.



## Tracking Poise and Stagger

To create something like a **Progress Bar**, representing the current Poise Damage, the provided **View Model** can be
used.

This View Model provides the following values that can be used for **Property Binding** in **Widgets**.

1. **Poise**: Current value for the **Poise** Gameplay Attribute.
2. **Poise Damage**: Current value for the **Poise Damage** Gameplay Attribute.
3. **Poise Recovery**: Current value for the **Poise Recovery** Gameplay Attribute.
4. **Poise Recovery Interval**: Current value for the **Poise Recovery Interval** Gameplay Attribute.
5. **Poise Percent**: The proportion of **Poise Damage**, based on **Poise**, in **[0, 1]** range.
6. **Is Staggered**: Informs if the character is currently **staggered**.
7. **Stagger Duration**: The **duration** for the Stagger state.
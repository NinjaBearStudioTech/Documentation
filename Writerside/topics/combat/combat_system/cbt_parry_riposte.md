# Parry and Riposte
<primary-label ref="combat"/>

<tldr>
    <ul>
        <li><b>Parry Windows</b> define when an attacker is vulnerable to counters and can be configured via <b>Melee Scans</b> or a dedicated <b>Notify State</b>.</li>
        <li><b>Parry Scans</b> are triggered by defenders to detect and respond to enemies with an active Parry Window.</li>
        <li>Successful parries grant a <b>Riposte Opportunity</b>, allowing a powerful follow-up attack within a limited window.</li>
        <li>Each step - Parry Window, Parry Ability, Riposte Opportunity, and Riposte Ability - can be configured <b>independently</b> to suit your combat design.</li>
    </ul>
</tldr>

A **parry** is a defensive mechanic where a well-timed **counter** can **interrupt** an enemy's attack and place them in 
a **vulnerable state**. This vulnerability often creates an opportunity for a powerful follow-up, such as a **riposte** 
that deals additional damage or triggers a special animation.

These concepts have been made widely popular by _soulslike_ games, where precision, patience, and mastery of timing are
rewarded with satisfying and impactful responses.

While the terms "parry" and "riposte" are genre-inspired, the system is flexible. You can simply think of them as
**counters** and **follow-up attacks**, making them suitable for a variety of combat styles and game types beyond just
soulslike design.

## Parry Window
A Parry Window defines the **opportunity window** for a target to successfully execute a **parry**. This window can be 
set in two ways: by using the **Melee Scan Animation Notify State**, or a dedicated **Parry Window Animation Notify State**.

### Melee Scan Animation Notify State
Parry windows are often tied to a melee scan, since the opportunity to counter typically aligns with the moment an attack 
can apply damage.

<procedure title="Setting a Melee Scan as a Parry Window" collapsible="true" default-state="expanded">
    <step>Open an <b>Animation Montage</b> that already has a <b>Melee Scan</b> configured.</step>
    <step>
        <p>In the list of <b>Melee Scan Tags</b>, add <code>Combat.State.Parry.Victim</code>. This marks the attacker as vulnerable to a <b>Parry</b> for the duration of the scan.</p>
        <img src="cbt_wpatk_parry_riposte_melee_scan.png" alt="Parry Window and Melee Scan" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

This approach is simple and works well in many cases, but it comes with two important caveats:

1. Since the Parry Window overlaps with the damage frames, players must be **extremely precise**. A mistimed but technically successful parry may still result in taking full damage.
2. You cannot display a dedicated **Gameplay Cue** for the Parry Window unless it shares the same cue as the Melee Scan.

If precision and feedback are important in your design, consider using a separate **Parry Window Animation Notify State** instead.

### Parry Window Animation Notify State
Ninja Combat provides a dedicated Notify State for the Parry Window. You can place this Notify **just before** the Melee 
Scan, giving players a small lead-in window to successfully parry before the attack becomes dangerous.

This Notify State also supports a dedicated **Gameplay Cue**, which can be used to visually or audibly notify players of 
the parry opportunity.

<procedure title="Configuring the Parry Window" collapsible="true" default-state="expanded">
    <step>Open an <b>Animation Montage</b> that includes a <b>Melee Scan</b>.</step>
    <step>
        <p>Add the <b>Parry Window Animation Notify State</b> just before the scan. You may also assign a Gameplay Cue to signal the window to players.</p>
        <img src="cbt_wpatk_parry_riposte_parry_window.png" alt="Standalone Parry Window" border-effect="line" thumbnail="true"/>
    </step>
</procedure>

As long as your Attack Ability is already configured, this is all that's needed to make the attack vulnerable to parries.

## Parry Scans
With the **Parry Window** configured on the attacker, it’s time to handle the **defender's side** who will be executing 
a **Parry Counter**. This is done using a **Parry Scan**, which works similarly to a Melee Scan.

A **Parry Scan** searches for a **viable Parry target**, typically the attacker currently in a Parry Window, and triggers 
the counter effect when the scan is successful. These scans are configured in the **Parry Counter animation montage**, 
usually played during a successful parry response.

<procedure title="Configuring Parry Scans" collapsible="true" default-state="expanded">
    <step>
        <p>Open the <b>Animation Montage</b> that represents the Parry Counter ability (the animation played by the defender after a successful parry).</p>
    </step>
    <step>
        <p>Add the <b>Parry Scan Animation Notify State</b> to the frames that should trigger the scan.</p>
        <img src="cbt_wpatk_parry_riposte_parry_scan.png" alt="Parry Scan Notify State" border-effect="line" thumbnail="true"/>
    </step>
    <step>
        <p>In the Configuration Panel, set the <b>Weapon Query</b> to find the correct defensive item, usually the shield equipped by the character.</p>
        <img src="cbt_wpatk_parry_riposte_parry_scan_query.png" alt="Weapon Query for Parry Scan" border-effect="line" thumbnail="true"/>
    </step>
    <step>Set the <b>Scan Channel</b> to <code>CombatObject</code>, ensuring it detects combatants that can be parried.</step>
    <step>Choose an appropriate <b>collision shape</b> (such as a box or capsule) that accurately represents the parry area—this is often the shield or arm sweep zone.</step>
</procedure>

Once configured, this scan will actively look for a target with an **active Parry Window** during the scan’s active frames, 
allowing the counter to be performed if a valid target is found.

## Parry Ability
With the **Parry Scan** configured, the next step is to create the **Parry Ability**, which is similar to a standard Melee 
Attack but includes additional options specific to parry behavior.

| Property                      | Description                                                                                                                                                                                  |
|-------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Successful Parry Effect Class | The **Gameplay Effect** applied to the avatar when a parry is successfully executed. This can include buffs or status effects.                                                               |
| Successful Parry Effect Level | The level at which the successful parry effect is applied.                                                                                                                                   |
| Remove Riposte Effect         | If set to **true**, this will remove any **Riposte Chance** effect. You typically don't want to set this in a Parry Ability, but it may be useful in attacks that consume the Riposte state. |

<procedure title="Creating a Parry Ability" collapsible="true" default-state="expanded">
  <step>Create a new <b>Gameplay Ability</b> based on <code>CombatAbility_Parry</code>.</step>
  <step>Assign the <b>Animation Montage</b> that includes the <b>Parry Scan Notify State</b>.</step>
  <step>Grant this ability to your character and assign it to the appropriate <b>input action</b>.</step>
  <img src="cbt_wpatk_parry_riposte_parry_ability.png" alt="Parry Ability Setup" border-effect="line" thumbnail="true"/>
</procedure>

At this point, you have a complete implementation of a **Parry System**, where an enemy can expose a **Parry Window**, 
and the player can respond with a **Parry Ability** that detects and reacts to it.

Next, let’s look at the **Riposte**, the powerful counterattack that usually follows a successful parry.

## Riposte Opportunity
Once a **successful parry** is detected, the **Combat Manager** applies a **Riposte Opportunity** to its owner. This 
signals a limited window during which a **Riposte Attack** can be executed.

By default, the **Riposte Opportunity** is represented by the `CombatEffect_RiposteOpportunity` Gameplay Effect. This 
effect is configured in the **Combat Manager**, and its duration is defined by the `RiposteWindowDuration` **Gameplay 
Attribute**, which you can tune to fit your game’s timing and difficulty.

The opportunity ends either when the **duration expires** or when an **ability consumes it**, such as the dedicated 
**Riposte Ability**.

> **Creating Riposte Opportunity Windows**  
> 
> The presence of the `Combat.Opportunity.Riposte` tag on the character, determines a **Riposte Opportunity Window**. 
{style="note"}

## Riposte Ability
Finally, let's discuss the **Riposte Ability**, which is also a special type of attack with a few additional options:

| Property                        | Description                                                                |
|---------------------------------|----------------------------------------------------------------------------|
| Successful Riposte Effect Class | Gameplay Effect applied to the avatar on a successful riposte.             |
| Successful Riposte Effect Level | Level for the Gameplay Effect applied.                                     |
| Remove Riposte Effect           | If true, removes a Riposte Chance. This is usually set in Riposte attacks. |

<procedure title="Creating the Riposte Ability" collapsible="true" default-state="expanded">
    <step>Prepare an <b>Animation Montage</b> for your attack. There are no special requirements for this montage.</step>
    <step>Create a <b>Gameplay Ability</b> based on <code>CombatAbility_Riposte</code>.</step>
    <step>Set the Animation Montage you created in the ability.</step>
    <step>Add the ability to the character and configure the necessary input mapping.</step>
    <img src="cbt_wpatk_parry_riposte_riposte_ability.png" alt="Riposte Ability Setup" border-effect="line" thumbnail="true"/>
</procedure>

> **Activation Required Tags**  
> 
> Note that `Combat.Opportunity.Riposte` is listed under the ability's **Required Tags**!
> 
> This tag represents the **Riposte Opportunity** and ensures the ability is only available during that window.  
{style="tip"}

This finishes a basic setup for **Parry and Riposte**. At this point, the full system should now be functional in your project.


# Lazy Loading
<primary-label ref="gas"/>
<secondary-label ref="advanced"/>
<secondary-label ref="experimental"/>

You may have multiple actors in the world that may require their own Ability System Component. However, having multiple 
instances of the ASC can be heavy, potentially leading to performance issues. Lazy Loading can help alleviating that problem.

> **Fortnite Use Case**
>
> In Fortnite, multiple actors can exist in the map and the ASC may never actually be used. This is a common use case 
> for a lazy-loading implementation, in which these actors only have their ASC loaded the first time any interaction
> happens, such as applying damage.

The default actor provided by Ninja GAS, `NinjaGASActor`, supports this design pattern, allowing you to define for each
actor type the **initialization mode** for the Ability System Component:

- **Lazy**: The Ability System Component is only initialized when used for the first time. This is the default setting for `NinjaGASActor` blueprints.
- **Eager**: The Ability System Component is initialized as soon as possible.

> **Lazy versus Eager**
>
> Lazy initialization is ideal for non-critical or infrequently used actors, while eager initialization suits primary
> characters or core gameplay elements that need immediate ASC access.
{style=note}

## Default Ability Data

The base `NinjaGASActor` does not include an instance of the Ability System Component in the editor's Defaults pane. 
This means you cannot directly assign the**[Data Asset](gas_data_asset.md)** to the ASC within the editor

As an alternative to that, this base actor class implements `AbilitySystemDefaultsInterface`, which allows blueprints to
set the appropriate Data Asset directly in the Actor Property `DefaultAbilitySetup`.

Alternatively, you can create your own version of the Ability System Component, already set with the appropriate Data
Asset to be used during the initialization.

## Attribute Sets

Because the Ability System Component might not yet be initialized when a Gameplay Effect is applied to an actor, Attributes 
must be stored in a temporary structure and later on applied to the newly-create ASC.

The framework will handle this for you, but you **must change the macro used in your Replication Notifies**. Instead of
using `GAMEPLAYATTRIBUTE_REPNOTIFY`, you should use `LAZY_GAMEPLAYATTRIBUTE_REPNOTIFY` instead.

> **Eligible Attribute Sets**
> 
> This change is only relevant to attributes that will be used by an actor that supports lazy loading. Other Attribute 
> Sets expected to be used with a main character, such as the Combat Attribute Set for example, would not need this
> change.
{style=note}

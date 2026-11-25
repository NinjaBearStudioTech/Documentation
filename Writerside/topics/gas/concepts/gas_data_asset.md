# Setup Data, Bundles, and Loading
<primary-label ref="gas"/>

A **G.A.S. Setup** asset is an ability bundle. Reuse one for characters that start with the same abilities and values. Registering the asset makes it available in a packaged game. Its entries take effect when the actor's Ability System Component initializes with that bundle.

| Bundle entry | Example | What the component does |
| --- | --- | --- |
| **Default Attribute Sets** | Energy starts at 25. | Creates the set and reads starting values from its optional **AttributeMetaData** table. |
| **Default Gameplay Effects** | A guard starts on duty. | Applies the effect to the owner at the configured level. An infinite effect can grant a tag for as long as it stays active. |
| **Default Gameplay Abilities** | The guard can recover energy. | Grants the ability at the configured level. Ordinary abilities wait for activation. |

The server grants starting effects and abilities. **Instantiation Scope** controls where an Attribute Set is created. Choose **Both** for the usual shared setup. A set used for server-only bookkeeping can use **Server**. Follow the set's own replication rules for values a client needs to display.

## Which Bundle Is Used?

For owner defaults, the component first checks whether its owner provides a bundle, then falls back to the component's **Default Ability Setup**. When the avatar is a different actor, its bundle adds a second set of grants. Put each Attribute Set class in one place so the component has a single instance to initialize.

Use the owner bundle for values shared across lives. **Respawn Policy** offers **Keep** and **Reset** for attribute sets. For a value that must survive a pawn swap, put its set on the persistent owner, select **Keep**, and leave full reset on avatar change off. Put values specific to a given pawn in its avatar bundle.

The supplied character classes expose **Default Ability Setup** to Blueprint authors. For a custom C++ owner or avatar, implement `IAbilitySystemDefaultsInterface::GetAbilityData() const` and return your `UNinjaGASDataAsset`. For example, a pilot and a vehicle can each supply a different bundle while the Player State keeps the shared component.

## When Grants Are Ready

A lazy world actor can have a bundle assigned before it has a component. A player pawn can exist on the client before its Player State arrives. [Wait for the ability system](gas_first_steps.md) before reading attributes, and check for the particular ability before enabling its button. In C++, `OnAbilityGiven()` on the Ninja component reports individual grants. [Grant Starting Attributes and Abilities](gas_guide_starting_abilities.md) shows how to use it.

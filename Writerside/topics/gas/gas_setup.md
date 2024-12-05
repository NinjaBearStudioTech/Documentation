# Setup
<primary-label ref="gas"/>

<tldr>
    <ul>
        <li>Install the Ninja G.A.S. plugin using the Epic Games Launcher.</li>
        <li>Open your project and enable the plugin: <code>Edit</code> &rightarrow; <code>Plugins</code>, search for <i>gas</i>, and tick the checkbox for <b>Ninja G.A.S.</b> and restart the engine.</li>
        <li>Use the Base Class table to create your Actors, Pawns, Characters and Player States from the correct classes.</li>
    </ul>
</tldr>

## Installing the Plugin

Once acquired, the plugin can be installed via the **Epic Games Launcher**. As with any **Code Plugin**, it can be
installed to any compatible engine version.

Once installed, create or open your project and navigate to **Edit** and then **Plugins**. In the search bar, type
_gas_ and the **Ninja G.A.S.** plugin should appear. Tick the checkbox and restart the engine.

## C++ Libraries

If you plan to work with C++ and use classes from the GAS System, ensure you add the following modules to your
`Build.cs` file:

<tabs group="sample">
    <tab title="Build.cs">
        <code-block lang="c#">
        PublicDependencyModuleNames.AddRange(new []
        {
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "NinjaGAS"
        });
        </code-block>
    </tab>
</tabs>

## Asset Manager

The GAS System uses a **Primary Data Asset** and **soft references** to initialize common abilities elements for actors,
and you need to register this Primary Data Asset to the Asset Manager.

In the Editor, configure the **Asset Manager** by navigating `Edit` > `Project Settings` > `Asset Manager`, and then
adding the following asset.

| Asset Name          | Base Class           | Description                                                |
|---------------------|----------------------|------------------------------------------------------------|
| `AbilityBundleData` | `UNinjaGASDataAsset` | Bundles all Attribute Sets, Effects and Abilities to give. |

Once configured, your entry in the Asset Manager should look like this:

![Ability Bundle Data Asset Setup](gas_setup_data_asset.png "Ability Bundle Data Asset Setup")

> **Asset Directory**
> 
> If you have a specific **directory** for your Data Assets, like in the example above, make sure to set that in the
> Primary Asset type registry as well.

## Ability System Initialization

Projects using the Gameplay Ability System must initialize the **Global Data**. This framework will automatically do that,
when its **Subsystem** initializes. **No additional steps are necessary**.

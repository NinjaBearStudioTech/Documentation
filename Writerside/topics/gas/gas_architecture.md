# Architecture
<primary-label ref="gas"/>

This section includes **deep dive** on important **technical aspects** of the GAS Wrapper.

**[](gas_data_asset.md)**
: On top of common ways that you can add Gameplay Abilities to an actor, Ninja GAS allows you to set **Attribute Sets**, 
**Gameplay Effects**, **Gameplay Abilities** and **loose replicated tags** using a **Data Asset**.

**[](gas_base_classes.md)**
: This topic will walk you through all the **base classes** that can be used to create your Actors, Pawns or Characters.
They will provide an Ability System Component out of the box for you, ready-to-use.

**[](gas_artificial_intelligence.md)**
: If you have AI Agents in your projects, then most likely you will need them to activate abilities or other tasks that
might require attribute information. Ninja GAS provides such features for both **Behavior and State Trees**.

**[](gas_local_gameplay_cues.md)**
: Similar to the Batch Activation, Gameplay Cues may be heavy on the network and since these are cosmetics, the Gameplay
Ability System will reinforce certain limitations. To circumvent that, we can use **local Gameplay Cues**.

**[](gas_batch_activation.md)**
: In some cases, you might need to activate **multiple abilities together**, but considering that each local activation
will trigger an RPC, it is a good practice to activate them together. Ninja GAS supports batch activation.

**[](gas_lazy_loading.md)**
: You may have multiple actors in the world that may require their own Ability System Component. However, having multiple
instances of the ASC can be heavy, potentially leading to performance issues. Lazy Loading can help alleviating that problem.
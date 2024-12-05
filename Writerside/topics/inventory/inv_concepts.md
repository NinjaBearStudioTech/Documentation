# Concepts
<primary-label ref="inventory"/>

This section includes **high-level concepts** for the Inventory System. These elements are provided by an aggregation of
multiple technical elements, such as **components** and **gameplay classes**.

**[](inv_container_and_layout.md)**
: Containers are "parts" of the inventory that can **store items**. Containers can be added to an inventory using
certain functions, from items, or via an **Inventory Layout**.

**[](inv_items_and_fragments.md)**
: Items are the most common entity in an Inventory System. Ninja Inventory proposes _aggregation_ as a way to create 
your items, by adding multiple **fragments** to them.

**[](inv_inventory_manager.md)**
: Items added to the Inventory are managed by the **Inventory Manager** component. This component is responsible for 
managing and replicating items between the owner and the server.

**[](inv_equipment.md)**
: Items are **data objects**. They do not have a physical representation unless they have an **Equipment** configured.
Equipments are visual configurations of items, that may include multiple **states** and **actors**.

**[](inv_equipment_manager.md)**
: Analogous to the Inventory Manager, the Equipment Manager handles **Equipment instances**. It is also responsible for
replication, but this time, for all relevant actors in the game.

**[](inv_loot_management.md)**
: Loot is a dedicated entity that includes selection logic for items and their quantities, along with dedicated ways to
adding generated loot to the inventory. 
# Guides and Showcase 

<img src="sc_banner_01.png" alt="Showcase"/>

The **Showcase Project** can be downloaded so you can test the tech by playing a small, yet fully realized game project.
The showcase is also the reference project used in the following **guides**.

These guides are focused on the **Ninja Bear Studio plugins** and expect previous knowledge on other aspects of the 
Unreal Engine, such as creating common objects and their hierarchies, working with Animation Blueprints, basics of the
Gameplay Ability System, and so on.

## Part 1

**[P01.G01: Configure Input Handlers](p01g01_configure_inputs.md)**  
: Configure **Ninja Input** and replace the default configuration from a project, such as the Third Person Template, so 
it will use **Input Handlers** and an **Input Setup**.

**[P01.G02: Configure the Gameplay Ability System](p01g02_configure_gas.md)**  
: Using **Ninja GAS**, you can configure the Gameplay Ability System in your project and prepare your Player Character, 
so it can use the Combat Attribute Set provided by **Ninja Combat**.

**[P01.G03: Create Melee Weapons](p01g03_create_melee_weapons.md)**  
: After configuring the initial **Combat Components**, the first step in Ninja Combat is to prepare your character for 
**Melee Attacks** using a **Melee Weapon**, which must be registered with the **Weapon Manager**.

**[P01.G04: Create Melee Attacks](p01g04_create_melee_attacks.md)**  
: With the **melee weapons** configured, the next step is to create a **primary** and a **secondary** attack using the
**Attack Ability**, add these abilities to the player character using **Ninja GAS** and configure their inputs using
**Ninja Input**.

**[P01.G05: React to Incoming Damage](p01g05_react_to_player_damage.md)**  
: To make sure that our attacks work, we need an enemy. Using concepts established before, we will create a new enemy 
character that properly **reacts to incoming damage** from player attacks.

**[P01.G06: React to Fatal Damage](p01g06_react_to_fatal_damage.md)**  
: Continuing the damage handling, we will handle fatal damage, which starts the death flow and activates the 
**Death Ability**.

**[P01.G07: Create a Combo](p01g07_create_primary_combo.md)**  
: The **Combo System** is used to trigger attack sequences that can even branch out depending on different inputs. In this
guide you will learn more about it and how to mix **Attack** and **Cast** abilities in a combo.

**P01.G08: Opportunity System**  
: Since enemies can be consistently staggered, this is a good moment to introduce the **Opportunity Attack** system. It
will be used to create an execution with **paired animations** and a **cinematic camera**.

## Part 2

**P02.G01: Target Lock System**  
: The **Target Lock Ability** helps with camera focus, precision and add visual indicators to a target. This system uses 
Unreal Engine's **Gameplay Targeting System** to collect targets.

**P02.G02: Motion Warping**  
: Motion Warping can adjust **root motion animations** to **shorten** or **stretch** their movement, so they will 
properly reach targets. 

**P01.G03: Track enemy attributes**  
: Going a step further in the enemy configuration, it is now time to learn how to use the provided **Widgets** and
**Viewmodels** to track the enemy's **health**, **stagger**, and **incoming damage**.

**P01.G04: Track player attributes**  
: Still in the **user interface** topic, let's create more visual elements, but this time to track the **Player's Vitals**.
Once again, using **Viewmodels**, we will create progress bars for **Health**, **Stamina**, and **Magic**.

**P02.G05: Configure the Inventory**  
: To create our **secondary weapon**, we should have **Ninja Inventory** configured. So this is our next task: perform the 
setup, update the **Weapon Manager**, and convert our weapons into **Items** and **Equipment**.

**P02.G06: Switch Weapons**  
: Let's create a new weapon that will enable us to work with projectiles. Once that is done, we will configure the 
**Equipment Ability** to switch weapons and also their **Abilities** and **Animation Layers**.

**P02.G07: Create a Projectile**  
: With the new weapon configured and usable, we will create a **Projectile** and the appropriate **Attack Ability** to use 
it, utilizing the camera as an **aiming mechanism**.

**P02.G08: Area of effect and targeting**  
: Let's look into the secondary ability to the ranged weapon. It will allow us to explore the integration with the **Gameplay
Ability System Targeting**, in conjunction with the **Cast Ability**.

## Part 3

**P03.G01: Actor Pooling**  
: We have recurring actors for projectiles and the Cast ability in the Combo. Let's use the **Actor Pooling** to make sure
that these are pre-spawned, and we can avoid the constant spawning/destruction overhead.

**P03.G02: Configure the Weapon UI**  
: Using Inventory Widgets, we can create a simple user interface that indicates which weapon is currently in use and
other features, such as arrows for the bow.

**P03.G03: Inventory interface**  
: With two armor sets and two weapon sets, we can build our **Inventory UI** to allow managing these properly. This will
use the **Inventory Viewmodels**, including their **drag and drop** functionality.

**P03.G04: Mesh swapping**  
: Since we can swap inventory meshes, it means we also need to control how our character looks when not wearing any armor.
So we need to revisit the **Inventory and Equipment setup** and configure **default meshes**.

**P03.G05: Stacks and Consumable Items**  
: Using the **consumable fragment**, we will look into potions that can be consumed by the player. We will also configure
the arrows as a stackable item that we can adjust as they are used.

**P03.G06: Configuring Damage and Armor**  
: Let's add random stats for the weapons and armor. This will be done using Item Fragments that can select random values
from pre-defined ranged.

**P03.G07: Weight and Quality**  
: In this guide we'll add other variants of the weapons and armor, ranging from light and heavier armor pieces and with
varying quality levels.

**P03.G08: Item Pickups**  
: Now that it's possible to properly perform inventory management, and we have a certain item variety, it's time to
configure **item drops** from the defeated enemies, including a configuration of their **loot tables**.

## Part 4

**P04.G01: Configure Factions**  
: The AI uses **teams** to determine their attitudes towards other Controllers. We will use **Ninja Factions** to configure
the alignment between **players** and **enemies**.

**P04.G02: Currency and reputation**  
: Now that we have a stable Combat, Inventory, and Bot setup, let's configure our project so that whenever an enemy is
killed, the character will receive a **bounty** and increase its reputation with the **Merchant Faction**.

**P04.G03: Configure the AI Agent**  
: In this step, we will introduce **Ninja Bot** to the project and perform the first few steps to make our enemy react to
the player. This includes configuring the **Bot Controller** and using the **data-driven perception setup**.

**P04.G04: Create Enemy attacks**  
: Now that the enemy can detect and perceive the player as an opponent, we can configure a weapon and a couple of **Attack
Abilities** that can be used in the enemy's **Behavior Tree**.

**P04.G05: Block enemy damage**  
: Now that the enemy can attack, we will introduce the **Block Ability**, which mitigates damage. Then, we will add a **Hit
Reaction Ability** to the player, including two important damage types: **Block** and **Breaker**.

**P04.G06: Evades and invulnerability**  
: Continuing on the defense mechanisms, we will configure an **Evade Ability**, including **invulnerability** during some 
animation frames. Evades can be **directional** when locked on targets.

**P04.G07: Parry and counter-attacks**  
: Now that enemies can perform attacks, the player can **parry** and **counter-attack**. In this context, this can be used 
to greatly increase the enemy's **stagger bar**.

**P04.G08: Token management system**  
: To better organize the AI behavior, we will use the **AI Token Management** system from **Ninja Bot**. This will make 
agents only act when they have the appropriate **Action Tokens**, or request them when needed.


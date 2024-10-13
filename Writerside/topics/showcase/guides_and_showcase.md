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

**[P01.G05: React to Player Damage](p01g05_react_to_player_damage.md)**  
: To make sure that our attacks work, we need an enemy. Using concepts established before, we will create a new enemy 
character that properly **reacts to incoming damage** and eventually dies.

**P01.G06: Track enemy attributes**  
: Going a step further in the enemy configuration, it is now time to learn how to use the provided **Widgets** and 
**Viewmodels** to track the enemy's **health**, **stagger**, and **incoming damage**.

**P01.G07: Track player attributes**  
: Still in the **user interface** topic, let's create more visual elements, but this time to track the **Player's Vitals**. 
Once again, using **Viewmodels**, we will create progress bars for **Health**, **Stamina**, and **Magic**.

**P01.G08: Create a combo**  
: For now, we only have a light and a heavy attack. Here we will replace the primary attack with a **combo** that will 
activate a different **light attack** after each button press and optionally, a **heavy attack**.

## Part 2

**P02.G01: Motion Warping**  
: Motion Warping can adjust **root motion animations** to **shorten** or **stretch** their movement so it will properly
reach certain targets. Let's add this to our attacks so they are more **precise**.

**P02.G02: Configure the Inventory**  
: To create our **secondary weapon**, we should have **Ninja Inventory** configured. So this is our next task: perform the 
setup, update the **Weapon Manager**, and convert our weapons into **Items** and **Equipment**.

**P02.G03: Switch Weapons**  
: Let's create a new weapon that will enable us to work with projectiles. Once that is done, we will configure the 
**Equipment Ability** to switch weapons and also their **Abilities** and **Animation Layers**.

**P02.G04: Create a projectile**  
: With the new weapon configured and usable, we will create a **Projectile** and the appropriate **Attack Ability** to use 
it, utilizing the camera as an **aiming mechanism**.

**P02.G05: Configure Factions**  
: The AI uses **teams** to determine their attitudes towards other Controllers. We will use **Ninja Factions** to configure 
the alignment between **players** and **enemies**.

**P02.G06: Configure the AI Agent**  
: In this step, we will introduce **Ninja Bot** to the project and perform the first few steps to make our enemy react to 
the player. This includes configuring the **Bot Controller** and using the **data-driven perception setup**.

**P02.G07: Create Enemy attacks**  
: Now that the enemy can detect and perceive the player as an opponent, we can configure a weapon and a couple of **Attack 
Abilities** that can be used in the enemy's **Behavior Tree**.

**P02.G08: Block enemy damage**  
: Now that the enemy can attack, we will introduce the **Block Ability**, which mitigates damage. Then, we will add a **Hit 
Reaction Ability** to the player, including two important damage types: **Block** and **Breaker**.

## Part 3

**P03.G01: Target Lock system**  
: The **Target Lock Ability** helps with camera focus and melee precision. This allows us to move the enemy overhead widget 
to a **Marker Actor** that is assigned to any actor being focused on by the player.

**P03.G02: Evades and invulnerability**  
: Continuing on the defense mechanisms, we will configure an **Evade Ability**, including **invulnerability** during some 
animation frames. Evades can be **directional** when locked on targets.

**P03.G03: Parry and counter-attacks**  
: Now that enemies can perform attacks, the player can **parry** and **counter-attack**. In this context, this can be used 
to greatly increase the enemy's **stagger bar**.

**P03.G04: Opportunity system**  
: Since enemies can be consistently staggered, this is a good moment to introduce the **Opportunity Attack** system. It 
will be used to create an execution with **paired animations** and a **cinematic camera**.

**P03.G05: Token management system**  
: To better organize the AI behavior, we will use the **AI Token Management** system from **Ninja Bot**. This will make 
agents only act when they have the appropriate **Action Tokens**, or request them when needed.

**P03.G06: Loot chest**  
: Next, we will create a **loot chest** that can be opened when the enemies are defeated. It will contain a **new armor 
set** that can be worn by players who prefer using the secondary weapon.

**P03.G07: Inventory interface**  
: With two armor sets and two weapon sets, we can build our **Inventory UI** to allow managing these properly. This will
use the **Inventory Viewmodels**, including their **drag and drop** functionality.

**P03.G08: Mesh swapping**  
: Since we can swap inventory meshes, it means we also need to control how our character looks when not wearing any armor. 
So we need to revisit the **Inventory and Equipment setup** and configure **default meshes**.

## Part 4

**P04.G01: Area of effect and targeting**  
: Let's finally add a secondary ability to the ranged weapon. It will allow us to explore the integration with the G.A.S. 
**Targeting System**, used in conjunction with the **Cast Ability**.

**P04.G02: Actor pooling**  
: Now that some actors were introduced for ranged attacks, cast attacks, and targeting, we can add an **Actor Pool** to 
the player character, which will avoid some of the performance costs of spawning and destroying actors.

**P04.G03: Consumable items**  
: With the main combat and inventory functionalities stable, we can introduce new elements such as **consumable items**. 
So let's create some potions to restore the player's vital attributes.

**P04.G04: Currency and reputation**  
: Now that we have a stable Combat, Inventory, and Bot setup, let's configure our project so that whenever an enemy is 
killed, the character will receive a **bounty** and increase its reputation with the **Merchant Faction**.

**P04.G05: Configure interactions**  
: Next, we will introduce **Ninja Interaction** and create a reputation-based **vendor**. This vendor will sell potions 
and other items based on the player's **reputation**.

**P04.G06: Mounts**  
: Mixing **Input** and **Interaction**, let's move our vendor to a bit farther away on the map and allow the player to 
acquire a **mount** that will make it easier to travel between the vendor area and the enemy base.

**P04.G07: AI Strategy**  
: To create a better game loop, we need to allow the enemies to respawn after some time. We will do this using Ninja Bot's 
**Territory** and **Strategy** systems.

**P04.G08: Respawn and Save System**  
: We haven't properly handled **Player Death** and the **save and load** systems. Let's implement that to finish this 
first pass on the main game loop.


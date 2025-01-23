# Gameplay Abilities
<primary-label ref="interaction"/>

## Find Interactable Actor

This Ability should be always granted to characters that will be able to **trigger interactions**. Whenever their 
**Interaction Manager** component detects the first eligible Interaction Target, this Ability will be activated via a
**Gameplay Event** and start sorting all available targets based on certain conditions.

Once an Interaction Target is selected, it will receive **focus**, allowing characters to start the interaction. When
this happens, this Ability will send another **Gameplay Event** meant to activate the **Execute Interaction** ability.

Conditions are represented by **Ability Tasks**. You can define the appropriate Gameplay Task in your Ability, using 
the ones provided by the framework or creating your own.

### Find Closest Interaction Target
This Ability Task will sort all Interaction Targets available and select the one closest to the target.

### Find Camera Interaction Target
This Ability Task will select the Interaction Target positioned at the center of the camera.

## Execute Interaction

This Ability effectively triggers the interaction, for a target provided via a **Gameplay Event**. It will orchestrate
the integration with the **Gameplay Behavior** set in the **Smart Object**.
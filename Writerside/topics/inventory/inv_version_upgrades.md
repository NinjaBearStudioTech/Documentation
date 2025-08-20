# Version Upgrades
<primary-label ref="inventory"/>

> **Back up first!**
>
>Before migrating to a newer version, it is highly recommended that you back up your project first!  
{style="warning"}

## 1.0 to 2.0
2.0 is a full rewrite. Install the new version, then update your project to match the new concepts/APIs. There is no 
compatibility layer. Minimal upgrade flow:
- Install/enable 2.0 in your project.
- Go through the updated setup pages.
- Fix build settings: ensure your modules reference the new inventory modules you use.
- Open your main maps/Blueprints and resolve compile errors by following the migration points.
- Run and verify basic flows such as add item, equip, remove, container events.

### Key migration points
- Fragments have new modules.
- Delegates are centralized in the Inventory Manager (BP + Native)
- Equipment Data Asset removed, configure in the Equipment Fragment
- Inventory Layouts (do not confuse with the new Container Layouts)
- Simplified Widgets; UI moved to ViewModels + Inventory Resolver

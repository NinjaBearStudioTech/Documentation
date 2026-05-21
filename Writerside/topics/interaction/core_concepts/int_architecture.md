# Architecture
<primary-label ref="interaction"/>

This section includes **deep dive** on important **technical aspects** of the Interaction System.

**[](int_manager_component.md)**
: The **Interaction Manager** captures and stores available **Interaction Targets** for a pawn or character. Once captured,
these targets can be **focused**, making them eligible for the **Interaction Flow**.

**[](int_target_component.md)**
: The **Interaction Target** is built on two frameworks: **Smart Objects** and **Gameplay Behaviors**. It introduces
specialized logic and flows, integrated with other parts of the Interaction System.

**[](int_user_interface.md)**
: The Interaction System displays information to players, conveying the status of available or active interactions. This
is done via interaction-specific **Widget Components**, **Widgets** and **UMG Viewmodels**.
# Architecture
<primary-label ref="input"/>

This section includes **deep dive** on important **technical aspects** of the Input System.

**[](ipt_input_handlers.md)**
: These small pieces of code are responsible for handling input. They are self-contained and highly reusable. The system
also provides Input Handlers fully integrated with the **Gameplay Ability System**. 

**[](ipt_forward_reference.md)**
: This element is important for certain control schemes, such as _twin-stick_ controls, where a constant forward 
reference is necessary.

**[](ipt_input_detection.md)**
: Ninja Input provides a native way to detect changes in the input mode - Gamepad or Keyboard and Mouse.

**[](ipt_common_ui.md)**
: Common UI has a few systems that are closely related to input handling such as the Input Routing. Ninja Input can help
adjusting certain input settings for user interfaces as well.

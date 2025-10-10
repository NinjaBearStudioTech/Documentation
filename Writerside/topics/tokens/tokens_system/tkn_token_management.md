# Token Management
<primary-label ref="tokens"/>

The Token Manager stores **per-tag budgets** for a pawn (the "owner") and coordinates token requests from other pawns 
(the "requesters"). Owners **grant tokens immediately when capacity is available** or **enqueue requests when it is not**. 
Requesters receive callbacks when their request is granted or denied and **must return the token handle when finished**.

## Component Setup

Add `UNinjaTokenManagerComponent` to any Pawn that will **own** or **request** tokens. This keeps behavior independent of 
the controller, so it works the same for both player-controlled and AI-controlled pawns.

For Pawns that own tokens, configure **token tags** and **capacities** on the component.

- A **token tag** uniquely identifies the token and, importantly, its purpose. For example, a tag like `AI.Token.Type.Attack` can be used to control how many enemy AIs may attack the same target simultaneously.
- **Capacity** is the budget available for that tag. For example, if `AI.Token.Type.Attack` has a capacity of 3 and each enemy AI requests a cost of 1, then up to three enemies AIs can attack at once. If a boss AI requests a cost of 2, then only the boss AI and one other enemy AI can attack at the same time.

Although optional, it's recommended to also **implement** `IActionTokenProviderInterface`, which declares the `GetTokenManager` 
function. This will provide direct access to other objects integrated with this component.

## Requesting Tokens

Even though this component is mostly used in the backend, and your AI agents would manage their keys using the provided
objects for **Behavior Trees** or **State Trees**, you can still request tokens from the component itself. This is particularly
useful when you are integrating this system with other AI frameworks.


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

The following functions can be invoked by a **requester**.

> **Providers vs. Requesters**
> 
> A **Provider** is the component that owns the token budget, while a **Requester** borrows tokens from it.
{style="note"}

| Function                  | Description                                                                                                                                              |
|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------|
| `RequestBorrow`           | Requests one or more tokens from a **target** component. The requester calls this on the target and receives both a **request result** and a **handle**. |
| `ReturnBorrowedToken`     | Returns a previously borrowed token using its **handle**.                                                                                                |
| `ReturnBorrowedTokenById` | Returns a token using its **Token ID**, resolving the corresponding handle internally if possible.                                                       |
| `CancelQueued`            | Cancels queued tokens defined by their identifying Gameplay Tag, that were requested by a given component.                                               |

The **request result** can be one of the following:

1. **Granted**: The token was granted immediately.
2. **Queued**: The token request was added to the queue and will be granted once the owner has enough available budget.
3. **Failed**: The request failed, usually because the owner has no budget defined for the requested token type.

## Querying Token Info

You can **query token states**, budgets, and other relevant information using the provided functions.

As with token requests, the Behavior Tree and State Tree implementations often handle these details automatically. However, 
if you need to create custom AI logic or integrate with other frameworks, the following functions are available.

| Function                      | Description                                                                                                                                                                           |
|-------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `HasQueuedRequestForBorrower` | Checks if this **Token Provider** currently has a **queued request** for the specified borrower and token type. Useful for confirming whether an agent is already waiting for access. |
| `HasActiveGrantForBorrower`   | Checks if this **Token Provider** has an **active grant** (borrowed token) for the given borrower and handle ID.                                                                      |
| `HasBorrowedHandle`           | Checks if this **Token Requester** still holds a borrowed token with the specified handle ID.                                                                                         |
| `GetCapacity`                 | Returns the **maximum capacity** (total budget) for the given token type. This defines how many concurrent borrowers are allowed.                                                     |
| `GetAvailable`                | Returns the number of tokens of the given type that are **currently available** for use.                                                                                              |
| `GetBorrowed`                 | Returns the number of tokens of the given type that are **currently borrowed** by other agents.                                                                                       |

## Delegates

Requesters or other systems can react to events in the token layer using the following **delegates** and **callbacks**.
These allow both Blueprint and C++ systems to respond when **token requests are granted or denied**.

| Delegate               | Description                                                                                                                                                                                   |
|------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `OnTokenGranted`       | Fired on the **requester** when a previously requested token is **granted**—either immediately or after being queued. This is a **BlueprintAssignable** delegate, ideal for visual scripting. |
| `OnTokenDenied`        | Fired on the **requester** when a token request is **denied**, either due to immediate rejection or expiration of the request’s time-to-live (TTL). Also **BlueprintAssignable**.             |
| `OnTokenGrantedNative` | C++ variant of `OnTokenGranted`. This is a non-dynamic delegate intended for **native binding** (e.g. lambdas) in code.                                                                       |
| `OnTokenDeniedNative`  | C++ variant of `OnTokenDenied`. This is a non-dynamic delegate intended for **native binding** (e.g. lambdas) in code.                                                                        |

# Ninja Tokens
<primary-label ref="tokens"/>

![Ninja Tokens](tkn_feature.png "Ninja Tokens")

**Ninja Tokens** is a **lightweight coordination** layer for AI. It solves the classic "too many agents do the same thing 
at once" problem by giving targets a **token budget** and letting agents **request** or **queue** access to actions through 
a fair and deterministic system.

Under the hood, each target owns a **per-tag budget** and queue; agents request a token, get granted immediately if capacity 
exists, or are enqueued and later granted as capacity frees up. Priority and FIFO tiebreakers keep outcomes predictable, 
and TTL policies are enforced **opportunistically**. No ticks or timers, so the system **scales cleanly**.

## Features Overview

- **Tag-based tokens and budgets**: Use Gameplay Tags to define independent action channels (e.g., `AI.Token.Type.Attack`) with per-target capacities and costs.
- **Compatible with Behavior Trees and State Trees**: Includes tasks to request and return tokens, and decorators/conditions to check token availability.
- **Fair, predictable queuing**: Highest priority wins (useful for elites, bosses and the such); ties honor arrival order. If a high-priority request doesn’t fit, a smaller one that fits can proceed, no blocking.
- **TTL without ticking**: Requests with time-to-live are expired on later interactions (new requests/returns). No timers, no per-frame overhead, allowing the system to scale further.
- **Simple integration points**: Blueprint & C++ delegates and other extension and integration points, so the system can be easily extended or integrated with other modules.
- **Dedicated diagnostics**: Integrated with the Visual Logger and Unreal Insights.


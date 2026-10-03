# Changelog
<primary-label ref="bot"/>

## 1.0.21 - 05/10/2026
```
[change] Centralized target-transition notifications and ensured destroyed targets trigger clearing callbacks and delegates.
[change] Kept awareness entries active after perception is lost so awareness decay can complete.
[change] Updated Behavior Tree and State Tree sensor integrations to clear their outputs correctly.
[change] Threat managers now retry perception binding after asynchronous Ninja Bot setup completes.
[change] Perception bindings now detach safely when the controller's perception component changes.
[change] Awareness ViewModels now initialize immediately from the bot's current perception entry.
[fix] Prevented inactive stimuli from retaining stale scores or remaining eligible for target selection.
[fix] Corrected stimulus normalization to use the current target's distance.
[fix] Ensured awareness-level changes update LastAwarenessChangeTime.
[fix] Ensured destroying the current target clears selection state and notifies the AI controller and listeners.
[fix] Corrected strength-normalization helpers to return the source actor instead of the perception owner.
[fix] Ensured EQS perception contexts safely return an invalid location when the target has no perception record.
[fix] Ensured highest raw and normalized threat caches update when the leading threat actor remains unchanged.
[fix] Prevented repeated bot setup from accumulating duplicate ViewModel callbacks.
[fix] Ensured changing or clearing the component owner resets ViewModel bindings consistently.
[fix] Applied fixes identified during documentation updates.
```

## 1.0.5 - 30/06/2026
```
[build] Added support for Unreal Engine 5.8.
```

## 1.0.4 - 17/04/2026
```
[new] Settings include an option to set custom State and Behavior Components for the AI Controller.
[fix] Ensured that bot assets are only released after the bot is unpossessed.
```

## 1.0.2 - 09/03/2026
```
[fix] Direct interface call on the Bot AI Controller.
[fix] Added perception callback invocation, to broadcast targets to the owning AI Controller. 
```

## 1.0.0 - 12/01/2026
First release for Unreal Engine 5.6 and 5.7.
# Backlog

Potential features and improvements to consider based on future project requirements.

These are not commitments or a fixed roadmap. Features will be implemented as needed.

## Distribution & Reusability

- **Turn into a plugin**: Package the multiplayer subsystem as a reusable Unreal Engine plugin with a clean public API.

## Session & Connection Handling

- **Host disconnect dialog**: Inform clients when they are returned to the main menu because the host disconnected.
- **Player join/leave delegate**: Expose a delegate for reacting to players joining or leaving the session, e.g. for in-game notifications.
- **Session reconnect**: Offer players the option to reconnect to their previous session after an unexpected disconnect.

## Player Management

- **Kicking players**: Allow the host to remove a player from the session.
- **Banning players**: Allow the host to prevent a player from rejoining the session.

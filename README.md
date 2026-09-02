# Unreal Engine Steam Multiplayer Template

A minimal reference project for **Steam multiplayer in Unreal Engine 5.7**.

This repository exists because Unreal Engine's Steam multiplayer setup has gone through breaking changes across recent engine versions, while existing documentation and tutorials have not always been updated to reflect those changes.

The goal of this project is to provide a **known-working C++ implementation** that can be used as a reference when starting a new Unreal Engine multiplayer project.

> **Note:** Blueprint support is currently not provided. This project is primarily intended as a C++ reference implementation.

## Scope

This repository is intended to be a **small, working reference project** that can be consulted when starting a new multiplayer project.

It is **not** a complete game template or project starter.

It contains only:

- Steam session networking and configuration required to host and join games
- Minimal main menu logic
- Minimal gameplay logic
- Third-person mannequin movement

Features outside the scope of this project may be added in the future, but are intentionally kept to a minimum for now.

## Requirements

- Unreal Engine **5.7**
- **Online Subsystem Steam**
- **Steam Sockets** plugin
- Steam client

Steam must be running when testing the project.

No other online subsystem is currently supported.

## Supported Session Types

The project currently supports three session types:

### Public

The session is publicly discoverable and can appear in the session browser.

### Friends Only

Only Steam friends can join the session.

Friends-only sessions **do not appear in the normal session search results**. If you want to display friends' active sessions in a session browser, you must enumerate the player's Steam friends separately and check whether each friend has an active session.

### Invite Only

Players can only join through a Steam invitation.

> **Known Steam limitation:** Friends cannot currently be invited to Invite Only sessions through the standard Friends List functionality in the Steam overlay.
>
> To send an invitation, use the separate Steam invite UI exposed through:
>
> `USteamMultiplayerSubsystem::ShowInviteUI()`
>
> Alternatively, a custom friend/invite UI can be implemented.

## Configuration

### 1. Enable Steam Sockets

Enable the **Steam Sockets** plugin in Unreal Engine and restart the editor.

### 2. Update `Build.cs`

Add `OnlineSubsystem` to `PrivateDependencyModuleNames` in your project's `[PROJECT_NAME].Build.cs` file.

Also add:

```cpp
DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
```

### 3. Configure `DefaultEngine.ini`

Add the following configuration:

```ini
[/Script/Engine.GameEngine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/SteamSockets.SteamSocketsNetDriver",DriverClassNameFallback="/Script/SteamSockets.SteamNetSocketsNetDriver")

[OnlineSubsystem]
DefaultPlatformService=Steam

[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480 ; 480 is Spacewar and can be used for testing. Replace with your own App ID when available.

[/Script/SteamSockets.SteamSocketsNetDriver]
NetConnectionClassName="/Script/SteamSockets.SteamSocketsNetConnection"
```

### 4. Copy the multiplayer classes

Copy the following files into your project and modify them as needed:

```text
SteamMultiplayerSubsystem.h
SteamMultiplayerSubsystem.cpp
SessionData.h
Enums.h
```

## Testing

To test Steam multiplayer:

1. Start the Steam client.
2. Build and launch the project.
3. Start one instance as the host.
4. Start another instance using a different Steam account.
5. Host or join a session using the main menu.

When testing multiple clients, make sure each client is running as a separate game instance rather than relying on a single shared PIE session, unless the particular test is known to work with PIE.

## Project Structure

The main Steam multiplayer implementation is contained in:

```text
Source/
└── [ProjectName]/
    ├── SteamMultiplayerSubsystem.h
    ├── SteamMultiplayerSubsystem.cpp
    ├── SessionData.h
    └── Enums.h
```

The rest of the project exists primarily to provide a minimal environment in which the multiplayer implementation can be tested.

## Known Limitations

- Blueprint support is currently not provided.
- Only Online Subsystem Steam is supported.
- Friends-only sessions are not returned by normal session searches.
- Invite-only sessions require `ShowInviteUI()` or a custom invitation UI.
- This project is not intended to provide a complete matchmaking, lobby, or dedicated-server solution.

## Contributing

If Unreal Engine, Steam Sockets, or Online Subsystem Steam introduce changes that affect the implementation, contributions that keep the project working with the supported Unreal Engine version are welcome.

## License

See [LICENSE](LICENSE) for licensing information.

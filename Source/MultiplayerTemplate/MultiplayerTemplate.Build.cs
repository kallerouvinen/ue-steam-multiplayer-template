// Copyright 2026 Kalle Rouvinen. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerTemplate : ModuleRules
{
	public MultiplayerTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
		});

		// TODO: Remove redundant modules from the dependency list
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"Engine",
			"EnhancedInput",
			"InputCore",
			"OnlineSubsystem",
			// "OnlineSubsystemUtils",
			"Slate",
			"StateTreeModule",
			// "SteamSockets",
			"UMG",
		});

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		PublicIncludePaths.AddRange(new string[] {
			"MultiplayerTemplate",
		});
	}
}

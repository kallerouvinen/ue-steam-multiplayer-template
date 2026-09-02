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

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"Engine",
			"EnhancedInput",
			"InputCore",
			"OnlineSubsystem",
			"Slate",
			"StateTreeModule",
			"UMG",
		});

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		PublicIncludePaths.AddRange(new string[] {
			"MultiplayerTemplate",
		});
	}
}

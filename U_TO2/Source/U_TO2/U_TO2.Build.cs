// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U_TO2 : ModuleRules
{
	public U_TO2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject"
			, "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem"
			, "AIModule", "GameplayTasks" });
	}
}

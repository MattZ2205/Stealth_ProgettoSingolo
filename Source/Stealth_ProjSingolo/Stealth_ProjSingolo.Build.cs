// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Stealth_ProjSingolo : ModuleRules
{
	public Stealth_ProjSingolo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

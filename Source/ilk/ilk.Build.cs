// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ilk : ModuleRules
{
	public ilk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

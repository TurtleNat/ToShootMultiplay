// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ToShoot : ModuleRules
{
	public ToShoot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "OnlineSubsystemUtils", "OnlineSubsystemUtils", "Sockets", "Networking" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[] { "ToShoot/Public/Player", "ToShoot/Public/Components", "ToShoot/Public/Weapon", "ToShoot/Public/Weapon/Components", "ToShoot/Public/Menu", "ToShoot/Public/Menu/UI", "ToShoot/Public/Dev" });
       // PublicIncludePaths.AddRange(new string[] { "TestShooter/Public/Player", "TestShooter/Public/Component" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}

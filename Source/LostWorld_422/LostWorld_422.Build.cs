// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class LostWorld_422 : ModuleRules
{
	public LostWorld_422(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "UnrealEd", "Blutility", "UMGEditor" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Fixes the "command line is too long to fit in debug record" error
        bLegacyPublicIncludePaths = false;

        // Uncomment if you are using Slate UI
        //PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}

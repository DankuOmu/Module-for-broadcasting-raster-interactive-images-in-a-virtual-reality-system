using UnrealBuildTool;

public class VRMouseClient : ModuleRules
{
    public VRMouseClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        bEnableExceptions = true;
    }
}

// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class OuyaSDKPlugin : ModuleRules
	{
		public OuyaSDKPlugin(TargetInfo Target)
		{
			PrivateIncludePaths.AddRange(
				new string[] {
                    "OuyaSDKPlugin/Private",
                    "../../../../Source/Runtime/Launch/Private",
					// ... add other private include paths required here ...
				});

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
                    "Engine",
					// ... add other public dependencies that you statically link with here ...
				});

            PublicIncludePathModuleNames.Add("Launch");

			if (Target.Platform == UnrealTargetPlatform.Android)
			{
				string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(pluginPath, "OuyaSDKPlugin_APL.xml")));
			}
		}
	}
}

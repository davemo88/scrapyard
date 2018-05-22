// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ScrapyardEditorTarget : TargetRules
{
	public ScrapyardEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Scrapyard" } );
        ExtraModuleNames.Add("ScrapyardServer");
        ExtraModuleNames.Add("ScrapyardClient");

	}
}


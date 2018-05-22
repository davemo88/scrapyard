// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ScrapyardTarget : TargetRules
{
	public ScrapyardTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Scrapyard" } );
        ExtraModuleNames.Add("ScrapyardServer");
        ExtraModuleNames.Add("ScrapyardClient");
	}
}

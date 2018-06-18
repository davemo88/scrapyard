// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ScrapyardClientTarget : TargetRules
{
	public ScrapyardClientTarget(TargetInfo Target) : base(Target)
	{
//		Type = TargetType.Game;
		Type = TargetType.Client;

		ExtraModuleNames.Add("Scrapyard");
//        ExtraModuleNames.Add("ScrapyardClient");
	}
}

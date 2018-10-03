#!/bin/bash
RANDNUM1=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM2=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM3=$(( ( RANDOM % 1000 ) + 1000 ));
$HOME/UnrealEngine/Engine/Build/BatchFiles/Linux/RunMono.sh $HOME/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe -ModuleWithSuffix=Scrapyard,$RANDNUM1 -ModuleWithSuffix=ScrapyardServer,$RANDNUM2 -ModuleWithSuffix=ScrapyardClient,$RANDNUM3 Linux Development -TargetType=Editor -Project="$HOME/Scrapyard/Scrapyard.uproject" -canskiplink "$HOME/Scrapyard/Scrapyard.uproject"  -progress

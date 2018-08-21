#!/bin/bash
RANDNUM1=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM2=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM3=$(( ( RANDOM % 1000 ) + 1000 ));
#/home/hg/UnrealEngine/Engine/Build/BatchFiles/Linux/RunMono.sh /home/hg/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe -ModuleWithSuffix=Scrapyard,$RANDNUM1 -ModuleWithSuffix=ScrapyardServer,$RANDNUM2 -ModuleWithSuffix=ScrapyardClient,$RANDNUM3 Linux Development -TargetType=Editor -Project="/home/hg/Scrapyard/Scrapyard.uproject" -canskiplink "/home/hg/Scrapyard/Scrapyard.uproject"  -progress
/home/hg/UnrealEngine/Engine/Build/BatchFiles/Linux/RunMono.sh /home/hg/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe Linux Development -TargetType=Editor "/home/hg/Scrapyard/Scrapyard.uproject" -progress -verbose -waitmutex

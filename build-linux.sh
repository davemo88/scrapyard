#!/bin/bash
RANDNUM1=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM2=$(( ( RANDOM % 1000 ) + 1000 ));
RANDNUM3=$(( ( RANDOM % 1000 ) + 1000 ));
/home/hg/UnrealEngine/Engine/Build/BatchFiles/Linux/RunMono.sh /home/hg/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe Scrapyard -ModuleWithSuffix=Scrapyard,$RANDNUM1 -ModuleWithSuffix=ScrapyardServer,$RANDNUM2-ModuleWithSuffix=ScrapyardClient,$RANDNUM3 Linux Development -editorrecompile -canskiplink "/home/hg/Scrapyard/Scrapyard.uproject"  -progress

#!/bin/bash
$HOME/UnrealEngine/Engine/Build/BatchFiles/Linux/RunMono.sh $HOME/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe Development Linux -Project="$HOME/Scrapyard/Scrapyard.uproject" -TargetType=Editor -Progress -NoHotReloadFromIDE

#!/bin/bash
# optionally pass the starting map
if [ ! -z "$1" ]
then
    $HOME/UnrealEngine/Engine/Binaries/Linux/UE4Editor -game $HOME/Scrapyard/Scrapyard.uproject $HOME/Scrapyard/Content/Levels/$1.umap 
else
    $HOME/UnrealEngine/Engine/Binaries/Linux/UE4Editor -game $HOME/Scrapyard/Scrapyard.uproject
fi

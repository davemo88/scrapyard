#!/bin/bash
./build-linux-server.sh
./build-linux-dev.sh
echo "Copying Server Binary"
cp $HOME/Scrapyard/Binaries/Linux/ScrapyardServer $HOME/Packaged/LinuxNoEditor/Scrapyard/Binaries/Linux/
echo "Copying Client Binary"
cp $HOME/Scrapyard/Binaries/Linux/Scrapyard $HOME/Packaged/LinuxNoEditor/Scrapyard/Binaries/Linux/

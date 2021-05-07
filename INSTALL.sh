#!/bin/bash

currentDir=echo pwd
echo "########################################"
echo "# WELCOME TO SNAKE INSTALLATION SCRIPT #"
echo "########################################"
echo
echo "-------------------------------------"
echo "--- Installing dependencies : "
echo "-------------------------------------"
sudo apt install gcc libstdc++6 make cmake libsfml-graphics2.5 libsfml-system2.5 libsfml-window2.5
echo "-------------------------------------"
echo "--- Making build directory and move to this directory "
echo "-------------------------------------"
mkdir build 
cd build
echo "-------------------------------------"
echo "--- Generating automatic build script "
echo "-------------------------------------"
cmake .. -DCMAKE_BUILD_TYPE=Release
echo "-------------------------------------"
echo "--- Building the project "
echo "-------------------------------------"
make
chmod +x snake
echo "-------------------------------------"
echo "--- Running the app "
echo "-------------------------------------"
./snake
cd $currentDir
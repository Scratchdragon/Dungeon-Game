# Dungeon-Game
A simple c++ based rougelike dungeon-crawler

# Features
A floor by floor system where you have to plow through enemies to reach your goal\
Each floor has a boss at the end which you will need to kill to continue\
The dungeon is randomly generated with geometry that is often complex and confusing\

# Installation Guide
To install on linux devices do the following:\
Navigate to the "dungeon_game" directory and cd into it\
From there run the following commands in sequence\
rm -r build\
sudo apt install g++; sudo apt install libsdl2-dev libsdl2-2.0-0 -y; sudo apt install make; sudo apt install cmake; mkdir build/; cd build/; cmake ../; make\
cd -; sudo chmod +x dungeon.sh; g++ -o Dungeon run.cpp; sudo chmod +x shortcut.sh; ./shortcut.sh

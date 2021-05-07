# Snake
A very disruptive game.
Written in C++.
Hope Bjarne will be proud.

# How to play ?

Snake is a game far from the classical AAA. It aims at focusing on the main components of what makes a gameplay enjoyable. The game design is a natural by-product of the inherent superiority of the creator's mind. 

Use the arrow keys to move the snake. Press escape to exit. Press space, because it's cool.

If you loose, take a deep breath, and try again. Never stop.
# LINUX : Compile and run from source

The following procedure has been tested on Ubuntu 20.04.
## The very lazy way
Just run the INSTALL.sh script, follow the instructions, be kind with this script, and enjoy your life. 
To do so, from the source directory, run

```sh
chmod +x INSTALL.sh; sudo ./INSTALL.sh
```

This script will install dependencies, build the project, and run it. You will have to enter sudo password, and might have to accept some package installation. 

To run the game again, just run 
```sh
./snake
```
from the build directory.

If you want to compile the project step by step, the categories below provide more details.
## Dependencies

To compile this project, some packages have to be installed on your machine.


First, some usual packages concerning C/C++ build.

```sh
sudo apt install gcc libstdc++6 make cmake 
```

Those packages are respectivelly the C/C++ compiler, the C++ standard library, the automatic build application, and a tool to generate scripts for the automatic build application.

The project is also based on the SFML project (Simple Fast Multimedia Library).

To install the required module of this library, run
```sh
sudo apt install libsfml-graphics2.5 libsfml-system2.5 libsfml-window2.5
```


## Compile
To compile the game, you first need to create a build directory aside from the source. For example, from this directory, run

```sh
mkdir build 
cd build
```

Then, from the build directory, run cmake in Release mode, through the command

```sh
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Please note that `..` is just a generic command that designates the parent directory. 

The generic path to provide for cmake is the path to the source directory (i.e. where the `CMakeList.txt` file is). 

Consequently, if the build folder has been created elsewhere, you must replace `..` with the source directory path.

From the same directory which you've run the `cmake <...>` command, now run

```sh
make
```

This command calls the compiler to properly generate the final binary. 
## Run

A binary file called `snake` has been created in the build folder.

To run the game, juste run 
```sh
./snake
```

If it fails with a message such as `permission denied: ./snake`, you need to grant `snake` the execution permission by running :

```sh
chmod +x snake
```

The precedent command should now work properly.

# WINDOWS : Compile from source

TO DO !

Still need to provide SMFL .dll extensions in this folder and ensure Windows10 automatically cope with dynamic/static linking to standard libraries libstdc++.

The `mingw-w64-x86_64.cmake` is a cmake configuration file that configure cmake to cross compile this Snake project from linux to windows. It recquires the installation of mingw-gcc. 

The obtained .exe file has only been tested with wine, and failed to dynamically link the .exe. Hence, this app is not cross-platform for now.
# Notes 

- The `.ttf` file is a font that is used to display the score on screen.

# Disclaimer
- Wasnt willing to write my own UI library, and this is the safest way of including the dependecies, it gives a warning, but didnt cause issue on neither linux nor windows
- Changed the cmake file according to the sfml-imgui github: https://github.com/SFML/imgui-sfml
- I am not associated with the above mentioned repo, I am just a user, it is developed by a third party. All the other code has been developed by myself according to the documentation
# Usage and changes
- Added editorwindows for prototyping, building and changing the game. Fixed a couple bugs while i was at it.
- The WaveEditor allows to set a distribution of the incomming enemies from 8 directions, so the incomming enemies will respect the given distribution in each octal. Inside of them there is a supposed uniform distribution. WaveDuration is the time over which Numberofenemies will be spawned. It allows to export the current setup into a hardcoded path in the assets folder for further analytics
- The PlayerEditor allows to test the game with multiple keyboard setups, the Godmode is only there to allow for checking the of the infinitymode, it softlocks, so exiting is advised, defaultvalues are read from the constants file.
- The Enemyeditor allows speedchanges and scoring influence.
- Start the game with the topright button, default username is goofy, refering to me for almost missing that case
- The score tracks the amount of kills, not the time spent
- didnt reskin the game, it has a nostalgic and soothing vibe compared to the editor

# Bugs fixed
- missing random seed for rand()
- always recreating and reassinging the whole sf::Text
- infinity mode negative times if the player is too good (now capped)
- Player Movement more according to the vampires + same speed even at diagonals (added the mathutils.cpp to reuse the same functions)
- Playermovement clamping missing y direction and on left and bottom spritesize
- playerweapon vanish on death
- default case for the weapondirection
- only kill when vampire when weapon is drawn
- reuse vampire shared pointers - not really a bug, just a very simple pooling of the dead until limit is reached. this should speedup the drawing of the alive ones as well
- the weapon is behaving strangly but its a feature, as long as the attack button is pressed the weapon is drawn and damaging
- Marked in the code + some somewhat optimisations and rationals


# Coding Test
Hi! This is the base code structure for the coding test.
The code below is a very basic and intensionally broken version of a generic survivor game.

## Disclaimer

We strongly recommend that you:
- Place assets in the `/assets` folder and use the `ResourceManager` class to get file paths.
    - Example usage: `m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf"))`
    - Look in `/src/Game.cpp` for examples of loading fonts and textures.
- Use CMake to build your project and do not modify the CMakeLists.txt file.
- Test on different platforms to assure your submission builds and functions the same.

We will build your project with the build steps outlined below. If your submission produces any build errors we will most likely end the evaluation there.

## Prerequisites

NOTE: Hive computers (should) have these dependencies installed already.

You must have [CMake](https://cmake.org/) version 3.22.1 or later installed to build this project.

If you are on Linux, make sure to install SFML's dependencies. For Debian-based distros:
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

## Building

Simply run `cmake -B build` and `cmake --build build`. This builds the executable in `./build/bin/`.

The exact location of the executable may differ depending on your system and compiler. Example locations are `./build/bin/survive` and `./build/bin/Debug/survive.exe`.

Alternatively, you can specify a generator suited for your toolchain.
- `cmake -B build -G"Unix Makefiles"`
- `cmake -B build -G"Visual Studio 17 2022"`
- `cmake -B build -GXcode`

Run `cmake -G` to list all available generators.

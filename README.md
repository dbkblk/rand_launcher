# AND2 Checker : Install or update your game easily !
## Description
Here is an executable that will ease the installation and maintenance of the mod. No need for external tools to install or update anymore !
Features:
- Check for the mod presence. If it is not installed, the executable download automatically the latest development version.
- If the mod is detected, it can update to the current version or get back to the previous version.
- If there is a problem in your installation, it can cleanup the directory, then you can update it again easily.
- It automatically clear the cache on update.

## Installation instructions
- Download the installation pack: Here
- Unzip the folder into My Document\My Games\Beyond the sword\Mods
- Now, go into the newly created Rise of Mankind - A New Dawn folder and execute and2_checker.exe
- Follow the instructions

Just execute and2_checker.exe again when you want to update, or clean, etc...

## Comments
While thinking about git, i came to an idea and TADAM ! This executable is pretty basic, but it get the job done on my PC. Please test it and give me some feedback.
With these scripts, no need for TortoiseSVN or whatever. No need for nightly builds neither . You just unzip and launch.
The idea is pretty basic, but i will improve it. The nice part is that we can include it later directly into the repo.

The next step is to implement an option the make the mod auto-start when launching Civilization. Then i'll try to make a GUI, but that is much harder to me at the moment.

## Changelog
v0.3
Auto-detection of installation
A menu to update, revert to the last version or cleanup the
installation
Auto-clear the cache

v0.2
Executable in C++. Basic functions: Check for installation. If yes > update, if no > install.
DO NOT CANCEL THE INSTALLATION IF THE MOD IS NOT INSTALLED AT THE MOMENT
v0.1
Basic idea with script
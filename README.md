# Rise of Mankind - A New Dawn Launcher source code

Last build : [![pipeline status](https://gitlab.com/dbkblk/rand_launcher/badges/master/pipeline.svg)](https://gitlab.com/dbkblk/rand_launcher/commits/master)

## Description
This launcher should help to customize and update the mod "Rise of Mankind - A New Dawn" @ http://anewdawn.sf.net

Features:
- Change language. Add support for new languages (Asian languages, Russian, etc...).
- Update the mod to the latest version in two clicks. Check changelog before update.
- Reset the mod the default installation (Remove customizations without reinstalling from scratch)
- Clear the cache of the game at each update.
- Many other customizations (Flag types, interface color, game autostart, terrain textures, etc.)

## Installation instructions
It is automatically installed when you install the mod on your computer.

## How to use the launcher with another mod
Due to a request, the launcher has been made a bit more configurable, to allow to be used with others mods. When the launcher is first launched, it will generate a config file under "checker/checker_config.ini" which will contains the following:

```
[Main]
ExecutablePath=
Lang=en
LocalRev=

[Modules]
ColorUI=Default
ModernFlags=1
Terrain=0

[Update]
DistantRev=
```

If you add the following lines under [Mod], it will allow customization:

```
mod_name=Your mod name
url_check=http://theurlofyourupdateflux
```

The mod_name should be the same as the mod folder name. The url_check setting is used to check for update. Check for http://civ.afforess.com/changelog_last.xml as an example. It should follow the same syntax (it is an SVN output XML).

Finally, the background can be changed in checker/and2_background.jpg.

## How to compile (easy way)
### Requirements
- Docker: https://www.docker.com/
- Autohotkey (Windows): https://autohotkey.com/

### Compilation
A Dockerfile is created under "project/". If you have Autohotkey installed:
- Execute "project\docker_prepare_build_machine.ahk" to prepare the build machine.
- Insert your Transifex API key (for translation update) and your mod path in "project/settings.ahk"
- To build the project: execute "project\docker_build_project.ahk" (build will output in "build/" dir).
- To update the translations: "project\docker_update_translations.ahk" (translations will be copied into your mod directory)

If you don't have Windows to build it, either install Autohotkey with wine, or read the commands and paste them manually in a console. Docker is still needed.

## How to compile (former way)
### Requirements
- Qt 5.4 with MinGW binaries http://qt.io/
- Python 3.4

### Compilation
- To compile a static version of the launcher, you'll need a static version of Qt 5.4 configured into QtCreator. Follow this guide to do this: https://qt-project.org/wiki/Building_Qt_Desktop_for_Windows_with_MinGW
- Then, open the launcher .pro file and compile.

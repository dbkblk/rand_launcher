# Roadmap
## 0.8
### Features

DONE -> Update label after mod update
DONE -> Hide the close button while update is still pending
DONE -> Add a menu to navigate to the mod folder

### Bugfix

DONE -> Restore launcher update check from options
DONE -> setText on installation box label crash the window !
DONE -> Fix incorrect version just after update.
DONE -> Remove the "Waiting for data..." when the text is updated on the changelog window.
DONE -> Do not invoke a window to cleanup the mod but show a confirmation message
DONE -> Fix update process (the signal don't create a window)

## 0.9
### Features

DONE -> Autodetect the game path from registry
DONE -> Add easy installation of addons
DONE -> Option to autoupdate the launcher, and the mod
DONE -> Update graphics
DONE -> Add an option to setup "formations"
DONE -> Allow to install the mod from the Civ 4 folder
DONE -> Reset gameoptions on update (may need to change the way it read/write into the ini file to avoid mess when deleting options).
DONE -> Make a configuration cleaner
DONE -> Make an update manager which have checkboxes, rows with name type (mod, launcher, addon update), your version and the newest version. Choose which one to update, them let's have an update party !
DONE -> Change version to MAJOR / MINOR numbers instead of float

### Bugfix
DONE -> Fixed a mighty segfault when colors are all defined to zero.

## 0.10
### Features
DONE -> Create a graphical launcher updater
DONE -> Recheck addon state after installation
DONE -> Make a uninstallation for addons (compare with the file list from the repo "svn list --recursive")


### Bugfix
DONE -> Option: Formations don't keep parameters
DONE -> Confirm that the mod has been updated to popup "the mod has been updated"
DONE -> Do not tell update is available if addons aren't installed
DONE -> Show changelog from the head version
DONE -> Update main window infos after update;

## 0.11
### Features

- Autocheck svn state from error message.
DONE -> Link to the translation platform
DONE -> Make the launcher translatable
DONE -> Improve installer
- Add option for bluemarble
- Code a new addon installer separated from the launcher


### Bugfix
- Fix addon installer
DONE -> Fix menus not clickable at start
- Fix delay when starting the component manager

## 2.0
### Features

- Fix binaries packaging launching from launcher
- Create a borderless window with metro style

# Features pending

- Integrate git into the launcher
- Download a compressed version the first time, then update it (save bandwidth).
- Integrate a git workflow

# Bugfixes pending
As soon as I started the game for the first time, I got the yellow button "Update available" but there are of course no updates. It happened only once. I'll see if I can reproduce it.

# Notes
## Dev tools
- XML Parser
- Pack binaries: Make a list + checksum of each binary file
- Pack binaries: Compare each modified file with the checksum list

## Git Workflow
- Make a "Base pack" with all the fpk, sounds, art hosted on sourceforge
- Put all the code and small binaries on github (it will be under 800mb)
- Put a ini file in which we write the base package version and a download link
- Use my launcher to grab the new files from github and a incremential base package update when the ini file specifiy there is a new version
- We can work with a master branch where we put the new revision on and a devel branch where we just update and experiment.
- When a fpk need to be updated, just pack it, upload it on sourceforge, then update the ini file with a new version number and a download link, so the launcher will know there's an update. If the file is named, for example, "BASE_PACK_UPDATE_694.7z", it will be easy to know that it correspond to the 694 version. This way, the version control process, still works !

## Release process
- Compile executable
- Put the executable in release_files/, change the version number in NSIS script and compile the NSIS installer in installer/
- Upload the installer file
- Put the modified files in a packed update file
- Upload the update pack
- Upload source code
- Merge devel with master
- Update update.ini in master with the update pack link and push it to enable autoupdate.

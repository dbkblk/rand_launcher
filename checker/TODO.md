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
DONE -> Link to the translation platform
DONE -> Make the launcher translatable
DONE -> Improve installer
DONE -> Code a new svn installer separated from the launcher
DONE -> Reimplement clean and revert function
DONE -> Reorganized code
DONE -> Add option for bluemarble

### Bugfix
DONE -> Fix menus not clickable at start
DONE -> Fix delay when starting the component manager
DONE -> Fixed cache not working

## 0.12
DONE -> Save the language state
DONE -> Choose the merge possibilities (--accept tc / etc.)
DONE -> Use XML to better layout changes

## 0.13
DONE -> BUG: When changing language, the component window does not retranslate everything.
DONE -> Installer: Add MSVC in the installer page

## 0.14
DONE -> Add a command window to the fix installation menu
DONE -> Revert command with a cmd window
DONE -> Fixed rev number sometimes not updated
DONE -> Fixed modules window title
DONE -> Fixed module updater not updating when the launcher is installed from the installer

## 0.15
DONE -> Add a marker to see current language
DONE -> BUG: Fix updater progress bar
DONE -> CHECK: Self-updating launcher check

## 1.0
DONE -> Integrate RSYNC instead of SVN
DONE -> Setup the installer to automatically execute the launcher the first time
DONE -> Check the first time installer
DONE -> Improved updater progress

## 1.01
DONE -> Updater: Create a "updating" file at start then delete it at the end. The launcher should check if the file is present, and then relaunch the updater again.

## 1.02
DONE -> Force installer to make a folder named "Rise of Mankind - A New Dawn" and to decompress into "Mods/" folder + Check the folder name at start
DONE - Possibility to use the default color (!?)
DONE -> GUI to exclude files
- Drop support for Sinhala (unmaintened and less than 1% translated)

## Pending
? - Fix the weird updating loop !?

## 1.1
- Add support for exclusions for mods files
- Reimplement addon installer

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

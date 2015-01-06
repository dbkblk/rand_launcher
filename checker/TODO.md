# Roadmap
## 1.1
- Add support for exclusions for mods files
- Reimplement addon installer with XML injection support
- Eventual linux support

## 1.03
-x Fix the mighty rsync error on some W7 / W8.1 64 bits systems.
-x Autostart the mod with the game from the launcher, independently from the autostart option set.
x Detect double folders presence in base game and my documents and warn the user.
x Detect the Blue Marble FPK file.
x Color UI / Formations: Instead of blocking the file from update, save the parameters and check / inject at each launcher start if changed.
x Fixed "exclude files" button size.
x Generate an exclusion.custom.xml file if not present.

## 1.02
x Force installer to make a folder named "Rise of Mankind - A New Dawn" and to decompress into "Mods/" folder + Check the folder name at start
x Possibility to use the default color (!?)
x GUI to exclude files
x Drop support for Sinhala (unmaintened and less than 1% translated)
x Add a function to reset the mod in the default state

## 1.01
x Updater: Create a "updating" file at start then delete it at the end. The launcher should check if the file is present, and then relaunch the updater again.

## 1.0
x Integrate RSYNC instead of SVN
x Setup the installer to automatically execute the launcher the first time
x Check the first time installer
x Improved updater progress

## 0.15
x Add a marker to see current language
x BUG: Fix updater progress bar
x CHECK: Self-updating launcher check

## 0.14
x Add a command window to the fix installation menu
x Revert command with a cmd window
x Fixed rev number sometimes not updated
x Fixed modules window title
x Fixed module updater not updating when the launcher is installed from the installer

## 0.13
x BUG: When changing language, the component window does not retranslate everything.
x Installer: Add MSVC in the installer page

## 0.12
x Save the language state
x Choose the merge possibilities (--accept tc / etc.)
x Use XML to better layout changes

## 0.11
x Link to the translation platform
x Make the launcher translatable
x Improve installer
x Code a new svn installer separated from the launcher
x Reimplement clean and revert function
x Reorganized code
x Add option for bluemarble
x Fix menus not clickable at start
x Fix delay when starting the component manager
x Fixed cache not working

## 0.10
x Create a graphical launcher updater
x Recheck addon state after installation
x Make a uninstallation for addons (compare with the file list from the repo "svn list --recursive")
x Option: Formations don't keep parameters
x Confirm that the mod has been updated to popup "the mod has been updated"
x Do not tell update is available if addons aren't installed
x Show changelog from the head version
x Update main window infos after update;

## 0.9
x Autodetect the game path from registry
x Add easy installation of addons
x Option to autoupdate the launcher, and the mod
x Update graphics
x Add an option to setup "formations"
x Allow to install the mod from the Civ 4 folder
x Reset gameoptions on update (may need to change the way it read/write into the ini file to avoid mess when deleting options).
x Make a configuration cleaner
x Make an update manager which have checkboxes, rows with name type (mod, launcher, addon update), your version and the newest version. Choose which one to update, them let's have an update party !
x Change version to MAJOR / MINOR numbers instead of float
x Fixed a mighty segfault when colors are all defined to zero.

## 0.8
x Update label after mod update
x Hide the close button while update is still pending
x Add a menu to navigate to the mod folder
x Restore launcher update check from options
x setText on installation box label crash the window !
x Fix incorrect version just after update.
x Remove the "Waiting for data..." when the text is updated on the changelog window.
x Do not invoke a window to cleanup the mod but show a confirmation message
x Fix update process (the signal don't create a window)

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

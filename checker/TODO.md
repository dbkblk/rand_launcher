# Roadmap
## 1.1
- Add support for exclusions for mods files
- Reimplement addon installer with XML injection support
- Eventual linux support

## 1.06
- Fix the dropdown not remembering the previous choice on close/open options window
-> Add menu for the civilopedia strings translation

## 1.05
- Remove the terrain art from the FPK and add a dropdown box to choose between original Civ terrain / A New Dawn terrain / Blue Marble
- Fix the custom exclusion box to save files on Windows 7+.

## 1.04
- Updated all the executables to the latest cygwin version (should fix curl errors and ease maintenance)
- Updated Blue Marble option algorithm
- Installer: Updated to fix the wrong shortcut execution path (which prevent the launcher to start from the shortcut)

## 1.03
- Fix the mighty rsync error on some W7 / W8.1 64 bits systems.
- Autostart the mod with the game from the launcher, independently from the autostart option set.
- Detect double folders presence in base game and my documents and warn the user.
- Detect the Blue Marble FPK file.
- Color UI / Formations: Instead of blocking the file from update, save the parameters and check / inject at each launcher start if changed.
- Fixed "exclude files" button size.
- Generate an exclusion.custom.xml file if not present.

## 1.02
- Force installer to make a folder named "Rise of Mankind - A New Dawn" and to decompress into "Mods/" folder + Check the folder name at start
- Possibility to use the default color (!?)
- GUI to exclude files
- Drop support for Sinhala (unmaintened and less than 1% translated)
- Add a function to reset the mod in the default state

## 1.01
- Updater: Create a "updating" file at start then delete it at the end. The launcher should check if the file is present, and then relaunch the updater again.

## 1.0
- Integrate RSYNC instead of SVN
- Setup the installer to automatically execute the launcher the first time
- Check the first time installer
- Improved updater progress

## 0.15
- Add a marker to see current language
- BUG: Fix updater progress bar
- CHECK: Self-updating launcher check

## 0.14
- Add a command window to the fix installation menu
- Revert command with a cmd window
- Fixed rev number sometimes not updated
- Fixed modules window title
- Fixed module updater not updating when the launcher is installed from the installer

## 0.13
- BUG: When changing language, the component window does not retranslate everything.
- Installer: Add MSVC in the installer page

## 0.12
- Save the language state
- Choose the merge possibilities (--accept tc / etc.)
- Use XML to better layout changes

## 0.11
- Link to the translation platform
- Make the launcher translatable
- Improve installer
- Code a new svn installer separated from the launcher
- Reimplement clean and revert function
- Reorganized code
- Add option for bluemarble
- Fix menus not clickable at start
- Fix delay when starting the component manager
- Fixed cache not working

## 0.10
- Create a graphical launcher updater
- Recheck addon state after installation
- Make a uninstallation for addons (compare with the file list from the repo "svn list --recursive")
- Option: Formations don't keep parameters
- Confirm that the mod has been updated to popup "the mod has been updated"
- Do not tell update is available if addons aren't installed
- Show changelog from the head version
- Update main window infos after update;

## 0.9
- Autodetect the game path from registry
- Add easy installation of addons
- Option to autoupdate the launcher, and the mod
- Update graphics
- Add an option to setup "formations"
- Allow to install the mod from the Civ 4 folder
- Reset gameoptions on update (may need to change the way it read/write into the ini file to avoid mess when deleting options).
- Make a configuration cleaner
- Make an update manager which have checkboxes, rows with name type (mod, launcher, addon update), your version and the newest version. Choose which one to update, them let's have an update party !
- Change version to MAJOR / MINOR numbers instead of float
- Fixed a mighty segfault when colors are all defined to zero.

## 0.8
- Update label after mod update
- Hide the close button while update is still pending
- Add a menu to navigate to the mod folder
- Restore launcher update check from options
- setText on installation box label crash the window !
- Fix incorrect version just after update.
- Remove the "Waiting for data..." when the text is updated on the changelog window.
- Do not invoke a window to cleanup the mod but show a confirmation message
- Fix update process (the signal don't create a window)

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

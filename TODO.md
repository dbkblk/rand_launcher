# General todo
/* DON'T SEEM POSSIBLE AS SVN REDOWNLOAD EVERYTHING */- Download a compressed version the first time, then update it (save bandwidth).
- Find a correct Github workflow for the main mod (easily separate binaries from code)
DONE -> Create an installer and a desktop shortcut

# GUI todo:

DONE -> Need to reconnect the end of installation with the GUI
DONE -> Enhance the QT integration
DONE -> Detect new version.

- Recheck after update
- Clean up useless functions
- Hide the close button while update is still pending
- Enhance the GUI responsivity by passing update routines to a new thread
- Option to autoupdate the launcher, and the mod
- Make an update manager which have checkboxes, rows with name type (mod, launcher, addon update), your version and the newest version. Choose which one to update, them let's have an update party !
- Create a graphical launcher updater

# Addons integration
- Add easy installation of Civ Mega Pack (Git + sourceforge repo)
- Add easy installation of More music (only direct download)

# Bug :
setText on installation box label crash the window !
Fix incorrect version just after update.
Remove the "Waiting for data..." when the text is updated on the changelog window.

# Git Workflow
- Make a "Base pack" with all the fpk, sounds, art hosted on sourceforge
- Put all the code and small binaries on github (it will be under 800mb)
- Put a ini file in which we write the base package version and a download link
- Use my launcher to grab the new files from github and a incremential base package update when the ini file specifiy there is a new version
- We can work with a master branch where we put the new revision on and a devel branch where we just update and experiment.
- When a fpk need to be updated, just pack it, upload it on sourceforge, then update the ini file with a new version number and a download link, so the launcher will know there's an update. If the file is named, for example, "BASE_PACK_UPDATE_694.7z", it will be easy to know that it correspond to the 694 version. This way, the version control process, still works !

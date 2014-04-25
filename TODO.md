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

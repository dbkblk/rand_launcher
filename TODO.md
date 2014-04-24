# General todo
/* DON'T SEEM POSSIBLE AS SVN REDOWNLOAD EVERYTHING */- Download a compressed version the first time, then update it (save bandwidth).
- Find a correct Github workflow for the main mod (easily separate binaries from code)
DONE -> Create an installer and a desktop shortcut

# GUI todo:

DONE -> Need to reconnect the end of installation with the GUI
DONE -> Enhance the QT integration
DONE -> Detect new version.
- Create a window for updating, restoring, etc... with a label, a pushbutton and a console output:
 -> When opened, show the changelog with a question "Would you like to update ? Y/N"
 -> When Y is pressed, show the console output

- Add a progress bar on the main installation
- Recheck after update
- Clean up useless functions
- Enhance the GUI responsivity by passing update routines to a new thread
- Option to autoupdate the launcher, and the mod

# Addons integration
- Add easy installation of Civ Mega Pack (Git + sourceforge repo)
- Add easy installation of More music (only direct download)

# Bug :
setText on installation box label crash the window !

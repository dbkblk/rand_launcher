xcopy /Y ".\checker\release\and2_checker.exe" ".\release_files\and2_checker.exe"
xcopy /Y ".\updater\release\upd_proc.exe" ".\release_files\checker\upd_proc.exe"
xcopy /Y ".\checker\lang\*.qm" ".\release_files\checker\lang\"
xcopy /Y /E ".\release_files\checker" ".\svn736_files\checker\"
copy ".\release_files\and2_checker.exe" ".\svn736_files\and2_checker.exe"
SLEEP 2
MOVE "S:\Documents\Projets\and2_checker\release_files\" release_files_temp
PAUSE
move "svn736_files" "release_files"
makensis.exe ".\installer\installer_script.nsi"
xcopy /Y ".\installer\AND2_installer.exe" "AND2_full_installer.exe*"
SLEEP 5
DEL /F /Q ".\installer\AND2_installer.exe"
move ".\release_files_temp" ".\release_files_temp"
move ".\release_files" ".\svn736_files"
DEL /F /Q ".\svn736_files\and2_checker.exe"
rmdir /s /q ".\svn736_files\checker\"
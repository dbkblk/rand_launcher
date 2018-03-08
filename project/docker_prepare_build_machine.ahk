#Include, settings.ahk

; This file will build three containers with Docker
; A shared container with build tools
; A routine to build the launcher
; A routine to update the translations

SetWorkingDir, ..
RunWait, %comspec% /c docker build -f .\project\DockerCommon -t rand_launcher . && timeout 10
RunWait, %comspec% /c docker build -f .\project\DockerLauncher -t rand_launcher_build . && timeout 10
RunWait, %comspec% /c docker build -f .\project\DockerTranslations -t rand_launcher_translations --build-arg api=%api% . && timeout 10
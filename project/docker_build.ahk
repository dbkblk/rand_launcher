SetWorkingDir, ..
IfNotExist, build
   FileCreateDir, build
Run, %comspec% /c docker build -f .\project\LauncherBuilder.docker -t rand_launcher_build . && docker run --rm -v "%A_WorkingDir%\build":/app/build/ -it rand_launcher_build && timeout 10

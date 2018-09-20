SetWorkingDir, ..
IfNotExist, build
   FileCreateDir, build
Run, %comspec% /c docker run -v "%A_WorkingDir%\build":/app/build/ -it rand_launcher_build && timeout 10
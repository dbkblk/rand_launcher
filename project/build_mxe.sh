#!/bin/bash

# /!\ Make sure that you use this script with MXE installed (see ToolsBuilder.docker for details)
# sudo apt-get install -y mxe-i686-w64-mingw32.static-qtbase mxe-i686-w64-mingw32.static-qttools upx

cd ..

# Ensuring folder are created
mkdir -p build
mkdir -p build/checker_release
mkdir -p build/checker_release/.obj
mkdir -p build/checker_release/.moc
mkdir -p build/checker_release/.rcc
mkdir -p build/checker_release/.ui
mkdir -p build/checker_debug
mkdir -p build/checker_debug/.obj
mkdir -p build/checker_debug/.moc
mkdir -p build/checker_debug/.rcc
mkdir -p build/checker_debug/.ui
mkdir -p build/updater_release
mkdir -p build/updater_release/.obj
mkdir -p build/updater_release/.moc
mkdir -p build/updater_release/.rcc
mkdir -p build/updater_release/.ui
mkdir -p build/updater_debug
mkdir -p build/updater_debug/.obj
mkdir -p build/updater_debug/.moc
mkdir -p build/updater_debug/.rcc
mkdir -p build/updater_debug/.ui

# Build process
i686-w64-mingw32.static-qmake-qt5 rand_launcher.pro
make -j8
sleep 2
mv -f build/checker_release/and2_checker.exe build/
mv -f build/updater_release/upd_proc.exe build/

# Compression
upx -f build/and2_checker.exe
upx -f build/upd_proc.exe

# Finalisation
cd project
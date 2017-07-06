#!/bin/bash
# Author: Hadrien Dussuel
# Date: 20170428
# Description: Rebuild the launcher and the updater using MXE Cross Compilation environment (static). Use Ubuntu/Debian or Bash for Windows.
# Dependencies: mxe upx-ucl
# ! Make sure that MXE is properly configured (executables in the PATH)

i686-w64-mingw32.static-qmake-qt5 rand_launcher.pro
make -j3 -s
rm -R checker/release/
rm -R checker/debug/
rm checker/object_script*
rm checker/Makefile*
rm checker/and2_checker_plugin_import.cpp
rm -R updater/release/
rm -R updater/debug/
rm updater/Makefile*
rm updater/upd_proc_plugin_import.cpp
rm build/and2_checker.exe
rm build/upd_proc.exe
mv build/checker_release/and2_checker.exe build/and2_checker.exe
mv build/updater_release/upd_proc.exe build/upd_proc.exe
upx build/and2_checker.exe
upx build/upd_proc.exe
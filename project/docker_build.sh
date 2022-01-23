#!/bin/bash
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

# Building
docker build -f ./project/LauncherBuilder.docker -t rand_launcher_build .
docker run --rm -v build:/app/build/ -it rand_launcher_build
timeout 10
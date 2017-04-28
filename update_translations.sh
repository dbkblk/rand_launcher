#!/bin/bash
# Author: Hadrien Dussuel
# Date: 20170428
# Description: Update and prepare translations to be published with the mod

MOD_DIR="/home/hadrien/Dropbox/devel/civ4/civ4_svn_repository/Rise of Mankind - A New Dawn"

cd translations/
tx pull -a
cd ..
lupdate rand_launcher.pro
lrelease rand_launcher.pro
cd translations/
mv *.qm "$MOD_DIR/checker/lang/"

#!/bin/bash
# Author: Hadrien Dussuel
# Date: 20170428
# Description: Update and prepare translations to be published with the mod
# Dependencies: tx (transifex client) [sudo apt install python-pip qt5-default qttools5-dev-tools && sudo pip install transifex-client]

MOD_DIR="/mnt/d/Archives/dev/civ4_svn_repository/Rise of Mankind - A New Dawn"

cd translations/
tx pull -a
cd ..
lupdate rand_launcher.pro
lrelease rand_launcher.pro
cd translations/
mv *.qm "$MOD_DIR/checker/lang/"

#!/bin/bash

# Put the environmental variables into a file named settings.sh with the following content (remove the prefix #, but let one # on the first line)
# #!/bin/bash
#api=""
#mod_dir=""

source settings.sh

cd ..

docker build -f ./project/TranslationsUpdater.docker -t rand_launcher_translations --build-arg api=$api .
docker run -v "translations":/app/translations/ -it rand_launcher_translations
timeout 5

mv -f translations/*.qm $mod_dir/checker/lang/

echo "Translations are now in translations/"
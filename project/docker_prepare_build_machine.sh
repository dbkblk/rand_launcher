#Include, settings.ahk

# This file will build three containers with Docker
# A shared container with build tools
# A routine to build the launcher
# A routine to update the translations

cd ..
docker build -f ./project/ToolsBuilder.docker -t rand_build_tools .

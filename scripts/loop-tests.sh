#!/usr/bin/env bash

dir=${1:-"."}
count=${2:-100}

eval $(scripts/project_vars "" 1)

LOGDIR="pluginval-logs"

case $OS_TAG in
"macos")
    FILE="pluginval.app"
    FULLPATH="pluginval.app/Contents/MacOS/pluginval"
esac

cd $dir

if [ ! -f "pluginval.zip" ]; then
    curl -L "https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_macOS.zip" -o pluginval.zip
fi

if [ ! -e "${FILE}" ]; then
    unzip pluginval.zip
fi

if [ ! -d "$LOGDIR" ]; then
    mkdir $LOGDIR
fi

while [[ $count > 0 ]]
do
    echo "---------- COUNT = ${count} ------------"
    pluginval.app/Contents/MacOS/pluginval --strictness-level 5 --validate-in-process \
        --output-dir "${LOGDIR}" \
        "Source/${SF_PROJECT}_artefacts/Release/VST3/${SF_ARTIFACT_PATH}/${SF_BUILD_FILE}" || exit 1
    count=$((${count} - 1))
done
#!/usr/bin/env bash

set -e

dir=${1:-"."}
count=${2:-100}

eval $(scripts/project_vars.sh "" 1)

LOGDIR="pluginval-logs"

case $OS_TAG in
"macos")
    FILE="pluginval.app"
    FULLPATH="pluginval.app/Contents/MacOS/pluginval"
    URL="https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_macOS.zip"
    ;;
"linux")
    FILE="pluginval"
    FULLPATH="./pluginval"
    URL="https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_Linux.zip"
    EXTRA_ARGS="--skip-gui-tests"
    ;;
esac

cd $dir

if [ ! -f "pluginval.zip" ]; then
    curl -L $URL -o pluginval.zip
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
    $FULLPATH --strictness-level 5 --validate-in-process \
        ${EXTRA_ARGS} --output-dir "${LOGDIR}" \
        "${SF_VST3_BUILD_PATH}/${SF_ARTIFACT_PATH}/${SF_BUILD_FILE}" || exit 1
    count=$((${count} - 1))
done
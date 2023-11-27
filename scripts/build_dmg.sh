#!/usr/bin/env bash

set -e
set -x 

if [ -z "$SF_BUILD_FILE" ]; then
    eval $(scripts/project_vars.sh "" 1)
fi

top_dir=$(pwd)

dmg_file="${SF_OUTPUT_STEM}-universal.dmg"
lib_path="/Library/Audio/Plug-Ins/VST3"


cd build

[ -f "$dmg_file" ] && rm -f ${dmg_file}

if [[ "$SF_IN_RUNNER" ]]; then

    echo "DMG_FILE=$dmg_file" >> "$GITHUB_OUTPUT"

    # This should only happen on the github runners
    [[ ! -d "$lib_path" ]] && sudo mkdir -p "${lib_path}"
fi


# positioning depends on the actual icon
# These are optized for the default icons
${top_dir}/extern/create-dmg/create-dmg \
    --volname "solidUtility Installer" \
    --hide-extension "$SF_BUILD_FILE" \
    --background "${top_dir}/packaging/macos/dmg_background.png" \
    --window-pos 200 120 \
    --window-size 600 400 \
    --icon-size 100 \
    --icon "$SF_BUILD_FILE" 160 190 \
    --add-drop-link "${lib_path}" Library 430 190 \
    $dmg_file \
    "${SF_VST3_BUILD_PATH}/${SF_BUILD_FILE}"

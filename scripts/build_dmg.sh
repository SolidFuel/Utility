
SUDO="sudo"
if [ -z "SF_BUILD_FILE" ]; then
    SUDO=""
    eval $(scripts/project_vars.sh "" 1)
fi

TOP=$(pwd)

cd build

dmg_file="${SF_PROJECT}-V${SF_VERSION}-${OS_TAG}-universal.dmg"
lib_path="/Library/Audio/Plug-Ins/VST3"

[ -f "$dmg_file" ] && rm -f ${dmg_file}

# This should only happen on the github runners
[[ -n "$SUDO" && ! -d "$lib_path" ]] && ${SUDO} mkdir -p "${lib_path}"

${SUDO} ${TOP}/extern/create-dmg/create-dmg \
    --volname "solidUtility Installer" \
    --background "${TOP}/packaging/macos/dmg_background.png" \
    --window-pos 200 120 \
    --window-size 800 400 \
    --icon-size 100 \
    --icon "$SF_BUILD_FILE" 200 190 \
    --add-drop-link "${lib_path}" Library 600 185 \
    $dmg_file \
    "${SF_VST3_BUILD_PATH}/${SF_BUILD_FILE}"

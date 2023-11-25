eval $(scripts/project_vars "" 1)

cd build

[ -d "${SF_PROJECT}" ] && rm -rf ${SF_PROJECT}
mkdir ${SF_PROJECT}

ln -s /Library/Audio/Plug-Ins/VST3 ${SF_PROJECT}/Library

cp -R "Source/${SF_PROJECT}_artefacts/Release/VST3/${SF_ARTIFACT_PATH}/${SF_BUILD_FILE}" ${SF_PROJECT}

hdiutil create -fs JHFS+ ${SF_PROJECT}-V${SF_VERSION}-${OS_TAG}-universal.dmg \
    -srcfolder $SF_PROJECT -volname $SF_PROJECT \
    -ov -format UDZO

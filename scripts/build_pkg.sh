#!/usr/bin/env bash

install_id="$1"

set -x
set -e

sudo pkgbuild --component ${SF_VST3_BUILD_PATH}/${SF_BUILD_FILE}  \
    --install-location /Library/Audio/Plug-Ins/VST3 \
    --sign "${install_id}" \
    ./${SF_PROJECT}-unsigned.pkg

sudo productbuild --package ./${SF_PROJECT}-unsigned.pkg \
       --sign "${install_id}" \
     ./${SF_OUTPUT_STEM}-universal.pkg

echo "PKGNAME=./${SF_OUTPUT_STEM}-universal.pkg" >> "$GITHUB_OUT"
#!/usr/bin/env bash

set -e

# ARGUMENT Defaults

# Where the script should do its work.
dir="build"

# How many times pluginval should be called.
count=100

# What severity level to pass to pluginval
level=5

# parse the command line. Argument casing was chosen to match the
# the windows powershell version.
#
while [[ "$1" ]]; do
    case "$1" in
     -Count)
        count=$2
        shift; shift
        ;;
     -Dir)
        dir=$2
        shift; shift
        ;;
     -Level)
        level=$2
        shift; shift
        ;;
     *)
        echo "ERROR: unknown option '$1'"
        exit 1
        ;;
    esac
done


eval $(scripts/project_vars.sh -exp sh)

log_dir="pluginval-logs"

case $OS_TAG in
"macos")
    FILE="pluginval.app"
    exec_path="pluginval.app/Contents/MacOS/pluginval"
    URL="https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_macOS.zip"
    extra_args=""
    ;;
"linux")
    FILE="pluginval"
    exec_path="./pluginval"
    URL="https://github.com/Tracktion/pluginval/releases/latest/download/pluginval_Linux.zip"
    extra_args="--skip-gui-tests"
    ;;
*)
    echo "OS_TAG is invalid or not set : '$OS_TAG' "
    exit 1
    ;;
esac

cd "$dir"

if [ ! -f "pluginval.zip" ]; then
    curl -L $URL -o pluginval.zip
fi

if [ ! -e "${FILE}" ]; then
    unzip pluginval.zip
fi

if [ ! -d "${log_dir}" ]; then
    mkdir -p "${log_dir}"
fi

echo "Count = $count"
echo "Level = $level"

while [[ $count > 0 ]]
do
    echo "---------- COUNT = ${count} ------------"
    $exec_path --strictness-level $level --validate-in-process \
        ${extra_args} --output-dir "${log_dir}" \
        "${SF_VST3_BUILD_PATH}/${SF_ARTIFACT_PATH}/${SF_BUILD_FILE}" > /dev/null || exit 1
    count=$((${count} - 1))
done
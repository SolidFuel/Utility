#!/usr/bin/env bash
#
# Calculate the project variables and place shell lines
# on stdout to define them
# 
# project_vars [config file] [exports]
#
# config file : (optional) Path and name of the PLUGIN_CONFIG file to use.
#       If this is not given (or is empty), it will try to find it by looking
#       up the directory heirarchy
#
# exports : (optional) If present, the script will generate export statements 
#       as well.

cfg_file=$1
do_export=$2

if [[  -z "$cfg_file"  ||   "X${cfg_file}Z" == "X-Z"  ]]; then
    cfg_file="PLUGIN_CONFIG"
    for file in "${cfg_file}" "../${cfg_file}"
    do
        if [ -e "$file" ]; then
            cfg_file=$file
            break
        fi
    done

    if [ ! -f "${cfg_file}" ]; then
        echo "ERROR: Could not find CONFIG file"
        exit 1
    fi
elif [ ! -f "$cfg_file" ]; then
    echo "ERROR: file '${cfg_file}' does not exist."
    exit 1
fi

if [ "$do_export" ]; then
    if [ "$do_export" == "ps" ]; then
        export="\$env:"
    else
        export="export "
    fi
else
    export=""
fi

if [ -z "$OS_TAG" ]; then
    uname=`uname`
    case ${uname} in
    "Darwin")
        OS_TAG="macos"
        ;;
    "Linux")
        OS_TAG="linux"
        ;;
    *)
        OS_TAG="win64"
        ;;
    esac
fi

while read -r line
do
    if [ $line == "#*" ]; then
        continue
    fi
    if [[ "$OS_TAG" == "win64" ]]; then
        IFS="=" read -r key value <<< "$line"
        echo "${export}${key}=\"$value\""
    else 
        echo "${export}${line}"
    fi
done < ${cfg_file}

# Create derived variable
source "${cfg_file}"

PROJ_LOWER=$(echo "$SF_PROJECT" | tr '[:upper:]' '[:lower:]')


case "$OS_TAG" in
"macos")
    ARTIFACT_PATH="."
    BUILD_FILE=${SF_PROJECT}.vst3
    VST3_BUILD_PATH="Source/${SF_PROJECT}_artefacts/Release/VST3"
    ;;
"linux")
    ARTIFACT_PATH="."
    BUILD_FILE=${SF_PROJECT}.vst3
    VST3_BUILD_PATH="Source/${SF_PROJECT}_artefacts/Release/VST3"
    ;;
"win64")
    ARTIFACT_PATH="${SF_PROJECT}.vst3\\Contents\\x86_64-win"
    BUILD_FILE=${SF_PROJECT}.vst3
    VST3_BUILD_PATH="Source\\${SF_PROJECT}_artefacts\\Release\\VST3"
    ;;
*)
    echo "ERROR: unknown OS_TAG = '$OS_TAG'"
    exit 1
    ;;
esac


echo "${export}SF_PROJ_LOWER=\"${PROJ_LOWER}\"";
echo "${export}SF_ARTIFACT_PATH=\"${ARTIFACT_PATH}\"";
echo "${export}SF_BUILD_FILE=\"${BUILD_FILE}\"";
echo "${export}SF_VST3_BUILD_PATH=\"${VST3_BUILD_PATH}\"";

#!/bin/bash

# This script can be used to compile core library
# export QT_ROOT_DIR=~/Qt/6.5.0

# https://intoli.com/blog/exit-on-errors-in-bash-scripts/
# exit when any command fails
set -e
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG

if [ "$#" -lt 1 ]; then
    echo "destination path is not specified"
    exit 1
fi
destinationPath="$1"

scriptDirectory=`dirname "${0}"`
scriptFileName=`basename "${0}"`
cd "${scriptDirectory}"
fileOrigin=`readlink "${scriptFileName}"` || :
while [ ! -z "${fileOrigin}" ]
do
    scriptDirectory=`dirname "${fileOrigin}"`
    scriptFileName=`basename "${fileOrigin}"`
    cd "${scriptDirectory}"
    fileOrigin=`readlink "${scriptFileName}"`  || :
done
cd ..
repositoryRoot=`pwd`
echo repositoryRoot=$repositoryRoot

source ${repositoryRoot}/ENVIRONMENT

if [[ "$(uname)" == "Darwin" ]]; then
    lsbCode=mac
    qtTarget=clang_64
    libSoNamePostfix=${cinternal_version_major}.dylib
    libNamePostfix=dylib
elif [[ "$(uname -s)" == Linux* ]]; then
    source /etc/os-release
    if [ -n "$VERSION_CODENAME" ]; then
        lsbCode="$VERSION_CODENAME"
    elif echo "$ID_LIKE" | grep -qE 'rhel|fedora|centos'; then
        lsbCode="el$(echo "$VERSION_ID" | cut -d. -f1)"
    else
        lsbCode="$(echo "$ID-$VERSION_ID" | tr '[:upper:]' '[:lower:]' | tr ' ' '-')"
    fi
    qtTarget=gcc_64
    libSoNamePostfix=so.${cinternal_version_major}
    libNamePostfix=so
fi

cd "${destinationPath}"
cp ${repositoryRoot}/sys/${lsbCode}/${Confilguration}/lib/lib${libNameBase}.${libSoNamePostfix} .
ln -s lib${libNameBase}.${libSoNamePostfix} lib${libNameBase}.${libNamePostfix}

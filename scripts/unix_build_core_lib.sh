#!/bin/bash

# This script can be used to compile core library
# export QT_ROOT_DIR=~/Qt/6.5.0

# https://intoli.com/blog/exit-on-errors-in-bash-scripts/
# exit when any command fails
set -e
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG

if [ -z "$QT_ROOT_DIR" ]; then
    echo "QT_ROOT_DIR environment variable is not set"
    exit 1
fi

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
fi

echo "lsbCode=${lsbCode}"
echo "qtTarget=${qtTarget}"

cd ${repositoryRoot}/prj/core/libcinternal_qt
rm -rf .qmake.stash
${QT_ROOT_DIR}/${qtTarget}/bin/qmake CONFIG+=release CONFIG-=debug
make -f Makefile.${libNameBase}.$lsbCode.${Confilguration}

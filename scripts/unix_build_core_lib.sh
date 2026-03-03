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
scriptDirectory=`pwd`

source ${scriptDirectory}/unix_source_per_session.sh ${scriptDirectory}/unix_source_per_session.sh 1
source ${cinternalRepoRoot}/ENVIRONMENT

echo "lsbCode=${lsbCode}"
echo "qtTarget=${qtTarget}"

cd ${cinternalRepoRoot}/prj/core/libcinternal_qt
rm -rf .qmake.stash
${QT_ROOT_DIR}/${qtTarget}/bin/qmake CONFIG+=release CONFIG-=debug
make -f Makefile.${libNameBase}.$lsbCode.${Confilguration}

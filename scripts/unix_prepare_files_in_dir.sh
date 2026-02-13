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
scriptDirectory=`pwd`

source ${scriptDirectory}/unix_source_per_session.sh ${scriptDirectory}/unix_source_per_session.sh 1
source ${cinternalRepoRoot}/ENVIRONMENT


cd "${destinationPath}"
cp ${cinternalRepoRoot}/sys/${lsbCode}/${Confilguration}/lib/lib${libNameBase}.${libSoNamePostfix} .
ln -s lib${libNameBase}.${libSoNamePostfix} lib${libNameBase}.${libNamePostfix}

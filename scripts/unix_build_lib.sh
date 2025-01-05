#!/bin/bash

# https://intoli.com/blog/exit-on-errors-in-bash-scripts/
# exit when any command fails
set -e
# keep track of the last executed command
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG

#scriptFileFullPath=`readlink -f ${0}`
#scriptDirectory=`dirname ${scriptFileFullPath}`
#cd ${scriptDirectory}/../..
#repositoryRoot=`pwd`
# in mac os above short calculation will not work
# also realpath utilit is missing in mac
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
cinternalRepoRoot=`pwd`
echo cinternalRepoRoot=\"${cinternalRepoRoot}\"

make -f prj/core/libcinternal_mkfl/cinternal.unix.Makefile CPPUTILS_RELEASE=1
make -f prj/core/libcinternal_mkfl/cinternal.unix.Makefile CPPUTILS_DEBUG=1

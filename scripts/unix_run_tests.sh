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
scriptDirectory=`pwd`

source ${scriptDirectory}/unix_source_per_session.sh ${scriptDirectory}/unix_source_per_session.sh ${scriptDirectory}/unix_source_per_session.sh

cd ${cinternalRepoRoot}/sys/${lsbCode}/Debug/test

pwd
ls -al

./any_quick_test
./c_global_initer_test
./c_raii_test
./insert_custom_info_into_bin_test_exe
./cinternal_unit_test

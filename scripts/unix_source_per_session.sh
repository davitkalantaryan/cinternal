

if [ $# -eq 0 ]; then
	if [ $0 != "/bin/bash" -a $0 != "bash" -a $0 != "-bash" ]; then
		sourcePath_local=`bash -c "source $0 1"`
	else
		sourcePath_local=${BASH_SOURCE[0]}
	fi
else
	if [ $# -eq 1 ]; then
		echo ${BASH_SOURCE[0]}
		return 0
	else
		sourcePath_local=${1}
	fi
fi


makeMainJob (){

	local sourcePath=${sourcePath_local}
	unset sourcePath_local
	echo sourcePath=$sourcePath

	local currentDirectory=`pwd`
	echo currentDirectory=$currentDirectory
	
	# in mac short directory calculation based on n'readlink' or 'realpath' will not work
	local scriptDirectory=`dirname "${sourcePath}"`
	local scriptFileName=`basename "${sourcePath}"`
	cd "${scriptDirectory}"
	local fileOrigin=`readlink "${scriptFileName}"` || :
	while [ ! -z "${fileOrigin}" ]
	do
		local scriptDirectory=`dirname "${fileOrigin}"`
		local scriptFileName=`basename "${fileOrigin}"`
		cd "${scriptDirectory}"
		local fileOrigin=`readlink "${scriptFileName}"`  || :
	done
	cd ..
	cinternalRepoRoot=`pwd`
	export cinternalRepoRoot
	echo cinternalRepoRoot=$cinternalRepoRoot

	if [[ "$(uname)" == "Darwin" ]]; then
		# Do something under Mac OS X platform
    		macVersionMajor="$(sw_vers -productVersion | cut -d '.' -f1)"
    		if [ "$macVersionMajor" -gt 12 ]; then
        		lsbCode=mac
    		else
        		lsbCode=mac_old
    		fi
		qtTarget=macos
    		libNamePostfix=dylib
	elif [[ "$(expr substr $(uname -s) 1 5)" == "Linux" ]]; then
		# Do something under GNU/Linux platform
		source /etc/os-release
    		if [ -n "$VERSION_CODENAME" ]; then
        		lsbCode="$VERSION_CODENAME"
    		elif echo "$ID_LIKE" | grep -qE 'rhel|fedora|centos'; then
        		lsbCode="el$(echo "$VERSION_ID" | cut -d. -f1)"
    		else
        		lsbCode="$(echo "$ID-$VERSION_ID" | tr '[:upper:]' '[:lower:]' | tr ' ' '-')"
    		fi
    		qtTarget=gcc_64
    		libNamePostfix=so
		
		case "$LD_LIBRARY_PATH" in
			${cinternalRepoRoot}/sys/$lsbCode/Debug/lib:${cinternalRepoRoot}/sys/$lsbCode/Release/lib:* )
				echo "LD_LIBRARY_PATH for cinternal has been already set"
				;;
			* )
				export LD_LIBRARY_PATH=${cinternalRepoRoot}/sys/$lsbCode/Debug/lib:${cinternalRepoRoot}/sys/$lsbCode/Release/lib::$LD_LIBRARY_PATH
				;;
		esac
	fi
	export lsbCode
	export qtTarget
	export libSoNamePostfix
	export libNamePostfix
	echo "lsbCode="$lsbCode

	cd ${currentDirectory}
}


makeMainJob
return 0

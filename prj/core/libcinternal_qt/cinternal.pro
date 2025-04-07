#
# file:			cinternal.pro
# path:			prj/core/libcinternal_qt/cinternal.pro
# created on:	2025 Jan 03
# created by:	Davit Kalantaryan
#


message("!!! $${_PRO_FILE_}")

TEMPLATE = lib
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )
include ( $${cinternalRepoRoot}/ENVIRONMENT)

TARGET = $${libNameBase}

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

VERSION = $${cinternal_version_major}.$${cinternal_version_minor}.$${cinternal_version_patch}

DEFINES += CINTERNAL_COMPILING_SHARED_LIB

SOURCES	+=		\
        "$${cinternalRepoRoot}/src/core/cinternal_core_hash.c"	    \
        "$${cinternalRepoRoot}/src/core/cinternal_core_logger.c"    \
	"$${cinternalRepoRoot}/src/core/cinternal_core_typeinfo.c"


OTHER_FILES += $$files($${PWD}/../libcinternal_mkfl/*.Makefile,false)
OTHER_FILES += "$${cinternalRepoRoot}/scripts/unix_build_core_lib.sh"
OTHER_FILES += "$${cinternalRepoRoot}/scripts/unix_prepare_files_in_dir.sh"
OTHER_FILES += "$${cinternalRepoRoot}/scripts/windows_build_core_lib.bat"
OTHER_FILES += "$${cinternalRepoRoot}/scripts/windows_prepare_files_in_dir.bat"

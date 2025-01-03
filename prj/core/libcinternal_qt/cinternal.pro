#
# file:			cinternal.pro
# path:			prj/core/libcinternal_qt/cinternal.pro
# created on:	2025 Jan 03
# created by:	Davit Kalantaryan
#


message("!!! $${_PRO_FILE_}")

TEMPLATE = lib
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
DEFINES += CINTERNAL_COMPILING_SHARED_LIB

SOURCES	+=		\
        "$${cinternalRepoRoot}/src/core/cinternal_core_hash.c"	    \
        "$${cinternalRepoRoot}/src/core/cinternal_core_logger.c"    \
	"$${cinternalRepoRoot}/src/core/cinternal_core_typeinfo.c"


OTHER_FILES += $$files($${PWD}/../libcinternal_mkfl/*.Makefile,false)

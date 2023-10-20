#
# repo:		cinternal
# file:		c_global_initer_test.pro
# path:		prj/tests/c_global_initer_test_qt/c_global_initer_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
CONFIG += console

win32{
} else {
	LIBS += -pthread
}

SOURCES	+=		\
        "$${cinternalRepoRoot}/src/tests/main_c_global_initer_test.c"

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../c_global_initer_test_mkfl/*.Makefile,false)

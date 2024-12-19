#
# repo:		cinternal
# file:		c_raii_test_unix.pro
# path:		prj/tests/any_quick_test_qt/c_raii_test_unix.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )
DESTDIR = "$${ArifactFinal}/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
CONFIG += console

win32{
} else {
	LIBS += -pthread
}

SOURCES += $$files($${PWD}/../../../src/tests/c_raii_test_unix/*.c*,false)

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../c_raii_test_unix_mkfl/*.Makefile,false)

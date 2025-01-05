#
# repo:		cinternal
# file:		insert_custom_info_into_bin_test_exe.pro
# path:		prj/tests/insert_custom_info_into_bin_test_exe_qt/insert_custom_info_into_bin_test_exe.pro
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

SOURCES	+=		\
        "$${PWD}/../../../src/tests/insert_custom_info_into_bin_test/main_insert_custom_info_into_bin_test_exe.cpp" \
        "$${PWD}/../../../src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c"


HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../insert_custom_info_into_bin_test_exe_mkfl/*.Makefile,false)

#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#


message("!!! $${_PRO_FILE_}")

TEMPLATE = lib

include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

win32{
} else {
	LIBS += -pthread
}

SOURCES	+=		\
        "$${PWD}/../../../src/tests/insert_custom_info_into_bin_test/entry_insert_custom_info_into_bin_test_lib.c" \
        "$${PWD}/../../../src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c"

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../insert_custom_info_into_bin_test_lib_mkfl/*.Makefile,false)

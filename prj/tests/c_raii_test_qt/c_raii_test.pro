#
# repo:		cinternal
# file:		c_raii_test.pro
# path:		prj/tests/c_raii_test_qt/c_raii_test.pro
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

LIBS += -pthread


SOURCES += "$${PWD}/../../../src/tests/main_c_raii_test.c"

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../c_raii_test_mkfl/*.Makefile,false)

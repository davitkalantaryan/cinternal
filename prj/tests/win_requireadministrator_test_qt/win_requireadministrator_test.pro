#
# file:			googletest_getter.pro
# path:			prj/tests/googletest_mult/googletest_getter.pro
# created on:	2021 Nov 03
# created by:	Davit Kalantaryan
#


message("!!! $${_PRO_FILE_}")
include ( "../../common/common_qt/flagsandsys_common.pri" )
include ( "$${cinternalRepoRoot}/prj/common/common_qt/win_requireadministrator.pri" )

# we reevaluate this
DESTDIR = "$${ArifactFinal}/test"

QT -= gui
QT -= core
QT -= widgets
#CONFIG -= qt
CONFIG   += CONSOLE

SOURCES_DIR = $${focustP01MonitorRepositoryRoot}/src/tests/windows_manifestfile_test

SOURCES += $$files($${SOURCES_DIR}/*.cpp)

HEADERS += $$files($${SOURCES_DIR}/*.hpp)

OTHER_FILES += $$files($${SOURCES_DIR}/*.manifest)
OTHER_FILES += $$files($${SOURCES_DIR}/*.rc)

#
# repo:         cinternal
# file:		win_requireadministrator_test.pro
# path:		prj/tests/win_requireadministrator_test_qt/win_requireadministrator_test.pro
# created on:	2024 Dec 02
# created by:	Davit Kalantaryan (davit.kalantaryan@desy.de)
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

SOURCES += "$${cinternalRepoRoot}/src/tests/main_win_requireadministrator_test.cpp"

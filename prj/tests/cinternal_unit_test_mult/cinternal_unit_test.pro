

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )
DESTDIR = "$${ArifactFinal}/test"

CONFIG -= qt
CONFIG += console

win32{
} else {
    LIBS += -pthread
    LIBS += -ldl
}

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)
HEADERS += $$files($${cinternalRepoRoot}/src/*.h,true)

SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.c,true)
SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.cpp,true)
SOURCES += $$files($${cinternalRepoRoot}/src/core/*.c,true)

OTHER_FILES += $$files($${PWD}/*.Makefile,false)

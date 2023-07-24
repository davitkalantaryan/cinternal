

CONFIG -= qt

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

LIBS += -ldl
LIBS += -pthread

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)
HEADERS += $$files($${cinternalRepoRoot}/src/*.h,true)

SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.c,true)
SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.cpp,true)
SOURCES += $$files($${cinternalRepoRoot}/src/core/*.c,true)

OTHER_FILES += $$files($${PWD}/*.Makefile,false)

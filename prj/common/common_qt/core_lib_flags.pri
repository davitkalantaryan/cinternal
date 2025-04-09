#
# repo:         cinternal
# file:         core_lib_flags.pri
# path:         prj/common/common_qt/core_lib_flags.pri
# created on:	2025 Apr 08
# created by:	Davit Kalantaryan (davit.kalantaryan@desy.de)
#


message("!!! $${PWD}/core_lib_flags.pri")

win32{

    QMAKE_CXXFLAGS += /Brepro
    QMAKE_CFLAGS += /Brepro
    QMAKE_LFLAGS += /Brepro
    CONFIG(release, debug|release) {
        QMAKE_CXXFLAGS += /Zi
        QMAKE_CFLAGS += /Zi
        QMAKE_LFLAGS += /DEBUG
        QMAKE_LFLAGS +=/INCREMENTAL:NO
    }

} else {
}

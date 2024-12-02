#
# repo:			cinternal
# name:			win_requireadministrator.pri
# path:			prj/common/common_qt/win_requireadministrator.pri
# created on:           2024 Dec 02
# created by:           Davit Kalantaryan (davit.kalantaryan@desy.de)
# usage:		Use this qt include file to calculate some platform specific stuff
#


message("!!! $${PWD}/win_requireadministrator.pri")

isEmpty(cinternalWinRequireAdministratorIncluded){
    cinternalWinRequireAdministratorIncluded = 1
    win32{
        #QMAKE_LFLAGS -= /MANIFEST
        #RC_FILE = $${SOURCES_DIR}/admin_manifest.rc
        QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator'"
    }
}

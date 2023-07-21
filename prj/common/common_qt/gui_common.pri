#
# repo:			cinternal
# name:			gui_common.pri
# path:			prj/common/common_qt/gui_common.pri
# created on:           2023 Jun 21
# created by:           Davit Kalantaryan (davit.kalantaryan@desy.de)
# usage:		Use this qt include file to calculate some platform specific stuff
#

message("!!! $${PWD}/gui_common.pri")

isEmpty(cinternalGuiCommonIncluded){
	cinternalGuiCommonIncluded = 1
	greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
	#QT -= core
	#QT -= gui
}


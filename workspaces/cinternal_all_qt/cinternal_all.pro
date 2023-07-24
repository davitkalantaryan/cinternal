#
# repo:		cinternal
# file:		cinternal_all.pro
# path:		workspaces/cinternal_all_qt/cinternal_all.pro
# created on:	2023 Jul 21
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../prj/common/common_qt/flagsandsys_common.pri" )

TEMPLATE = subdirs
#CONFIG += ordered


SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/c_global_initer_test_qt/c_global_initer_test.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/c_raii_test_qt/c_raii_test.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/c_raii_test_unix_qt/c_raii_test_unix.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/cinternal_unit_test_mult/cinternal_unit_test.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/insert_custom_info_into_bin_test_exe_qt/insert_custom_info_into_bin_test_exe.pro"
SUBDIRS		+=	"$${cinternalRepoRoot}/prj/tests/insert_custom_info_into_bin_test_lib_qt/insert_custom_info_into_bin_test_lib.pro"


OTHER_FILES += $$files($${cinternalRepoRoot}/docs/*.md,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/docs/*.txt,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/scripts/*.sh,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/scripts/*.bat,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/.github/*.yml,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/prj/common/common_mkfl/*.Makefile,true)
OTHER_FILES += $$files($${cinternalRepoRoot}/workspaces/cinternal_all_mkfl/*.Makefile,true)

OTHER_FILES	+=	\
        "$${cinternalRepoRoot}/.gitattributes"						\
	"$${cinternalRepoRoot}/.gitignore"							\
	"$${cinternalRepoRoot}/LICENSE"							\
	"$${cinternalRepoRoot}/README.md"

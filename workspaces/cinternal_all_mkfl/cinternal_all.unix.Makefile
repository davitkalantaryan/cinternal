

targetName=cinternal_all

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

ifndef cinternalRepoRoot
        cinternalRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../.. && pwd && cd ${curDir})
endif

osSystem		:= $(shell uname)

ifeq ($(osSystem),Darwin)

all: all_common

else

all: all_common all_no_mac

endif
	

all_no_mac:
	@echo "Probably no mac target is needed"

all_common:
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/cinternal_unit_test_mult/cinternal_unit_test.unix.Makefile

clean_no_mac:
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile clean

clean_common:
	make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/cinternal_unit_test_mult/cinternal_unit_test.unix.Makefile clean

ifeq ($(osSystem),Darwin)

.PHONY: clean
clean: clean_common

else

.PHONY: clean
clean: clean_common clean_no_mac

endif

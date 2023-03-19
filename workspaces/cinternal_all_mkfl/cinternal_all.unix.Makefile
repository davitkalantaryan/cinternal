

targetName=cinternal_all.unix

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
cinternalRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../.. && pwd && cd ${curDir})


all:
	make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile
	

.PHONY: clean
clean:
	make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile clean
	
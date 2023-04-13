

targetName=cinternal_all

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
cinternalRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../.. && pwd && cd ${curDir})


all:
        ifneq ($(osSystem),Darwin)
	        make -f $(cinternalRepoRoot)/prj/tools/freelib_on_remote_proc_by_handle_mkfl/freelib_on_remote_proc_by_handle.unix.Makefile
		make -f $(cinternalRepoRoot)/prj/tools/free_libs_by_names_on_remote_proc_mkfl/free_libs_by_names_on_remote_proc.unix.Makefile
		make -f $(cinternalRepoRoot)/prj/tools/ld_postload_mkfl/ld_postload.unix.Makefile

                make -f $(cinternalRepoRoot)/prj/core/libcintr_init_libdl_mkfl/libcintr_init_libdl.unix.Makefile

                make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile
		make -f $(cinternalRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile
	endif
	
	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/lhash_test_mkfl/lhash_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/llist_test_mkfl/llist_test.unix.Makefile
	make -f $(cinternalRepoRoot)/prj/tests/test_lib01_mkfl/test_lib01.unix.Makefile
	

.PHONY: clean
clean:
        ifneq ($(osSystem),Darwin)
	        make -f $(cinternalRepoRoot)/prj/tools/freelib_on_remote_proc_by_handle_mkfl/freelib_on_remote_proc_by_handle.unix.Makefile clean
		make -f $(cinternalRepoRoot)/prj/tools/free_libs_by_names_on_remote_proc_mkfl/free_libs_by_names_on_remote_proc.unix.Makefile clean
		make -f $(cinternalRepoRoot)/prj/tools/ld_postload_mkfl/ld_postload.unix.Makefile clean

                make -f $(cinternalRepoRoot)/prj/core/libcintr_init_libdl_mkfl/libcintr_init_libdl.unix.Makefile clean
	
                make -f $(cinternalRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile clean
		make -f $(cinternalRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile clean
	endif

	make -f $(cinternalRepoRoot)/prj/tests/c_global_initer_test_mkfl/c_global_initer_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_mkfl/c_raii_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/c_raii_test_unix_mkfl/c_raii_test_unix.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_exe_mkfl/insert_custom_info_into_bin_test_exe.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/insert_custom_info_into_bin_test_lib_mkfl/insert_custom_info_into_bin_test_lib.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/lhash_test_mkfl/lhash_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/llist_test_mkfl/llist_test.unix.Makefile clean
	make -f $(cinternalRepoRoot)/prj/tests/test_lib01_mkfl/test_lib01.unix.Makefile clean
	

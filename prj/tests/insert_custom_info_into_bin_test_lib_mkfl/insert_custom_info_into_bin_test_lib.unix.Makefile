
targetName=insert_custom_info_into_bin_test_lib

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

COMMON_FLAGS += -fPIC

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(repoRootPath)/src/tests/insert_custom_info_into_bin_test/main_insert_custom_info_into_bin_test_exe.cpp
SOURCES += $(repoRootPath)/src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c

all: $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/lib/lib$(targetName).so.1

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/lib/lib$(targetName).so.1: \
	$(SOURCES:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ -Wl,-E,-soname,lib$(targetName).so.1 -pie -shared $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of googletest complete !!!

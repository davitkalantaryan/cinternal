
targetName=freelib_on_remote_proc_by_handle

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(repoRootPath)/src/tools/freelib_on_remote_proc_by_handle/main_freelib_on_remote_proc_by_handle.c
SOURCES += $(repoRootPath)/src/core/cinternal_core_parser_argparser01.c
SOURCES += $(repoRootPath)/src/core/cinternal_core_loadfreelib_on_remote_process_unix.c

all: $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName)

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName): \
	$(SOURCES:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) -ldl $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName)
	@echo "  " cleaning of googletest complete !!!

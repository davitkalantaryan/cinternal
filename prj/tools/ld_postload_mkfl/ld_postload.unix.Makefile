
targetName=ld_postload

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all


COMMON_FLAGS	+= -I$(cinternalRepoRoot)/src/include

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(cinternalRepoRoot)/src/tools/ld_postload/main_cinternal_tools_ld_postload.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_parser_argparser01.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_loadfreelib_on_remote_process_unix.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_list_llist.c                                       
SOURCES += $(cinternalRepoRoot)/src/intern/cinternal_core_intern_tokenizer01_common.c                            
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_parser_tokenizer01.c

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

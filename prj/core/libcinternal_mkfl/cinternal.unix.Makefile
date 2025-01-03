
targetName=cinternal
libraryVersion=1

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

COMMON_FLAGS += -fPIC
COMMON_FLAGS += -DCINTERNAL_COMPILING_SHARED_LIB

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common.unix.Makefile


SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_hash.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_logger.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_typeinfo.c

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).$(CinternalLibExt).$(libraryVersion)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).$(CinternalLibExt).$(libraryVersion): \
        $(SOURCES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@mkdir -p $(@D)/../lib
	@mkdir -p $(@D)/../tlib
	@$(LINK) $^ -Wl,-soname,lib$(targetName).$(CinternalLibExt).$(libraryVersion) -pie -shared $(LIBS) $(LFLAGS) -o $@
	@rm -f $(@D)/../lib/lib$(targetName).$(CinternalLibExt)
	@cd $(@D)/../lib && ln -s ../dll/lib$(targetName).$(CinternalLibExt).$(libraryVersion) lib$(targetName).$(CinternalLibExt)

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).so*
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/lib/lib$(targetName).so*
	@echo "  " cleaning of $(targetName) complete !!!

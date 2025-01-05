
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
libWithSonameFlags = $(call construct_soname_flags,$(targetName),$(libraryVersion))
libWithSonameBase = $(call construct_soname,$(targetName),$(libraryVersion))
libWithSoname = $(strip $(libWithSonameBase))

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/$(libWithSoname)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/$(libWithSoname): \
        $(SOURCES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@mkdir -p $(@D)/../lib
	@mkdir -p $(@D)/../tlib
	@$(LINK) $^ $(libWithSonameFlags) -shared $(LIBS) $(LFLAGS) -o $@
	@rm -f $(@D)/../lib/lib$(targetName).$(CinternalLibExt)
	@cd $(@D)/../lib && ln -s ../dll/$(libWithSoname) lib$(targetName).$(CinternalLibExt)

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).so*
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/lib/lib$(targetName).so*
	@echo "  " cleaning of $(targetName) complete !!!


targetName=cinternal_unit_test

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
# line below is not needed, just here as a example

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common.unix.Makefile

UTEST_SRCS_DIR=$(cinternalRepoRoot)/src/tests/unit_test
CORE_SRCS_DIR=$(cinternalRepoRoot)/src/core

UTEST_SRCS_CPP	= $(shell find $(UTEST_SRCS_DIR) -name "*.cpp")
UTEST_SRCS_C	= $(shell find $(UTEST_SRCS_DIR) -name "*.c")
CORE_SRCS	= $(shell find $(CORE_SRCS_DIR) -name "*.c")

LIBS += -pthread

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName): \
		$(UTEST_SRCS_CPP:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(UTEST_SRCS_C:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(CORE_SRCS:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of $(targetName) complete !!!

#
# repo:		    cinternal
# file:		    flagsandsys_common.unix.Makefile
# created on:	    2020 Dec 14
# created by:	    Davit Kalantaryan (davit.kalantaryan@desy.de)
# purpose:	    This file can be only as include
#

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
include $(mkfile_dir)/flagsandsys_common_pure.unix.Makefile

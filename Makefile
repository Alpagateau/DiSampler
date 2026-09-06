# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		      := DSampler
GAME_TITLE	  := DSampler
GAME_SUBTITLE	:= PO Compatible DS Sampler

# Source code paths
# -----------------
SOURCE    := source
GFXDIRS		:= graphics
LIBS    := -lmm9 -lnds9
LIBDIRS := $(BLOCKSDS)/libs/maxmod
LIBDIRS += $(BLOCKSDS)/libs/libnds

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile

# Copyright (C) 1999, 2000, 2001 by David A. Capello

EXE = .exe
OBJ = .obj

TARGET_NAME = ../qtetris$(EXE)
TARGET_OBJS = $(addprefix obj/, $(addsuffix $(OBJ), $(basename $(notdir $(TARGET_SRC_FILES)))))

.PHONY: _default

_default: default

$(TARGET_NAME): $(TARGET_OBJS)
	wlink @ldwat.arg

obj/%.obj: %.c
	wcl386.exe -bt=dos4g -5s -s -zq -c $< /fo=$@

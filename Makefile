# Makefile

# ----- COMPILE-TIME DEFINITIONS -----

FEATURES := \
	-DFEATURE_DEBUG_MODE 

# ----- LIBRARIES -----

LIBS := \
	-lSDL2 \
	-lSDL2_ttf

# ----- COMPILER OPTIONS -----

CC := gcc
CC_FLAGS := \
	-Wall \
	-Werror \
	-Isrc

# ----- MANIFEST -----

HEADER_ONLY_FILES := \
	src/debug.h \
	src/type.h

OBJS := \
	build/obj/clock.o \
	build/obj/err.o \
	build/obj/event.o \
	build/obj/gamest.o \
	build/obj/graph.o \
	build/obj/rng.o \
	build/obj/tile.o \
	build/obj/theme.o

# ----- REAL TARGETS -----

build/obj/%.o: src/%.c src/%.h
	@mkdir -p build/obj
	@${CC} $< ${CC_FLAGS} ${LIBS} ${FEATURES} -c -o $@
	@echo "Built target '$@'"

build/bin/letris: src/main.c ${OBJS} ${HEADER_ONLY_FILES}
	@mkdir -p build/bin
	@${CC} $< ${OBJS} ${CC_FLAGS} ${LIBS} ${FEATURES} -o $@ 
	@echo "Built target '$@'"

# ----- PHONY TARGETS -----

.PHONY: \
	all \
	clean

all: build/bin/letris
	@echo "Built all targets"

clean: 
	@rm -rf build
	@echo "Build artifacts successfully cleaned"


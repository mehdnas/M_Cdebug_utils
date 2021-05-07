###########################################
# dependencies ############################
###########################################

DEPENDENCIES_DIR := ./dependencies

# terminal output coloring library
CLROUT_DIR := $(DEPENDENCIES_DIR)/M_clrout
CLROUT_BIN_DIR := $(CLROUT_DIR)/bin
CLROUT_LIB := libclrout.a
CLROUT_H := $(CLROUT_DIR)/clrout.h
CLROUT_LIB_BIN_PATH := $(CLROUT_BIN_DIR)/$(CLROUT_LIB)

# Directories where libraries' binaries are found
LIB_BIN_DIRS := $(CLROUT_BIN_DIR)

###########################################
# Project directories and files ###########
###########################################

# compilation and build directories
BIN_DIR := ./bin
BUILD_DIR := ./build

# Header files
DEBUG_H := debug.h

# Source files
DEBUG_C := debug.c

# Object files
DEBUG_O := $(BUILD_DIR)/$(DEBUG_C:.c=.o)
DEBUG_O_HEADERS := $(DEBUG_H) $(CLROUT_H)

# Library
DEBUG_LIB := $(BIN_DIR)/libCdebug_utils.a
DEBUG_LIB_OBJS := $(DEBUG_O)

# Include directories and global defines
INCLUDE_DIRS := $(CLROUT_DIR)
DEFINES := 

###########################################
# Compilation commands ####################
###########################################

# Compiler options
CC := gcc 
CFLAGS := -Wall -Werror
OUTPUT_FLAG := -o
OBJ_COMPILATION_FLAGS := -c $(OUTPUT_FLAG)
LINKER_FLAGS := $(OUTPUT_FLAG)

# Add option prefix to the include and lib directories and defines
GCC_INC_DIRS := $(addprefix -I, $(INCLUDE_DIRS))
GCC_LIB_DIRS := $(addprefix -L, $(LIB_BIN_DIRS))
GCC_DEFS := $(addprefix -D, $(DEFINES))

#build commands
#compile objects
COBJ := $(CC) $(CFLAGS) $(GCC_INC_DIRS) $(GCC_DEFS) $(OBJ_COMPILATION_FLAGS)
#link and generate an executable
CEXE := $(CC) $(CFLAGS) $(GCC_LIB_DIRS) $(LINKER_FLAGS)
# compile a library directory
MAKE_LIB := make -C

###########################################
# Compilation rules and recipes ##########
###########################################

# executables
all: $(BUILD_DIR) $(BIN_DIR) $(DEBUG_LIB)

$(BUILD_DIR):
	mkdir -p $@ 

$(BIN_DIR):
	mkdir -p $@

$(DEBUG_LIB): $(DEBUG_LIB_OBJS)
	ar r $@ $^
	ranlib $@

$(DEBUG_O): $(DEBUG_C) $(DEBUG_O_HEADERS)
	$(COBJ) $@ $<

clean:
	if [ -d "$(BUILD_DIR)" ]; then rm -r $(BUILD_DIR); fi


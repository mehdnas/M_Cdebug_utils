# Include directories and global defines
INCLUDE_DIRS := ./M_clrout
DEFINES := 

# Compiler options
CC := gcc 
CFLAGS := -Wall -Werror
OUTPUT_FLAG := -o
OBJ_COMPILATION_FLAGS := -c $(OUTPUT_FLAG)
LINKER_FLAGS := $(OUTPUT_FLAG)
GCC_INC_DIRS := $(addprefix -I, $(INCLUDE_DIRS))
GCC_DEFS := $(addprefix -D, $(DEFINES))

#build commands
#compile
COBJ := $(CC) $(CFLAGS) $(GCC_INC_DIRS) $(GCC_DEFS) $(OBJ_COMPILATION_FLAGS)
#link and generate an executable
CEXE := $(CC) $(CFLAGS) $(LINKER_FLAGS)
# compile a library directory
MAKE_LIB := make -C

# Files and directories
BIN_DIR := ./bin
BUILD_DIR := ./build

OUTPUT_FILE := $(BIN_DIR)/libCdebug_utils.a

OBJECTS := $(BUILD_DIR)/debug.o

HEADER_FILES := debug.h

$(OUTPUT_FILE): $(OBJECTS) $(BIN_DIR) $()
	ar r $@ $(OBJECTS)
	ranlib $@

$(BIN_DIR):
	mkdir -p $@

$(OBJECTS): $(BUILD_DIR)/%.o: %.c $(HEADER_FILES) $(BUILD_DIR)
	$(COBJ) $@ $<

$(CLROUT_LIB):
	$(MAKE_LIB) $(CLROUT_DIR)

$(BUILD_DIR):
	mkdir -p $@	

clean:
	rm -r $(BUILD_DIR)
	rm -r $(BIN_DIR)


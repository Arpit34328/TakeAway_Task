# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./library

# Diractories
SRC_DIR = source
BIN_DIR = bin
BUILD_DIR = build

# Output binary
Target = $(BIN_DIR)/main

# Find all .c files in src diractory and its subduractories, excluding specific files
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Default target to build everything
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(OBJ_FILES) -o $(TARGET)

# Rule to compile source files to object files
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	@./$(TARGET)

# Clean up object files and binaries
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild everything from scratch
rebuild: clean all

# Declare phony targets (they aren't files)
.PHONY: all clean rebuild run

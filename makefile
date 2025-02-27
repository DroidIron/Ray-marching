# Source files directory:
SRC_DIR := src

# Build files directory:
BUILD_DIR := build

# Finds all C source files:
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Replaces the src/ prefix with build/ prefix and the .c with .o for every src file:
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Compiler flags:
CFLAGS := -Iinclude

# Linker flags:
LDFLAGS := -Llib -lSDL3

# Target executable:
TARGET := main

# Default target:
all: $(TARGET)

# Link the .o files to the TARGET:
$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile each .c file to a .o file in the build directory:
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	gcc -c $< -o $@ $(CFLAGS)

# Clean up:
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
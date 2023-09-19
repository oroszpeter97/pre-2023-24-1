# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Isrc -g
LDFLAGS = -lm

# Directories
SRC_DIR = src
ASSETS_DIR = $(SRC_DIR)/assets
BIN_DIR = bin

# Source files
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))

# Executable name
TARGET = $(BIN_DIR)/engine

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compilation
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

# Run target
run: $(TARGET)
	clear
	./$(TARGET)

# Clean the log files
clean_logs:
	rm -f logs/*

# Clean target
clean:
	rm -rf $(BIN_DIR)/*
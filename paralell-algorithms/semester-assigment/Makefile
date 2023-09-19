# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -fopenmp

# Source files
SRCS = main.c helper-libraries/error_library.c helper-libraries/validity_checker.c helper-libraries/dynamic_int_array.c helper-libraries/timer.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = semester_assignment

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Compile each source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
ifndef ARGS
	@echo "Please provide arguments. Usage: make run ARGS=<arguments>"
else
	./$(TARGET) $(ARGS)
endif

# Debug run with default args
debug: $(TARGET)
	clear
	make clean
	./$(TARGET) 10000 0 100 10

# Open the documentation
documentation:
	doxygen ../documentation.conf
    # Check the operating system
    ifeq ($(OS),Windows_NT)
        start html/index.html
    else
        # Assume Unix-like operating system (Linux, macOS)
		open html/index.html
    endif

# The programs help argument
help:
	make
	./$(TARGET) -help

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

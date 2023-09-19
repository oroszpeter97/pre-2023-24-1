# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pthread

# Source files
SRCS = main.c helper-libraries/validator.c helper-libraries/timer.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = semester_assignment

# Compile the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Compile each source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Debug run with default args
debug: $(TARGET)
	./$(TARGET) 10000 0 100 2

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)	
# Java compiler
JC = javac

# Java runtime
JVM = java

# Source files directory
SRC_DIR = src/com/wo02d7/semesterassigment

# Class files directory
BIN_DIR = bin

# Main class name
MAIN_CLASS = com.wo02d7.semesterassigment.Main

# Source files
SOURCES = $(SRC_DIR)/Range.java $(SRC_DIR)/SpecializedArray.java $(SRC_DIR)/Main.java

# Target: build
build:
	$(JC) -d $(BIN_DIR) -sourcepath $(SRC_DIR) $(SOURCES)

# Target: run
run:
	$(JVM) -cp $(BIN_DIR) $(MAIN_CLASS) $(ARGS)

# Target: debug
debug:
	$(JVM) -cp $(BIN_DIR) $(MAIN_CLASS) 10000 0 100 1

# Target: clean
clean:
	rm -rf $(BIN_DIR)

# Target: rebuild
rebuild: clean build	
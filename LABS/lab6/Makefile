# Compiler to use
CXX = g++

# Compiler flags:
# -std=c++11  : Use C++11 standard
# -g          : Add debugging information
# -Wall       : Enable all basic warnings
# -Wextra     : Enable extra warnings
# -Wpedantic  : Issue warnings demanded by strict ISO C and ISO C++
CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wpedantic

# Additional flags for generating header dependencies
CPPFLAGS = -MMD -MP

# Directory for object files and dependency files
BUILD_DIR = build

# Source files (all .cpp files)
SRCS = ascii_art.cpp main.cpp twod_array.cpp

# Object files (replace .cpp with .o and add BUILD_DIR prefix)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Dependency files (one per source file)
DEPS = $(OBJS:.o=.d)

# Name of the final executable
TARGET = main.exe

# Default target (first target is default)
all: $(TARGET)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to create the final executable
# Links all object files together
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile source files to object files
# $@ = target file name
# $< = first prerequisite name (the .cpp file)
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean rule to remove generated files
clean:
	del /Q $(BUILD_DIR)\*.o $(BUILD_DIR)\*.d

# Deeper clean (removes executable too)
distclean: clean
	del /Q $(TARGET)

# .PHONY tells Make these targets don't create files
.PHONY: all clean distclean

# Help target to display available commands
help:
	@echo Available targets:
	@echo   all        : Build the executable (default target)
	@echo   clean      : Remove object files and dependency files
	@echo   distclean  : Remove all generated files including executable
	@echo   help       : Display this help message
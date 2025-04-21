# Compiler
CXX = g++
# Compile flags: -g for debugging, -Wall for warnings, -std=c++11 or higher
CXXFLAGS = -g -Wall -std=c++11

# Source files directory (assuming they are in the same directory as the Makefile)
SRC_DIR = .
# Build directory for object and dependency files
BUILD_DIR = build

# Source files (find all .cpp files in SRC_DIR)
# SRCS = $(wildcard $(SRC_DIR)/*.cpp) # Alternative if you want all .cpp files
SRCS = games.cpp board.cpp players.cpp bots.cpp test.cpp

# Object files (place them in BUILD_DIR)
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
# Dependency files (place them in BUILD_DIR)
DEPS = $(OBJS:.o=.d)

# Header files (for dependency tracking - assuming they are in SRC_DIR)
# No need to list them explicitly if using dependency generation correctly
# HDRS = games.h board.h players.h bots.h utils.h

# Target executable name
TARGET = main

# Default rule: build the target executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build finished: $(TARGET)"

# Rule to create the build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to compile .cpp files into .o files in the BUILD_DIR
# It depends on the BUILD_DIR existing
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include generated dependency files
# The '-' suppresses errors if the .d files don't exist yet
-include $(DEPS)

# Rule to clean up generated files
clean:
	@echo "Cleaning..."
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR) # Remove the entire build directory
	@echo "Clean complete."

# Phony targets are rules that don't represent actual files
.PHONY: all clean


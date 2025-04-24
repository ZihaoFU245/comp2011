# Compiler
CXX = g++
# Compile flags: -g for debugging, -Wall for warnings, -std=c++11 or higher
# Add flags for shared library and position independent code (PIC)
CXXFLAGS = -g -Wall -std=c++11 -shared -fPIC

# --- Python/pybind11 Configuration ---
# Use python to get necessary flags (adjust 'python' if needed)
PYBIND11_INCLUDES = $(shell python -m pybind11 --includes)
PYTHON_INCLUDES = $(shell python -c "import sysconfig; print('-I' + sysconfig.get_path('include'))")
# Get Python library path and library name/flags
PYTHON_LIB_PATH = $(shell python -c "import sysconfig; print('-L' + sysconfig.get_config_var('LIBDIR'))")
PYTHON_LIB = $(shell python -c "import sysconfig; print('-lpython' + sysconfig.get_config_var('VERSION'))") # e.g., -lpython313

# Combine CXXFLAGS with Python/pybind11 includes
CXXFLAGS += $(PYBIND11_INCLUDES) $(PYTHON_INCLUDES)

# --- MinGW Runtime DLLs (Adjust path if your MSYS2 is different) ---
MINGW_BIN_PATH = D:/MSYS2/ucrt64/bin
# Common runtime DLLs needed by GCC builds on Windows
RUNTIME_DLLS = $(MINGW_BIN_PATH)/libstdc++-6.dll $(MINGW_BIN_PATH)/libgcc_s_seh-1.dll
# Add others if needed, e.g., $(MINGW_BIN_PATH)/libwinpthread-1.dll

# --- Project Files ---
# Source files directory
SRC_DIR = .
# Build directory for object and dependency files
BUILD_DIR = build

# Source files for the module (excluding test.cpp)
SRCS = games.cpp board.cpp players.cpp bots.cpp TicTakToe.cpp # Corrected: player.cpp not players.cpp

# Object files (place them in BUILD_DIR)
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
# Dependency files (place them in BUILD_DIR)
DEPS = $(OBJS:.o=.d)

# Target module name (must match PYBIND11_MODULE name)
MODULE_NAME = TicTakToe
# Determine Python extension suffix (.pyd for Windows, .so for others)
ifeq ($(OS),Windows_NT)
    MODULE_EXT = .pyd
else
    MODULE_EXT = .so
endif
TARGET = $(MODULE_NAME)$(MODULE_EXT)

# Default rule: build the target module
all: $(TARGET) copy_dlls

# Rule to link the Python module (shared library)
$(TARGET): $(OBJS)
	@echo "Linking Python module..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(PYTHON_LIB_PATH) $(PYTHON_LIB)
	@echo "Build finished: $(TARGET)"

# Rule to copy runtime DLLs (Windows specific)
copy_dlls: $(TARGET)
ifeq ($(OS),Windows_NT)
	@echo "Copying runtime DLLs..."
	@for dll in $(RUNTIME_DLLS); do \
		if [ -f $$dll ]; then \
			cp $$dll . ; \
		else \
			echo "Warning: DLL $$dll not found." ; \
		fi; \
	done
	@echo "DLLs copied (if found)."
else
	@echo "Skipping DLL copy on non-Windows OS."
endif

# Rule to create the build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to compile .cpp files into .o files in the BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include generated dependency files
-include $(DEPS)

# Rule to clean up generated files
clean:
	@echo "Cleaning..."
	rm -f $(TARGET)
	# Also remove copied DLLs
ifeq ($(OS),Windows_NT)
	@for dll in $(RUNTIME_DLLS); do \
		rm -f $(notdir $$dll) ; \
	done
endif
	rm -rf $(BUILD_DIR) # Remove the entire build directory
	@echo "Clean complete."

# Phony targets
.PHONY: all clean copy_dlls


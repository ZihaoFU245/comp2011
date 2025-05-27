# config
TARGET_NAME := main
TARGET_NAME_DEBUG := $(TARGET_NAME)_debug

SRC_DIR := .
BUILD_DIR := build
DEBUG_SUBDIR := debug

# tools
CXX ?= g++
ifeq (Windows_NT,$(OS))
	CMD_RM := del
	# use -p flag to avoid error if directory exists
	CMD_MKDIR := mkdir -p
else
	CMD_RM := rm -fv
	CMD_MKDIR := mkdir -p
endif

CXXFLAGS := -std=c++11 -g -Wall -Wextra -Wpedantic
CXXOBJFLAGS := -c $(CXXFLAGS)
CXXFLAGS_DEBUG := -std=c++11 -g -Wall -Wextra -Wpedantic -fsanitize=address,leak,undefined
CXXOBJFLAGS_DEBUG := -c $(CXXFLAGS_DEBUG)

# files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

OBJ_FILES_DEBUG := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/$(DEBUG_SUBDIR)/%.o,$(SRC_FILES))
DEP_FILES_DEBUG := $(OBJ_FILES_DEBUG:.o=.d)

TARGET := $(TARGET_NAME)
TARGET_DEBUG := $(TARGET_NAME_DEBUG)
ifeq (Windows_NT,$(OS))
	TARGET := $(addsuffix .exe,$(TARGET))
	TARGET_DEBUG := $(addsuffix .exe,$(TARGET_DEBUG))
endif

CLEAN_FILES := $(OBJ_FILES) $(DEP_FILES) $(OBJ_FILES_DEBUG) $(DEP_FILES_DEBUG)
DISTCLEAN_FILES := $(CLEAN_FILES) $(TARGET) $(TARGET_DEBUG)

# default target
.PHONY: default
default: build

# commands
.PHONY: all
all: build debug

.PHONY: build
build: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo cleaning $(CLEAN_FILES)
	-$(CMD_RM) $(CLEAN_FILES)

.PHONY: distclean
distclean:
	@echo cleaning $(DISTCLEAN_FILES)
	-$(CMD_RM) $(DISTCLEAN_FILES)

# file targets
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_DEBUG): $(OBJ_FILES_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c*
	@$(CMD_MKDIR) $(@D)
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

$(BUILD_DIR)/$(DEBUG_SUBDIR)/%.o: $(SRC_DIR)/%.c*
	@$(CMD_MKDIR) $(@D)
	$(CXX) $(CXXOBJFLAGS_DEBUG) -o $@ $<

# automatic dependency graph generation
CXXFLAGS += -MMD -MP
CXXOBJFLAGS += -MMD -MP
CXXFLAGS_DEBUG += -MMD -MP
CXXOBJFLAGS_DEBUG += -MMD -MP
-include $(DEP_FILES) $(DEP_FILES_DEBUG)

# config
TARGET_NAME := main

SRC_DIR := .
BUILD_DIR := build

# tools
CXX ?= g++
ifeq (Windows_NT,$(OS))
	CMD_RM := del
	CMD_MKDIR := mkdir
else
	CMD_RM := rm -fv
	CMD_MKDIR := mkdir -p
endif

CXXFLAGS := -std=c++11 -g -Wall -Wextra -Wpedantic
CXXOBJFLAGS := -c $(CXXFLAGS)

# files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

TARGET := $(TARGET_NAME)
ifeq (Windows_NT,$(OS))
	TARGET := $(addsuffix .exe,$(TARGET))
endif

CLEAN_FILES := $(OBJ_FILES) $(DEP_FILES)
DISTCLEAN_FILES := $(CLEAN_FILES) $(TARGET)

# default target
.PHONY: default
default: build

# commands
.PHONY: all
all: build

.PHONY: build
build: $(TARGET)

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

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c*
	@$(CMD_MKDIR) $(@D)
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

# automatic dependency graph generation
CXXFLAGS += -MMD -MP
CXXOBJFLAGS += -MMD -MP
-include $(DEP_FILES)

CXX = g++
CXXFLAGS = -Wall -std=c++11
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

BUILD_DIR = build
TARGET = main.exe
SRCS = main.cpp LinkedList.cpp
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default to debug build
CXXFLAGS += $(DEBUG_FLAGS)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

.PHONY: debug release clean

clean:
	rmdir /s /q $(BUILD_DIR)
	del $(TARGET)

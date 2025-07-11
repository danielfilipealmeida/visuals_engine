SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
LIB_NAME := libEngine.a

OF_ROOT ?= ../../../..
$(info OF_ROOT: $(OF_ROOT))
OF_INCLUDES := \
  -I$(OF_ROOT)/libs \
  -I$(OF_ROOT)/libs/glm/include \
  -I$(OF_ROOT)/libs/glew/include \
  -I$(OF_ROOT)/libs/openFrameworks \
  -I$(OF_ROOT)/libs/openFrameworks/types \
  -I$(OF_ROOT)/libs/openFrameworks/utils \
  -I$(OF_ROOT)/libs/openFrameworks/graphics \
  -I$(OF_ROOT)/libs/openFrameworks/events \
  -I$(OF_ROOT)/libs/openFrameworks/video \
  -I$(OF_ROOT)/libs/openFrameworks/app \
  -I$(OF_ROOT)/libs/openFrameworks/sound \
  -I$(OF_ROOT)/libs/openFrameworks/3d \
  -I$(OF_ROOT)/libs/openFrameworks/math \
  -I$(OF_ROOT)/libs/openFrameworks/gl \
  -I$(OF_ROOT)/libs/openFrameworks/communication \
  -I$(OF_ROOT)/libs/tess2/include \
  -I$(OF_ROOT)/libs/utf8/include \
  -I$(OF_ROOT)/libs/json/include \
  -I$(OF_ROOT)/libs/pugixml/include \
  -I$(OF_ROOT)/libs/cairo/include/cairo


SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
$(info SRCS: $(SRCS))

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
$(info OBJS: $(OBJS))

INCLUDE_DIRS := $(shell find $(SRC_DIR) -type d)
$(info INCLUDE_DIRS: $(INCLUDE_DIRS))



CXX := g++
CXXFLAGS := -std=c++17 $(addprefix -I, $(INCLUDE_DIRS)) $(OF_INCLUDES)


# === BUILD RULES ===

all: $(LIB_DIR)/$(LIB_NAME)

# Compile .cpp → .o preserving path
$(BUILD_DIR)/%.o: $(SR_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all .o into static lib
$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)/$(LIB_NAME)


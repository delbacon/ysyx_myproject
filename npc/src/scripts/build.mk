.DEFAULT_GOAL = app

WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

INC_PATH := $(WORK_DIR)/src/include $(INC_PATH)
OBJ_DIR  = $(BUILD_DIR)/obj$(NAME)so

# 不带波形追踪的可执行文件（用于 run）
BINARY_NO_TRACE = $(OBJ_DIR)/V$(TOP_MODULE)
# 带 --trace-fst 的可执行文件（用于 sim）
BINARY_WITH_TRACE = $(OBJ_DIR)/V$(TOP_MODULE)_with_trace


#-------------------------
# Tool Chain Configuration
#-------------------------
VERILATOR := verilator
YOSYS := yosys
GTKWAVE := gtkwave

CXX := g++
LD := $(CXX)

#-------------------------
# Project Configuration
#-------------------------
TOP_MODULE := ysyx_26020055_top

#-------------------------
# Compiler Flags
#-------------------------
# Compilation flags
INCLUDES = $(addprefix -I, $(INC_PATH))
CFLAGS  := -O2 -MMD -Wall -Werror $(INCLUDES) -DTOP_NAME="\"V$(TOP_MODULE)\"" $(CFLAGS) 
LDFLAGS := -O2 $(LDFLAGS)

# Verilator optimization flags
# 通用参数（不含 trace）
VERILATOR_COMMON_FLAGS = --cc --exe --build -j 0 -Wall --top-module $(TOP_MODULE)
VERILATOR_CFLAGS := -MMD --build -cc
VERILATOR_CFLAGS += -x-assign fast --x-initial fast --noassert

# Linker flags 动态库链接
LDFLAGS += -lreadline
LDFLAGS += -L$(NEMU_HOME)/build -Wl,-rpath=$(NEMU_HOME)/build -lriscv32-nemu-interpreter-so

# 不带 trace 的 CXXFLAGS
CXXFLAGS_NO_TRACE = $(CXXFLAGS)
# 带 trace 的 CXXFLAGS（额外加上 -DWAVE_TRACE 参数）
CXXFLAGS_WITH_TRACE = $(CXXFLAGS) -DWAVE_TRACE

# Some convenient rules
.PHONY: app clean

app: $(BINARY_NO_TRACE)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):$(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

# 编译不带 trace 的版本
$(BINARY_NO_TRACE): $(VSRCS) $(CSRCS) $(OBJ_DIR)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CFLAGS) $(CXXFLAGS_NO_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

# 编译带 --trace-fst 的版本
$(BINARY_WITH_TRACE): $(VSRCS) $(CSRCS) $(OBJ_DIR)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) --trace-fst \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS_WITH_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

clean:
	-rm -rf $(BUILD_DIR)


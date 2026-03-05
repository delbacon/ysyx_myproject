#-------------------------
# Project Configuration
#-------------------------
TOPNAME = $(TOP_MODULE)
NXDC_FILES = constr/$(TOPNAME).nxdc
TOP_MODULE := ysyx_26020055_top

# Directories
BUILD_DIR = ./build
OBJ_DIR = ./obj_dir
OBJ_DIR_NO_TRACE = $(OBJ_DIR)/obj_dir_no_trace
OBJ_DIR_WITH_TRACE = $(OBJ_DIR)/obj_dir_with_trace
REPO_DIR = $(BUILD_DIR)/report

# Binary output
BIN = $(BUILD_DIR)/$(TOPNAME)

#-------------------------
# Tool Chain Configuration
#-------------------------
VERILATOR := verilator
YOSYS := yosys
GTKWAVE := gtkwave

#-------------------------
# Build Mode Configuration
#-------------------------
# Optimization level: 0, 1, 2, 3
OPT ?= 2


# Verilator optimization flags
VERILATOR_CFLAGS := -MMD --build -cc
VERILATOR_CFLAGS += -x-assign fast --x-initial fast --noassert
# Add optimization based on OPT level
ifeq ($(OPT),0)
	VERILATOR_CFLAGS += -O0
else ifeq ($(OPT),1)
	VERILATOR_CFLAGS += -O1
else ifeq ($(OPT),2)
	VERILATOR_CFLAGS += -O2
else
	VERILATOR_CFLAGS += -O3
endif


#-------------------------
# Source File Management
#-------------------------
# Find all Verilog sources
VSRCS := $(shell find $(abspath ./vsrc) -name "*.v" -o -name "*.sv")

# Auto-generated source from constraint files
# SRC_AUTO_BIND := $(abspath $(BUILD_DIR)/auto_bind.cpp)

# Find all C/C++ sources (unified definition)
CSRCS := $(shell find $(abspath ./csrc) \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" \))
# CSRCS += $(SRC_AUTO_BIND)

# Total sources
ALL_SRCS := $(VSRCS) $(CSRCS)


#-------------------------
# Compiler Flags
#-------------------------
# Include paths
INC_PATH ?=
INCFLAGS := $(addprefix -I, $(INC_PATH))
INCFLAGS += -I$(abspath ./csrc/include)

# Preprocessor definitions
CXXFLAGS += $(INCFLAGS)
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
CXXFLAGS += -Wall -Wextra
# 通过 -D(XXX) 可以在编译时传入宏定义



# Linker flags
LDFLAGS += -lreadline
#-------------------------
# Rules for Constraint Files
#-------------------------
# $(SRC_AUTO_BIND): $(NXDC_FILES) | $(BUILD_DIR)
# 	@echo "Generating auto_bind.cpp from $(NXDC_FILES)"
#	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

#-------------------------
# Main Build Target
#-------------------------
default: $(BIN)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_NO_TRACE):
	@mkdir -p $(OBJ_DIR_NO_TRACE)

$(OBJ_DIR_WITH_TRACE):
	@mkdir -p $(OBJ_DIR_WITH_TRACE)
#-------------------------
# Rules for NVBoard
#-------------------------
# include $(NVBOARD_HOME)/scripts/nvboard.mk


#-------------------------
# Simulation Targets
#-------------------------
# Image file for simulation (use relative path)
IMG ?= ../am-kernels/tests/cpu-tests/build/div-minirv-npc.bin

# Check if image file exists
ifeq ($(wildcard $(IMG)),)
  $(warning Warning: IMG not found: $(IMG))
endif

# 不带波形追踪的可执行文件（用于 run）
OBJ_NO_TRACE = $(OBJ_DIR_NO_TRACE)/V$(TOPNAME)
# 带 --trace-fst 的可执行文件（用于 sim）
OBJ_WITH_TRACE = $(OBJ_DIR_WITH_TRACE)/V$(TOPNAME)

# 通用参数（不含 trace）
VERILATOR_COMMON_FLAGS = --cc --exe --build -j 0 -Wall --top-module $(TOP_MODULE)

# 不带 trace 的 CXXFLAGS
CXXFLAGS_NO_TRACE = $(CXXFLAGS)

# 带 trace 的 CXXFLAGS（额外加上 -DWAVE_TRACE 参数）
CXXFLAGS_WITH_TRACE = $(CXXFLAGS) -DWAVE_TRACE

# 编译不带 trace 的版本
$(OBJ_NO_TRACE): $(VSRCS) $(CSRCS) $(BUILD_DIR) $(OBJ_DIR_NO_TRACE)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS_NO_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

# 编译带 --trace-fst 的版本
$(OBJ_WITH_TRACE): $(VSRCS) $(CSRCS) $(BUILD_DIR) $(OBJ_DIR_WITH_TRACE)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) --trace-fst \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS_WITH_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

# run 使用无 trace 版本
run: $(OBJ_NO_TRACE)
	@if [ ! -f "$(IMG)" ]; then \
		echo "Error: Image file not found: $(IMG)"; \
		exit 1; \
	fi
	./$(OBJ_NO_TRACE) $(IMG)

# sim 使用带 trace 版本，并打开波形
sim: $(OBJ_WITH_TRACE)
	$(call git_commit, "sim RTL")
	@if [ ! -f "$(IMG)" ]; then \
		echo "Error: Image file not found: $(IMG)"; \
		exit 1; \
	fi
	./$(OBJ_WITH_TRACE) $(IMG)

	$(GTKWAVE) waveform.* 2>/dev/null || echo "gtkwave not found or no waveform"


#-------------------------
# Yosys Synthesis & STA
#-------------------------
PROJ_PATH = $(shell pwd)
YOSYS_STA_HOME ?= $(HOME)/software/yosys-sta
YOSYS_STA_SCRIPTS ?= $(YOSYS_STA_HOME)/scripts
IEDA ?= $(YOSYS_STA_HOME)/bin/iEDA

SDC_FILE ?= $(YOSYS_STA_SCRIPTS)/default.sdc
RTL_FILES ?= $(shell find $(PROJ_PATH)/vsrc -name "*.v")
CLK_FREQ_MHZ ?= 500
export CLK_FREQ_MHZ
CLK_PORT_NAME ?= clk
export CLK_PORT_NAME
PDK := icsprout55

O ?= $(PROJ_PATH)/result
DESIGN ?= $(TOPNAME)
RESULT_DIR = $(O)/$(DESIGN)-$(CLK_FREQ_MHZ)MHz
NETLIST_SYN_V   = $(RESULT_DIR)/$(DESIGN).netlist.v
TIMING_RPT = $(RESULT_DIR)/$(DESIGN).rpt

# yosys

# Example:
#   make -C npc sta \
#     YOSYS_STA_HOME=$(HOME)/Learn/yosys-sta \
#     DESIGN=mydesign SDC_FILE=/path/to/my.sdc \
#     CLK_FREQ_MHZ=100 CLK_PORT_NAME=clk O=/path/to/pwd \
#     RTL_FILES="/path/to/mydesign.v /path/to/xxx.v ..."

check-yosys-sta:
	@test -f "$(YOSYS_STA_SCRIPTS)/yosys.tcl" || \
		(echo "Error: missing $(YOSYS_STA_SCRIPTS)/yosys.tcl. Set YOSYS_STA_HOME=..."; exit 1)
	@test -f "$(YOSYS_STA_SCRIPTS)/sta.tcl" || \
		(echo "Error: missing $(YOSYS_STA_SCRIPTS)/sta.tcl. Set YOSYS_STA_HOME=..."; exit 1)
	@test -x "$(IEDA)" || \
		(echo "Error: missing or non-executable $(IEDA). Set YOSYS_STA_HOME=..."; exit 1)

check-sdc:
	@test -f "$(SDC_FILE)" || \
		(echo "Error: SDC_FILE not found: $(SDC_FILE)"; exit 1)

syn: $(NETLIST_SYN_V)
$(NETLIST_SYN_V): $(RTL_FILES) | check-yosys-sta $(RESULT_DIR)
	@echo "Running Yosys synthesis..."
	echo tcl $(YOSYS_STA_SCRIPTS)/yosys.tcl $(DESIGN) $(PDK) \"$(RTL_FILES)\" $@ | \
		$(YOSYS) -g -l $(@D)/yosys.log -s -
	@echo "✓ Synthesis complete: $@"

sta: $(TIMING_RPT)
$(TIMING_RPT): $(NETLIST_SYN_V) | check-yosys-sta check-sdc
	@echo "Running static timing analysis..."
	set -o pipefail && \
	$(IEDA) -script $(YOSYS_STA_SCRIPTS)/sta.tcl $(SDC_FILE) $(NETLIST_SYN_V) $(DESIGN) $(PDK) 2>&1 | \
		tee $(RESULT_DIR)/sta.log
	@echo "✓ STA complete: $(TIMING_RPT)"

#-------------------------
# Clean Targets
#-------------------------
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)
	rm -f waveform.*
	@echo "✓ Clean complete"

clean-NV:
	rm -rf $(BUILD_DIR)

clean-yosys:
	rm -rf $(O) $(RESULT_DIR)

clean-all: clean clean-NV clean-yosys
	@echo "✓ All clean complete"

#-------------------------
# Help Target
#-------------------------
help:
	@echo "NPC Project Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make              - Build the project (default)"
	@echo "  make all          - Same as make"
	@echo "  make run          - Run quick simulation"
	@echo "  make sim          - Run simulation with waveform(#define WAVE_TRACE)"
	@echo "  make syn          - Run Yosys synthesis"
	@echo "  make sta          - Run static timing analysis"
	@echo ""
	@echo "Configuration:"
	@echo "  OPT=0|1|2|3       - Optimization level (default: 2)"
	@echo "  IMG=<path>        - Path to binary image"
	@echo ""
	@echo "Examples:"
	@echo "  make run"
	@echo "  make sim"
	@echo "  make run IMG=test.bin"
	@echo ""



#-------------------------
# Phony Targets
#-------------------------
.PHONY: default all clean clean-all clean-NV clean-yosys \
        run sim syn sta help \
        check-yosys-sta check-sdc



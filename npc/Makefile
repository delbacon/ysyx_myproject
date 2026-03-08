# Include all filelist.mk to merge file lists
FILELIST_MK = $(shell find -L ./src -name "filelist.mk")
include $(FILELIST_MK)


#-------------------------
# Project Configuration
#-------------------------
TOPNAME = $(TOP_MODULE)
NXDC_FILES = constr/$(TOPNAME).nxdc
TOP_MODULE := ysyx_26020055_top

# Directories
BUILD_DIR = $(NPC_HOME)/build
OBJ_DIR = $(BUILD_DIR)/obj_dir
OBJ_DIR_NO_TRACE = $(OBJ_DIR)/obj_dir_no_trace
OBJ_DIR_WITH_TRACE = $(OBJ_DIR)/obj_dir_with_trace

# Binary output
BIN = $(IMG).bin

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
OPT ?= CONFIG_OPT_LEVEL


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
CSRCS += $(filter-out $(SRCS-BLACKLIST-y),$(SRCS-y))
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


# Linker flags 动态库链接
LDFLAGS += "-lreadline"
LDFLAGS += -Wl,--no-as-needed 
LDFLAGS += -L$(NEMU_HOME)/build -Wl,-rpath=$(NEMU_HOME)/build -lriscv32-nemu-interpreter-so
LDFLAGS += -Wl,--as-needed  
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
include $(NVBOARD_HOME)/scripts/nvboard.mk


#-------------------------
# Simulation Targets
#-------------------------
# Image file for simulation (use relative path)
# IMG ?= ../am-kernels/tests/cpu-tests/build/div-minirv-npc.bin
# IMG ?= ../am-kernels/tests/am-tests/build/amtest-minirv-npc.bin
ELF_FILE = $(IMG).elf
DIFF_FILE = $(NEMU_HOME)/build/libriscv32-nemu-interpreter-so.so
# Run args
LOG_FILE = $(IMG).log

RUNARGS =  -l $(LOG_FILE) 
RUNARGS += --diff  $(DIFF_FILE)
RUNARGS += $(BIN) # RUN
RUNARGS_NO_TRACE ?=  --elf-input  $(ELF_FILE) $(RUNARGS)
RUNARGS_WITH_TRACE ?=  --elf-input  $(ELF_FILE) $(RUNARGS)
# 不带波形追踪的可执行文件（用于 run）
OBJ_NO_TRACE = $(OBJ_DIR)/V$(TOPNAME)
# 带 --trace-fst 的可执行文件（用于 sim）
OBJ_WITH_TRACE = $(OBJ_DIR)/V$(TOPNAME)_with_trace

# 通用参数（不含 trace）
VERILATOR_COMMON_FLAGS = --cc --exe --build -j 0 -Wall --top-module $(TOP_MODULE)

# 不带 trace 的 CXXFLAGS
CXXFLAGS_NO_TRACE = $(CXXFLAGS)

# 带 trace 的 CXXFLAGS（额外加上 -DWAVE_TRACE 参数）
CXXFLAGS_WITH_TRACE = $(CXXFLAGS) -DWAVE_TRACE


# 收集所有头文件依赖
HEADERS := $(shell find $(abspath ./csrc/include) -name "*.h")
KCONFIG_FILE := $(NPC_HOME)/Kconfig
CONFIG_FILE := $(NPC_HOME)/.config
CONFIG_HEADER := $(NPC_HOME)/csrc/include/config.h

# 编译不带 trace 的版本
$(OBJ_NO_TRACE): $(VSRCS) $(CSRCS) $(HEADERS) $(CONFIG_HEADER) | $(BUILD_DIR) $(OBJ_DIR)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS_NO_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

# 编译带 --trace-fst 的版本
$(OBJ_WITH_TRACE): $(VSRCS) $(CSRCS) $(HEADERS) $(CONFIG_HEADER) | $(BUILD_DIR) $(OBJ_DIR)
	mkdir -p $(dir $@)
	verilator $(VERILATOR_COMMON_FLAGS) --trace-fst \
		$(CSRCS) $(VSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS_WITH_TRACE)) \
		$(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(dir $@) \
		-o $(notdir $@)

# run 使用无 trace 版本
run: $(OBJ_NO_TRACE)
	@if [ ! -f "$(BIN)" ]; then \
		echo "Error: Image file not found: $(BIN)"; \
		exit 1; \
	fi
	$(OBJ_NO_TRACE) $(RUNARGS_NO_TRACE)

# sim 使用带 trace 版本，并打开波形
sim: $(OBJ_WITH_TRACE)
	$(call git_commit, "sim RTL")
	@if [ ! -f "$(BIN)" ]; then \
		echo "Error: Image file not found: $(BIN)"; \
		exit 1; \
	fi
	$(OBJ_WITH_TRACE) $(RUNARGS_WITH_TRACE)

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


# ====================================================================
# Kconfig-based Configuration System (for C/C++ macros)
# ====================================================================


# Ensure include dir exists
$(shell mkdir -p csrc/include)

# Add config.h to include path (so your C code can #include "config.h")
INCFLAGS += -I$(abspath ./csrc/include)

# Default Python
PYTHON3 ?= python3

# Launch graphical configuration (requires kconfiglib + windows-curses on Windows)
menuconfig:
	@echo "Starting menuconfig interface..."
	@PYTHONPATH=. python3 -c "from menuconfig import menuconfig; from kconfiglib import Kconfig; menuconfig(Kconfig('Kconfig'))" && touch $(NPC_HOME)/.config
	@echo "Configuration updated, regenerating config header..."
	@$(MAKE) gen-config
	@echo "Menuconfig completed successfully."
# Ensure include dir exists
$(shell mkdir -p csrc/include)

# Add config.h to include path (so your C code can #include "config.h")
INCFLAGS += -I$(abspath ./csrc/include)

# Generate config header when .config changes
$(CONFIG_HEADER): $(CONFIG_FILE)
	@echo "Generating config header from .config..."
	@mkdir -p $(dir $@)
	@if [ -f $< ]; then \
	{ \
		echo "/* Auto-generated from .config, do not edit! */"; \
		while IFS='=' read -r key val; do \
			case "$$key" in \#*) continue ;; esac; \
			if [ -n "$$key" ] && [ "$${key#CONFIG_}" != "$$key" ]; then \
				if [ "$$val" = "y" ]; then \
					echo "#define $$key 1"; \
				elif [ "$$val" = "n" ]; then \
					echo "/* #undef $$key */"; \
				else \
					# Handle string values by removing quotes or keeping numeric values as is \
					clean_val=$$(echo "$$val" | sed 's/^"\(.*\)"$$/\1/' | sed 's/\\"/"/g'); \
					echo "#define $$key $$clean_val"; \
				fi; \
			fi; \
		done < $<; \
	} > $@.tmp && mv $@.tmp $@; \
	else \
		echo "/* Auto-generated from .config, do not edit! */" > $@; \
	fi

#-------------------------
# Phony Targets
#-------------------------
.PHONY: default all clean clean-all clean-NV clean-yosys \
        run sim syn sta help \
        check-yosys-sta check-sdc \
		menuconfig defconfig savedefconfig

# Generate config header target
gen-config: $(CONFIG_HEADER)

# 为了能跑 git_commit ,也不要删掉这个！！
include ../Makefile

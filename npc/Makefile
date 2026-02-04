TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

SIM = 0


BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
REPO_DIR = $(BUILD_DIR)/report
BIN = $(BUILD_DIR)/$(TOPNAME)
SIMFILE ?= 


default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""


# rules for yosys
PROJ_PATH = $(shell pwd)
SHELL := /bin/bash

O ?= $(PROJ_PATH)/result
DESIGN ?= $(TOPNAME)
YOSYS_STA_HOME ?= $(HOME)/software/yosys-sta
YOSYS_STA_SCRIPTS ?= $(YOSYS_STA_HOME)/scripts
YOSYS ?= yosys
IEDA ?= $(YOSYS_STA_HOME)/bin/iEDA

SDC_FILE ?= $(YOSYS_STA_SCRIPTS)/default.sdc
RTL_FILES ?= $(shell find $(PROJ_PATH)/vsrc -name "*.v")
CLK_FREQ_MHZ ?= 500
export CLK_FREQ_MHZ
CLK_PORT_NAME ?= clk
export CLK_PORT_NAME
PDK = icsprout55

RESULT_DIR = $(O)/$(DESIGN)-$(CLK_FREQ_MHZ)MHz
NETLIST_SYN_V   = $(RESULT_DIR)/$(DESIGN).netlist.v
TIMING_RPT = $(RESULT_DIR)/$(DESIGN).rpt



$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
ifeq ($(SIM),0)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
else
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		--trace-fst \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
	@echo "sim on, waveform.fst should created"
endif

all: default

run: $(BIN)
	@$^

sim: $(SIMFILE)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	gktwave waveform.*

# yosys

# Example:
#   make -C npc sta \
#     YOSYS_STA_HOME=$(HOME)/Learn/yosys-sta \
#     DESIGN=mydesign SDC_FILE=/path/to/my.sdc \
#     CLK_FREQ_MHZ=100 CLK_PORT_NAME=clk O=/path/to/pwd \
#     RTL_FILES="/path/to/mydesign.v /path/to/xxx.v ..."

check-yosys-sta:
	@test -f "$(YOSYS_STA_SCRIPTS)/yosys.tcl" || (echo "Error: missing $(YOSYS_STA_SCRIPTS)/yosys.tcl. Set YOSYS_STA_HOME=..."; exit 1)
	@test -f "$(YOSYS_STA_SCRIPTS)/sta.tcl" || (echo "Error: missing $(YOSYS_STA_SCRIPTS)/sta.tcl. Set YOSYS_STA_HOME=..."; exit 1)
	@test -x "$(IEDA)" || (echo "Error: missing or non-executable $(IEDA). Set YOSYS_STA_HOME=..."; exit 1)

check-sdc:
	@test -f "$(SDC_FILE)" || (echo "Error: SDC_FILE not found: $(SDC_FILE)"; exit 1)

syn: $(NETLIST_SYN_V)
$(NETLIST_SYN_V): $(RTL_FILES) | check-yosys-sta
	mkdir -p $(@D)
	echo tcl $(YOSYS_STA_SCRIPTS)/yosys.tcl $(DESIGN) $(PDK) \"$(RTL_FILES)\" $@ | $(YOSYS) -g -l $(@D)/yosys.log -s -

sta: $(TIMING_RPT)
$(TIMING_RPT): $(NETLIST_SYN_V) | check-yosys-sta check-sdc
	mkdir -p $(RESULT_DIR)
	set -o pipefail && $(IEDA) -script $(YOSYS_STA_SCRIPTS)/sta.tcl $(SDC_FILE) $(NETLIST_SYN_V) $(DESIGN) $(PDK) 2>&1 | tee $(RESULT_DIR)/sta.log



clean:
	rm -rf $(BUILD_DIR)

clean-yosys:
	rm -rf $(O)

.PHONY: default all clean run syn sta clean-yosys check-yosys-sta check-sdc

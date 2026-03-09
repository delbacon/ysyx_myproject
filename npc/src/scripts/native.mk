#***************************************************************************************
# Copyright (c) 2014-2024 Zihao Yu, Nanjing University
#
# NEMU is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
#
# See the Mulan PSL v2 for more details.
#**************************************************************************************/

-include $(NPC_HOME)/../../Makefile
include $(NPC_HOME)/src/scripts/build.mk

include $(NPC_HOME)/src/tools/difftest.mk
# Some convenient rules

override ARGS += $(ARGS_DIFF)
# override ARGS += --elf-input=build/$(NAME)
# Command to execute NEMU
IMG ?=

# Binary output
BIN = $(IMG).bin


# Simulation Targets
#-------------------------
# Image file for simulation (use relative path)
LOG_FILE = $(BUILD_DIR)/npc-log.txt
ELF_FILE = $(IMG).elf
DIFF_FILE = /home/delbacon/ysyx-workbench/nemu/build/riscv32-nemu-interpreter-so
# Run args
override RUNARGS ?=  --log $(LOG_FILE)
override RUNARGS += --diff $(DIFF_FILE)
override RUNARGS += --elf-input $(ELF_FILE)
override RUNARGS += $(BIN) # RUN

# run 使用无 trace 版本
run: $(BINARY_NO_TRACE)
	@if [ ! -f "$(BIN)" ]; then \
		echo "Error: Image file not found: $(BIN)"; \
		exit 1; \
	fi
	$(BINARY_NO_TRACE) $(RUNARGS)

# sim 使用带 trace 版本，并打开波形
sim: $(BINARY_WITH_TRACE)
	$(call git_commit, "sim RTL")
	@if [ ! -f "$(BIN)" ]; then \
		echo "Error: Image file not found: $(BIN)"; \
		exit 1; \
	fi
	$(BINARY_WITH_TRACE) $(RUNARGS)

	$(GTKWAVE) waveform.* 2>/dev/null || echo "gtkwave not found or no waveform"


clean-tools = $(dir $(shell find ./src/tools -maxdepth 2 -mindepth 2 -name "Makefile"))
$(clean-tools):
	-@$(MAKE) -s -C $@ clean
clean-tools: $(clean-tools)
clean-all: clean distclean clean-tools

.PHONY: run sim clean-tools clean-all $(clean-tools)

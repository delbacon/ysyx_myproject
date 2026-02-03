SRCS = vsrc/*.v
TOP = top
SIM_FILE = csrc/main.cpp
#VCD=1时产生的波形文件为.VCD,注意修改cpp的define
VCD = 0


# verilator --cc --exe --build -j 0 --trace-vcd -Wall sim_main.cpp ./src/top.v
all:
	@echo "Write this Makefile by your self."
ifeq ($(VCD),1)
	echo "VCD enabled..."
	verilator --cc --exe --build -j 0 --trace-vcd -Wall \
	    $(SIM_FILE) $(SRCS)

else
	@echo "normal mode..."
	verilator --cc --exe --build -j 0 --trace-fst -Wall \
	    $(SIM_FILE) $(SRCS)
endif



run: obj_dir/V$(TOP)
	./obj_dir/V$(TOP)


.PHONY: sim
sim: run
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	gtkwave waveform.*

clean:
	rm -rf ./obj_dir waveform.*


include ../Makefile

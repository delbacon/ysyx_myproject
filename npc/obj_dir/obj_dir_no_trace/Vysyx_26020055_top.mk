# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f Vysyx_26020055_top.mk

default: Vysyx_26020055_top

### Constants...
# Perl executable (from $PERL, defaults to 'perl' if not set)
PERL = perl
# Python3 executable (from $PYTHON3, defaults to 'python3' if not set)
PYTHON3 = python3
# Path to Verilator kit (from $VERILATOR_ROOT)
VERILATOR_ROOT = /usr/local/share/verilator
# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?=
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?=

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = Vysyx_26020055_top
# Module prefix (from --prefix)
VM_MODPREFIX = Vysyx_26020055_top
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
  -I/home/delbacon/ysyx-workbench/npc/csrc/include \
  -I/home/delbacon/ysyx-workbench/npc/csrc/include \
  -DTOP_NAME="Vysyx_26020055_top" \
  -Wall \
  -Wextra \
  -MMD \
  -O3 \
  -I/usr/include/SDL2 \
  -D_REENTRANT \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \
  -lreadline \
  -lSDL2 \
  -lSDL2_image \
  -lSDL2_ttf \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
  main \
  inst \
  reg \
  simulator \
  clock \
  device \
  mem_access \
  readbin \
  monitor \
  expr \
  sdb \
  watchpoint \
  ebreak \
  log \
  trace \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
  ../.. \
  ../../csrc \
  ../../csrc/src/cpu \
  ../../csrc/src/device \
  ../../csrc/src/memory \
  ../../csrc/src/monitor \
  ../../csrc/src/sdb \
  ../../csrc/src/utils \

### Default rules...
# Include list of all generated classes
include Vysyx_26020055_top_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

main.o: /home/delbacon/ysyx-workbench/npc/csrc/main.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
inst.o: /home/delbacon/ysyx-workbench/npc/csrc/src/cpu/inst.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
reg.o: /home/delbacon/ysyx-workbench/npc/csrc/src/cpu/reg.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
simulator.o: /home/delbacon/ysyx-workbench/npc/csrc/src/cpu/simulator.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
clock.o: /home/delbacon/ysyx-workbench/npc/csrc/src/device/clock.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
device.o: /home/delbacon/ysyx-workbench/npc/csrc/src/device/device.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
mem_access.o: /home/delbacon/ysyx-workbench/npc/csrc/src/memory/mem_access.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
readbin.o: /home/delbacon/ysyx-workbench/npc/csrc/src/memory/readbin.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
monitor.o: /home/delbacon/ysyx-workbench/npc/csrc/src/monitor/monitor.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
expr.o: /home/delbacon/ysyx-workbench/npc/csrc/src/sdb/expr.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
sdb.o: /home/delbacon/ysyx-workbench/npc/csrc/src/sdb/sdb.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
watchpoint.o: /home/delbacon/ysyx-workbench/npc/csrc/src/sdb/watchpoint.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
ebreak.o: /home/delbacon/ysyx-workbench/npc/csrc/src/utils/ebreak.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
log.o: /home/delbacon/ysyx-workbench/npc/csrc/src/utils/log.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<
trace.o: /home/delbacon/ysyx-workbench/npc/csrc/src/utils/trace.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<

### Link rules... (from --exe)
Vysyx_26020055_top: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@

# Verilated -*- Makefile -*-

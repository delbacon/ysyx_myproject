#include <nvboard.h>
#include <Vtop.h>


#define MAX_TIME 100
#define TOPNAME top

#define CONCAT_V(x) V##x

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* TOPNAME);
/*
static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}
static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}
*/
int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

//  reset(10);
//  int st=0;
  while(1) {
    dut.eval();
//    if(dut.st != 0 && dut.st != st){
//      printf("st:%d  d:%d  data:%x\n",dut.st,dut.ps2_data,dut.data);
//      st = dut.st;
//      }
    nvboard_update();
//    single_cycle();
  }
}

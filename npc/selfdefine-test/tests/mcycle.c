#include "trap.h"


int main() {
	for(int i = 0; i < 100000; i++) {
        asm volatile("csrr a1, mcycleh");
        asm volatile("csrr a0, mcycle");
	}
	return 0;
}

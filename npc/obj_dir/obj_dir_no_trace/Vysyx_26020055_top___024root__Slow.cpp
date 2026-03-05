// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_26020055_top.h for the primary calling header

#include "Vysyx_26020055_top__pch.h"

void Vysyx_26020055_top___024root___ctor_var_reset(Vysyx_26020055_top___024root* vlSelf);

Vysyx_26020055_top___024root::Vysyx_26020055_top___024root(Vysyx_26020055_top__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vysyx_26020055_top___024root___ctor_var_reset(this);
}

void Vysyx_26020055_top___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vysyx_26020055_top___024root::~Vysyx_26020055_top___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}

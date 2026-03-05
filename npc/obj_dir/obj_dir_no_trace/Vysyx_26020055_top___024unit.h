// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_26020055_top.h for the primary calling header

#ifndef VERILATED_VYSYX_26020055_TOP___024UNIT_H_
#define VERILATED_VYSYX_26020055_TOP___024UNIT_H_  // guard

#include "verilated.h"


class Vysyx_26020055_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_26020055_top___024unit final {
  public:

    // INTERNAL VARIABLES
    Vysyx_26020055_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vysyx_26020055_top___024unit() = default;
    ~Vysyx_26020055_top___024unit() = default;
    void ctor(Vysyx_26020055_top__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vysyx_26020055_top___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

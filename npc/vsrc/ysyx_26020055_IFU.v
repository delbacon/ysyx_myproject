import "DPI-C" function int pROM_read(int vraddr) ;

module ysyx_26020055_IFU (
    input  [31:0] pc,
    output [31:0] inst
);
    assign inst = pROM_read(pc);
    
endmodule

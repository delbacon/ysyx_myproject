import "DPI-C" function int pROM_read_HDL(int addr) ;
import "DPI-C" function void inst_get_HDL(int vraddr) ;
import "DPI-C" function void pc_get_HDL(int val) ;
module ysyx_26020055_IFU (
    input clk,
    input  [31:0] pc,
    output [31:0] inst
);
    assign inst = pROM_read_HDL(pc);
    
    always@(posedge clk)begin
        inst_get_HDL(inst);
        pc_get_HDL(pc);
    end

endmodule

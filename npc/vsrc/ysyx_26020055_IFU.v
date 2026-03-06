import "DPI-C" function int pROM_read(int vraddr) ;
import "DPI-C" function void inst_get(int vraddr) ;
import "DPI-C" function void pc_get(int val) ;
module ysyx_26020055_IFU (
    input clk,
    input  [31:0] pc,
    output [31:0] inst
);
    assign inst = pROM_read(pc);
    
    always@(posedge clk)begin
        inst_get(inst);
        pc_get(pc);
    end

endmodule

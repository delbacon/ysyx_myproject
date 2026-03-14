/* verilator lint_off UNDRIVEN */


module ysyx_26020055_pROM #(ADDR_WIDTH = 8, DATA_WIDTH = 32) (
    input [ADDR_WIDTH-1:0] raddr,
    output [DATA_WIDTH-1:0] rdata
);


//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

//读
    assign rdata = rf[raddr];

endmodule


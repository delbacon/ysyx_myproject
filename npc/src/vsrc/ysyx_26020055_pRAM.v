
module ysyx_26020055_pRAM #(ADDR_WIDTH = 8, DATA_WIDTH = 32) (
    input clk,
    input [DATA_WIDTH-1:0] wdata,
    input [ADDR_WIDTH-1:0] addr ,
    input wen,  
    output [DATA_WIDTH-1:0] rdata
);

//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

//写
    always @(posedge clk) begin
        if (wen && addr != 0) begin
            rf[addr] <= wdata;
        end
    end

//读
    assign rdata = rf[addr];

endmodule


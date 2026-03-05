import "DPI-C" function void reg_get(int reg_idx, int val);

module ysyx_26020055_RegisterFile #(ADDR_WIDTH = 5, DATA_WIDTH = 32) (
    input clk,
    input [DATA_WIDTH-1:0] wdata,
    input [ADDR_WIDTH-1:0] waddr,
    input [ADDR_WIDTH-1:0] raddr1,
    input [ADDR_WIDTH-1:0] raddr2,
    input wen,  

    output [DATA_WIDTH-1:0] rdata1,
    output [DATA_WIDTH-1:0] rdata2
);

//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

//写
    always @(posedge clk) begin
        if (wen && waddr != 5'b00000) begin
            rf[waddr] <= wdata;
        end
    end

//读
    assign rdata1 = (raddr1==0)?32'd0 : rf[raddr1];
    assign rdata2 = (raddr2==0)?32'd0 : rf[raddr2];

    always@(posedge clk) begin
        for(int i=0;i<32;i=i+1)begin
            reg_get(i, rf[i]);
        end
    end

endmodule


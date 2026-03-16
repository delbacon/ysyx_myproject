module ysyx_26020055_CSR_RegisterFile #(ADDR_WIDTH = 12, DATA_WIDTH = 32) (
    input clk,
    input rst,
    input [DATA_WIDTH-1:0] wdata,
    input [ADDR_WIDTH-1:0] waddr,
    input [ADDR_WIDTH-1:0] raddr,
    input wen,

    output reg [DATA_WIDTH-1:0] rdata
);

//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

// 地址映射
    localparam  CSR_MCYCLE = 12'hB00,
                CSR_MCYCLEH= 12'hB80,
                CSR_MVENDORID = 12'hF11,
                CSR_MARCHID = 12'hF12,
                CSR_IDLE = 12'h000;

//写
    always @(posedge clk) begin
        if (wen) begin
            case(waddr)
                //只读
                //CSR_MCYCLE: rf[0] <= wdata;
                //CSR_MCYCLEH: rf[1] <= wdata;
                CSR_IDLE: rf[2] <= wdata;
                default: ;
            endcase
        end
    end

//读
    always@(*) begin
    case(raddr)
            CSR_MCYCLE   :rdata = rf[0];
            CSR_MCYCLEH  :rdata = rf[1];
            CSR_MVENDORID:rdata = 32'h79737978;//ysyx
            CSR_MARCHID  :rdata = 32'd26020055;//26020055
            default: rdata = 32'd0;
        endcase
    end



//CSR 功能实现
//csr_mcycle
    always@(posedge clk)begin
        if(rst)begin
            rf[0] <= 32'd0;
        end else begin
            rf[0] <= rf[0] + 1;
        end
    end
//csr_mcycleh
    always@(posedge clk)begin
        if(rst)begin
            rf[1] <= 32'd0;
        end else if(rf[0] == 32'hffff_ffff) begin
            rf[1] <= rf[1] + 1;
        end
    end
//csr_mvendorid
endmodule


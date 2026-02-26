import "DPI-C" function int pmem_read(input int raddr);
import "DPI-C" function void pmem_write(input int waddr, input int wdata, input byte wmask);


module ysyx_26020055_LSU(
    input [31:0] raddr,
    input [31:0] waddr,
    input [31:0] wdata,
    input [3:0] wnum, //写入的字节个数 1 2 4
    input valid,
    input wen,
    output reg [31:0] rdata
);
    reg [7:0] wmask;


    reg [31:0] pmem_rdata;
    always @(*) begin
        if (valid) begin // 有读写请求时
            pmem_rdata = pmem_read(raddr);
            if (wen) begin // 有写请求时
                pmem_write(waddr, wdata, wmask);
            end
        end else begin
            pmem_rdata = 0;
        end
    end

    always@(*)begin
        case(wnum)//wnum[3] = 0 unsigned
            4'b0001 :
                begin   wmask = 8'd1;    rdata = {{24{1'b0}},pmem_rdata[7:0]};    end
            4'b1001 :
                begin   wmask = 8'd1;    rdata = {{24{pmem_rdata[7]}},pmem_rdata[7:0]};    end
            4'b0010 :
                begin   wmask = 8'd2;    rdata = {{16{1'b0}},pmem_rdata[15:0]};    end
            4'b1010 :
                begin   wmask = 8'd2;    rdata = {{16{pmem_rdata[15]}},pmem_rdata[15:0]};    end
            4'b0011 ://4byte
                begin   wmask = 8'd4;    rdata = pmem_rdata;    end
            default :
                begin   wmask = 8'b0;    rdata = 0;    end
        endcase
    end
endmodule

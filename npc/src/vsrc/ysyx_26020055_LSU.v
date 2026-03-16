import "DPI-C" function int pRAM_read_HDL(int addr, int len);
import "DPI-C" function void pRAM_write_HDL(int addr, int len, int data) ;


module ysyx_26020055_LSU(
//    input clk,
    input       [31:0] exu_out  ,//addr 来源
    input       [31:0] src2     ,//wdata 来源
    input       [ 2:0] mem_op   ,
    input              mem_wen  ,
    input              mem_toreg,

    output reg [31:0] mem_rdata 
);
//mem_op
    localparam MEM_OP_SIGNED_BYTE   = 3'b000,
               MEM_OP_SIGNED_HALF   = 3'b001,
               MEM_OP_WORD          = 3'b010,
               MEM_OP_UNSIGNED_BYTE = 3'b100,
               MEM_OP_UNSIGNED_HALF = 3'b101;

//mem_rdata
    reg [31:0] mem_rdata_raw;
    always@(*)begin
        case(mem_op)
            MEM_OP_SIGNED_BYTE:
                mem_rdata = {{24{mem_rdata_raw[7]}}, mem_rdata_raw[7:0]};
            MEM_OP_SIGNED_HALF:
                mem_rdata = {{16{mem_rdata_raw[15]}}, mem_rdata_raw[15:0]};
            MEM_OP_WORD:
                mem_rdata = mem_rdata_raw;
            MEM_OP_UNSIGNED_BYTE:
                mem_rdata = {{24{1'b0}}, mem_rdata_raw[7:0]};
            MEM_OP_UNSIGNED_HALF:
                mem_rdata = {{16{1'b0}}, mem_rdata_raw[15:0]};
            default:
                mem_rdata = mem_rdata_raw;
        endcase   
    end
//mem_len
    reg [31:0] mem_len;
    always@(*)begin
        case(mem_op)
            MEM_OP_SIGNED_BYTE,MEM_OP_UNSIGNED_BYTE:
                mem_len = 32'd1;
            MEM_OP_SIGNED_HALF,MEM_OP_UNSIGNED_HALF:
                mem_len = 32'd2;
            MEM_OP_WORD:
                mem_len = 32'd4;
            default:
                mem_len = 32'd0;
        endcase   
    end


    wire [31:0] mem_wdata;
    assign mem_wdata = src2;
/* verilator lint_off UNUSEDSIGNAL */
    wire [31:0] mem_addr;
    assign mem_addr = (mem_wen || mem_toreg) ? exu_out : 32'h8000_0000; 




    always@(*)begin
        begin 
            if(mem_wen)begin
                mem_rdata_raw = 32'h0;
                pRAM_write_HDL(mem_addr, mem_len, mem_wdata);
            end else begin
                mem_rdata_raw = pRAM_read_HDL(mem_addr, mem_len);
            end
        end
    end

/*
reg [31:0] wdata;
always@(*)begin
    case(mem_len)
        1:begin
            wdata = {24'b0,mem_wdata[7:0]};
        end
        2:begin
            wdata = {16'b0,mem_wdata[15:0]};
        end
        4:begin
            wdata = mem_wdata;
        end
        default:begin
            wdata = 32'h0;
        end
    endcase
end
*/
/*
ysyx_26020055_pRAM u_ysyx_26020055_pRAM(
    .clk    (clk     ),
    .wdata  (wdata   ),
    .addr   (mem_addr[7:0]),
    .wen    (mem_wen     ),  
    .rdata  (mem_rdata_raw)
);
*/


endmodule

import "DPI-C" function int pROM_read_HDL(int addr) ;
import "DPI-C" function void inst_get_HDL(int vraddr) ;
import "DPI-C" function void pc_get_HDL(int val) ;
import "DPI-C" function void dnpc_get_HDL(int val) ;
module ysyx_26020055_IFU (
    input            clk          ,
    input            rst          ,
    output reg[31:0] pc           ,
    input            branch_flag  ,
    input     [31:0] branch_target,
    output    [31:0] inst         ,
    output reg       ifu_valid    ,
    input            wbu_ready        
);
// 从仿真环境中读取 ROM ，获得执行的指令
    localparam PC_INIT = 32'h8000_0000;

// 三段式状态机
localparam IDLE=0,WAIT=1;
reg st,n_st;
always@(posedge clk)begin
    if(rst)
        st <= IDLE;
    else
        st <= n_st;
end
always@(*)begin
    case(st)
        IDLE:begin n_st = WAIT; end
        WAIT:begin n_st = IDLE; end
        default:begin n_st = IDLE; end
    endcase
end

reg [31:0] ifu_data,ifu_addr;

always@(posedge clk)begin
    if(st == WAIT)
        inst <= ifu_data;
end
always@(posedge clk)begin
    if(st == IDLE)
        ifu_addr <= pc;
end


always @(posedge clk) begin
    if (rst) begin
        inst <= pROM_read_HDL(PC_INIT);
        ifu_valid <= 1'b0;
    end else if(st == WAIT)begin
        ifu_data <= pROM_read_HDL(ifu_addr);
        ifu_valid <= 1'b1;
    end else
        ifu_valid <= 1'b0;
    inst_get_HDL(inst);
end
/*
reg [7:0] pc_read;
always@(posedge clk)begin
        if(rst)
            pc_read <= PC_INIT[7:0];
        else
            pc_read <= next_pc[7:0];//确保与 pc 同步,如果写pc,会超前读1个指令
end
ysyx_26020055_pROM u_ysyx_26020055_pROM(
    .raddr  (pc_read  ),
    .rdata  (inst     )
);
*/

//更新pc
//如果跳转的话，更新pc为branch_target
    wire [31:0] next_pc ;
    assign next_pc = branch_flag ? branch_target : pc + 4; 
    


always @(posedge clk) begin
    if (rst) begin
        pc <= PC_INIT;
    end else if(wbu_ready && st == IDLE)begin
        pc <= next_pc; // 正常更新
    end
end

// DPI-C 向仿真环境传输数据
    always@(posedge clk)begin
        if(rst)begin
            pc_get_HDL(PC_INIT);
            dnpc_get_HDL(PC_INIT + 4);
        end else begin
            dnpc_get_HDL(next_pc);
            pc_get_HDL(pc);
        end
    end
endmodule

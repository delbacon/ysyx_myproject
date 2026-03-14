//import "DPI-C" function int pROM_read_HDL(int addr) ;
import "DPI-C" function void inst_get_HDL(int vraddr) ;
import "DPI-C" function void pc_get_HDL(int val) ;
import "DPI-C" function void dnpc_get_HDL(int val) ;
module ysyx_26020055_IFU (
    input            clk          ,
    input            rst          ,
    output reg[31:0] pc           ,
    input            branch_flag  ,
    input     [31:0] branch_target,
    output    [31:0] inst
);
// 从仿真环境中读取 ROM ，获得执行的指令
    localparam PC_INIT = 32'h8000_0000;
/*
    always@(posedge clk)begin
        if(rst)
            inst <= pROM_read_HDL(PC_INIT);
        else
            inst <= pROM_read_HDL(next_pc);//确保与 pc 同步,如果写pc,会超前读1个指令
            inst_get_HDL(inst);
    end
*/
reg [7:0] pc_read;
always@(posedge clk)begin
        if(rst)
            pc_read <= PC_INIT[7:0];
        else
            pc_read <= next_pc[7:0];//确保与 pc 同步,如果写pc,会超前读1个指令
end
ysyx_26020055_pROM u_ysyx_26020055_pROM(
    .raddr  (pc_read[7:0]  ),
    .rdata  (inst     )
);


//更新pc
//如果跳转的话，更新pc为branch_target
    wire [31:0] next_pc ;
    assign next_pc = branch_flag ? branch_target : pc + 4; 
    
    // pc_reg（在时钟上升沿更新）
    always @(posedge clk) begin
        if(rst)
            pc <= PC_INIT;
        else
            pc <= next_pc;
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

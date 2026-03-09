//npc/vsrc/ysyx_26020055_WBU.v
import "DPI-C" function void dnpc_get_HDL(int val) ;
module ysyx_26020055_WBU (
    input clk,
    input rst,
    input  [4:0]  rs1,
    input  [4:0]  rs2,
    input  [4:0]  rd,
    input  [31:0] wr_data,
    input wen,

    input jmp_taken,              //jmp跳转
    input [31:0]pc_jmp_target,    //jmp目标地址

    output [31:0] rs1_data,
    output [31:0] rs2_data,

    output reg [31:0] pc
);

//更新pc
//如果跳转的话，更新pc为pc_jmp_target
    wire [31:0] next_pc = jmp_taken ? pc_jmp_target : pc + 4; 
    
    // pc_reg（在时钟上升沿更新）
    always @(posedge clk) begin
        if(rst)
            pc <= 32'h8000_0000;
        else
            pc <= next_pc;
    end

    // 将 next_pc 同步到 C 中
    always@(posedge clk) begin
        dnpc_get_HDL(next_pc);
    end
//寄存器堆
ysyx_26020055_RegisterFile u_RegisterFile (
    .clk(clk),
    .wdata(wr_data),
    .waddr(rd),
    .raddr1(rs1),
    .raddr2(rs2),
    .rdata1(rs1_data),
    .rdata2(rs2_data),
    .wen(wen)
);

    
endmodule




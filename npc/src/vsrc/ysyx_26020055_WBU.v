//npc/vsrc/ysyx_26020055_WBU.v
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




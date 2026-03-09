`define MAX_OP 6

import "DPI-C" function void ebreak ();

/* verilator lint_off UNUSEDSIGNAL */

module ysyx_26020055_EXU (
    input [31:0] rs1_data,
    input [31:0] rs2_data,
    input [31:0] imm,
    input [`MAX_OP-1:0]  exu_op,
    input [3:0] jmp_op,
    input [3:0] uncal_op,
    input [3:0] sys_op,
    input [31:0] pc,
    input [31:0] rdata,
    input mem_on,

    output reg jmp_taken,
    output reg [31:0] pc_jmp_target,
    output [31:0] reg_wr_data,
    output reg [31:0] mem_rd_addr,
    output reg [31:0] mem_wr_addr
);
//exu_op拆解
    wire [3:0] alu_op;  // alu_op
    wire  exu_src;      // src2选择
    assign exu_src = exu_op[5];
//   assign exu_addr = exu_op[4];
    assign alu_op = exu_op[3:0];


//源数据
    wire [31:0] src1;
    wire [31:0] src2;

    assign src1 = rs1_data;
    assign src2 = exu_src ? imm : rs2_data;//源选择 exu_src


//ALU
    wire alu_zero,alu_cout,alu_overflow;
    wire [31:0] alu_out;
    ysyx_26020055_ALU alu (
        .a(src1),
        .b(src2),
        .op(alu_op),
        .y(alu_out),
        .zero(alu_zero),
        .cout(alu_cout),
        .overflow(alu_overflow)
    );

//jmp语句解析
    reg [31:0] rd_jmp_data;
    always@(*)begin
        case(jmp_op)
            4'd2:   //jalr
                begin   jmp_taken = 1; rd_jmp_data = pc + 4; pc_jmp_target = (src1 + imm) & ~1;  end
            default:
                begin   jmp_taken = 1'd0; rd_jmp_data = 32'd0; pc_jmp_target = 32'd0;    end
        endcase
    end

//uncal语句解析
    reg uncal_flag;
    reg [31:0] uncal_data;
    always @(*) begin
        case(uncal_op)
            4'b1:
                begin   uncal_flag = 1; uncal_data = imm; end //ecall
			default: 
                begin   uncal_flag = 0; uncal_data = 0; end
        endcase
    end

//sys语句解析
    always @(*) begin
        case(sys_op)
            4'd2:
                begin	ebreak();	end //ebreak
			default: ;
        endcase
    end

//out
    //data
    assign reg_wr_data = (jmp_taken == 1)? 
                            rd_jmp_data :
                        (uncal_flag == 1)? 
                            uncal_data :
                        (mem_on == 1) ?
                            rdata :
                            alu_out;    
    assign mem_wr_addr = alu_out;
    assign mem_rd_addr = alu_out;
endmodule

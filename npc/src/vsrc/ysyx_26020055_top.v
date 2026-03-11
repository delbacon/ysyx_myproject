
module ysyx_26020055_top (
    input         clk,
    input         rst
);
	wire [31:0] pc;
	wire [31:0] inst;

//branch
	wire branch_flag;
	wire [31:0] branch_target;
ysyx_26020055_IFU u_ysyx_26020055_IFU (
    .clk            (clk          ),
    .rst            (rst          ),
    .pc             (pc           ),
    .branch_flag    (branch_flag  ),
    .branch_target  (branch_target),
    .inst           (inst         )    
);

    wire [4:0] rs1,rs2,rd;

	wire [31:0] imm;

	wire [3:0] alu_op;
	wire [1:0] alu_base;
	wire 	   alu_asrc;

	wire       reg_wen;
	wire [2:0] mem_op;
	wire       mem_wen;
	wire       mem_toreg;

	wire [2:0] branch_op;
ysyx_26020055_IDU u_ysyx_26020055_IDU (
    .inst     	(inst     ), 
    .rs1        (rs1      ),
    .rs2        (rs2      ),
    .rd         (rd       ), 
	.imm        (imm      ),
    .alu_op   	(alu_op   ),//ALU工作模式
    .alu_base 	(alu_base ),//ALU输入类型
    .alu_asrc 	(alu_asrc ),//ALU输入a的来源

    .reg_wen  	(reg_wen  ),//reg写使能

    .mem_op   	(mem_op   ),//mem工作模式(byte/half/word)
    .mem_wen  	(mem_wen  ),//mem写使能
    .mem_toreg	(mem_toreg),//mem读结果写入到reg

    .branch_op	(branch_op)
);

wire [31:0] src1,src2;
wire [31:0] reg_wdata;
wire [31:0] mem_addr;
wire [31:0] alu_out;
assign reg_wdata = alu_out;
assign mem_addr = alu_out;
ysyx_26020055_EXU u_ysyx_26020055_EXU(
    .pc           (pc           ),

    .imm          (imm          ),

    .src1         (src1         ),
    .src2         (src2         ),

    .alu_op       (alu_op       ),
    .alu_base     (alu_base     ),
    .alu_asrc     (alu_asrc     ),

    .branch_op    (branch_op    ),
    .branch_flag  (branch_flag  ),
    .branch_target(branch_target),

    .alu_out      (alu_out      ) 
);



endmodule

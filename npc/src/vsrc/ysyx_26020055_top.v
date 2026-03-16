
module ysyx_26020055_top (
    input         clk,
    input         rst
);
	wire [31:0] pc;
	wire [31:0] inst;

//branch
	wire branch_flag;
	wire [31:0] branch_target;
    wire ifu_valid;
ysyx_26020055_IFU u_ysyx_26020055_IFU (
    .clk            (clk          ),
    .rst            (rst          ),
    .pc             (pc           ),
    .branch_flag    (branch_flag  ),
    .branch_target  (branch_target),
    .inst           (inst         ),
    .ifu_valid      (ifu_valid    ),
    .wbu_ready      (wbu_ready    )
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

    wire [2:0] csr_op;
    wire idu_valid;
    wire [31:0] pc_in;
    wire exu_ready;
ysyx_26020055_IDU u_ysyx_26020055_IDU (
    .clk        (clk       ),
    .rst        (rst       ),  
    .inst     	(inst     ), 
    .pc         (pc        ),
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

    .csr_wen     (csr_wen ),
    .csr_op      (csr_op  ),

    .branch_op	(branch_op),
    .ifu_valid  (ifu_valid),
    .idu_valid  (idu_valid),
    .exu_ready  (exu_ready),
    .pc_in      (pc_in    )
);



wire [31:0] src1,src2;
wire [31:0] exu_out;
wire csr_wen ;
wire exu_valid;

ysyx_26020055_EXU u_ysyx_26020055_EXU(
    .clk          (clk          ),
    .rst          (rst          ),
    .pc_in        (pc_in        ),

    .imm          (imm          ),

    .src1         (src1         ),
    .src2         (src2         ),

    .alu_op       (alu_op       ),
    .alu_base     (alu_base     ),
    .alu_asrc     (alu_asrc     ),

    .branch_op    (branch_op    ),
    .branch_flag  (branch_flag  ),
    .branch_target(branch_target),

    .csr_wen      (csr_wen      ),
    .csr_op       (csr_op       ),

    .exu_out      (exu_out      ),
    .idu_valid    (idu_valid    ),
    .exu_valid    (exu_valid    ),
    .exu_ready    (exu_ready    )
);

wire [31:0] mem_rdata;
ysyx_26020055_LSU u_ysyx_26020055_LSU(
 //   .clk          (clk          ),
    .exu_out      (exu_out      ),//addr 来源
    .src2         (src2         ),//wdata 来源
    .mem_op       (mem_op       ),
    .mem_wen      (mem_wen      ),
    .mem_toreg    (mem_toreg    ),
    .mem_rdata    (mem_rdata    ) 
);

wire wbu_ready;
ysyx_26020055_WBU u_ysyx_26020055_WBU (
    .clk          (clk          ),
    .rs1          (rs1          ),
    .rs2          (rs2          ),
    .rd           (rd           ),
     
    .exu_out      (exu_out      ),
    .mem_rdata    (mem_rdata    ),
    .reg_wen      (reg_wen      ),
    .mem_toreg    (mem_toreg    ),
 
    .src1         (src1         ),
    .src2         (src2         ),
    .exu_valid    (exu_valid    ),
    .wbu_ready    (wbu_ready   )
);

endmodule



module ysyx_26020055_top (
    input         clk,
    input         rst,
    output        ifu_valid,
    output        wbu_ready
);
	wire [31:0] pc;
	wire [31:0] inst;

//branch
	wire branch_flag;
	wire [31:0] branch_target;
//mem
wire [31:0]ch0_arAddr ;wire ch0_arValid    ;wire ch0_arReady;
wire [31:0]ch0_rData  ;wire [1:0]ch0_rResp ;wire ch0_rValid ;wire ch0_rReady ;
wire [31:0]ch0_awAddr ;wire ch0_awValid    ;wire ch0_awReady;
wire [31:0]ch0_wStrb  ;wire [31:0]ch0_wData;wire ch0_wValid ;wire ch0_wReady    ;
wire [1:0]ch0_bResp   ;wire ch0_bValid     ;wire ch0_bReady ;
ysyx_26020055_IFU u_ysyx_26020055_IFU (
    .clk            (clk          ),
    .rst            (rst          ),
    .pc             (pc           ),
    .branch_flag    (branch_flag  ),
    .branch_target  (branch_target),
    .inst           (inst         ),
    .ifu_valid      (ifu_valid    ),
    .wbu_ready      (wbu_ready    ),
/* AXI4-lite ports */
    .ifu_arAddr     (ch0_arAddr   ),
    .ifu_arValid    (ch0_arValid  ),
    .ifu_arReady    (ch0_arReady  ),
  
    .ifu_rData      (ch0_rData    ),
    .ifu_rResp      (ch0_rResp    ),
    .ifu_rValid     (ch0_rValid   ),
    .ifu_rReady     (ch0_rReady   ),
  
    .ifu_awAddr     (ch0_awAddr   ),
    .ifu_awValid    (ch0_awValid  ),
    .ifu_awReady    (ch0_awReady  ),
  
    .ifu_wStrb      (ch0_wStrb    ),
    .ifu_wData      (ch0_wData    ),
    .ifu_wValid     (ch0_wValid   ),
    .ifu_wReady     (ch0_wReady   ),
  
    .ifu_bResp      (ch0_bResp    ),
    .ifu_bValid     (ch0_bValid   ),
    .ifu_bReady     (ch0_bReady   )
);

assign ch0_awAddr  = 'd0;
assign ch0_awValid = 'd0;
assign ch0_wStrb   = 'd0;
assign ch0_wData   = 'd0;
assign ch0_wValid  = 'd0;
assign ch0_bReady  = 'd0;




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
wire lsu_valid;

wire [31:0]ch1_arAddr ;wire ch1_arValid    ;wire ch1_arReady;
wire [31:0]ch1_rData  ;wire [1:0]ch1_rResp ;wire ch1_rValid ;wire ch1_rReady ;
wire [31:0]ch1_awAddr ;wire ch1_awValid    ;wire ch1_awReady;
wire [31:0]ch1_wStrb  ;wire [31:0]ch1_wData;wire ch1_wValid ;wire ch1_wReady    ;
wire [1:0]ch1_bResp   ;wire ch1_bValid     ;wire ch1_bReady ;
ysyx_26020055_LSU u_ysyx_26020055_LSU(
    .clk          (clk          ),
    .rst          (rst          ),
    .exu_out      (exu_out      ),//addr 来源
    .src2         (src2         ),//wdata 来源
    .mem_op       (mem_op       ),
    .mem_wen      (mem_wen      ),
    .mem_toreg    (mem_toreg    ),
    .mem_rdata    (mem_rdata    ),
    .exu_valid    (exu_valid    ),
    .wbu_ready    (wbu_ready    ),
    .lsu_valid    (lsu_valid    ),
/* AXI4-lite ports */
    .lsu_arAddr   (ch1_arAddr   ),
    .lsu_arValid  (ch1_arValid  ),
    .lsu_arReady  (ch1_arReady  ),

    .lsu_rData    (ch1_rData    ),
    .lsu_rResp    (ch1_rResp    ),
    .lsu_rValid   (ch1_rValid   ),
    .lsu_rReady   (ch1_rReady   ),

    .lsu_awAddr   (ch1_awAddr   ),
    .lsu_awValid  (ch1_awValid  ),
    .lsu_awReady  (ch1_awReady  ),

    .lsu_wStrb    (ch1_wStrb    ),
    .lsu_wData    (ch1_wData    ),
    .lsu_wValid   (ch1_wValid   ),
    .lsu_wReady   (ch1_wReady   ),

    .lsu_bResp    (ch1_bResp    ),
    .lsu_bValid   (ch1_bValid   ),
    .lsu_bReady   (ch1_bReady   )
);

ysyx_26020055_mem_arbiter u_ysyx_26020055_mem_arbiter (

    .clk            (clk        ),
    .rst            (rst        ),

/* AXI4-lite for CH0*/
    /* 读地址操作 */
    .ch0_arAddr     (ch0_arAddr ),
    .ch0_arValid    (ch0_arValid),
    .ch0_arReady    (ch0_arReady),
    /* 读数据操作 */
    .ch0_rData      (ch0_rData  ),
    .ch0_rResp      (ch0_rResp  ),
    .ch0_rValid     (ch0_rValid ),
    .ch0_rReady     (ch0_rReady ),
    /* 写地址操作 */
    .ch0_awAddr     (ch0_awAddr ),
    .ch0_awValid    (ch0_awValid),
    .ch0_awReady    (ch0_awReady),
    /* 写数据操作 */
    .ch0_wStrb      (ch0_wStrb  ),  
    .ch0_wData      (ch0_wData  ),
    .ch0_wValid     (ch0_wValid ),
    .ch0_wReady     (ch0_wReady ),
    /* 写回操作 */
    .ch0_bResp      (ch0_bResp  ),
    .ch0_bValid     (ch0_bValid ),
    .ch0_bReady     (ch0_bReady ),

/* AXI4-lite for CH1*/
    /* 读地址操作 */
    .ch1_arAddr     (ch1_arAddr ),
    .ch1_arValid    (ch1_arValid),
    .ch1_arReady    (ch1_arReady),
    /* 读数据操作 */
    .ch1_rData      (ch1_rData  ),
    .ch1_rResp      (ch1_rResp  ),
    .ch1_rValid     (ch1_rValid ),
    .ch1_rReady     (ch1_rReady ),
    /* 写地址操作 */
    .ch1_awAddr     (ch1_awAddr ),
    .ch1_awValid    (ch1_awValid),
    .ch1_awReady    (ch1_awReady),
    /* 写数据操作 */
    .ch1_wStrb      (ch1_wStrb  ),  
    .ch1_wData      (ch1_wData  ),
    .ch1_wValid     (ch1_wValid ),
    .ch1_wReady     (ch1_wReady ),
    /* 写回操作 */
    .ch1_bResp      (ch1_bResp  ),
    .ch1_bValid     (ch1_bValid ),
    .ch1_bReady     (ch1_bReady )
);


ysyx_26020055_WBU u_ysyx_26020055_WBU (
    .clk          (clk          ),
    .rst          (rst          ),
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
    .wbu_ready    (wbu_ready    ),
    .lsu_valid    (lsu_valid    )
);

endmodule


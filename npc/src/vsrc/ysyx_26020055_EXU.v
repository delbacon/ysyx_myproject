/* verilator lint_off UNUSEDSIGNAL */

module ysyx_26020055_EXU (
    input           clk           ,
    input           rst           ,
    input      [31:0]pc           ,
    //imm_data    
    input      [31:0]imm          ,
    //reg_data    
    input      [31:0]src1         ,
    input      [31:0]src2         ,
    //alu_ctrl    
    input      [3:0] alu_op       ,//ALU工作模式
    input      [1:0] alu_base     ,//ALU输入类型
    input            alu_asrc     ,//ALU输入a的来源
    //branch_ctrl
    input      [2:0] branch_op    ,//分支工作模式
    output reg       branch_flag  ,//是否跳转
    output reg [31:0]branch_target,//跳转地址
    //csr
    input            csr_wen      ,
    input      [ 2:0]csr_op       ,
    //out
    output     [31:0]exu_out        
);

// csr 特殊处理
//======================================================//
    reg  [31:0] csr_wdata;
    wire [31:0] csr_rdata,ex_csr_rdata;
    wire [31:0] csr_out;
    ysyx_26020055_CSR_RegisterFile u_ysyx_26020055_CSR_RegisterFile (
        .clk        (clk        ),
        .rst        (rst        ),
        .wdata      (csr_wdata  ),
        .waddr      (imm[11:0]  ),
        .raddr      (imm[11:0]  ),
        .wen        (csr_wen    ),  

        .rdata      (csr_rdata  )
    );
    //ex_csr 存的是实现 ecall 的几个需要同时交互的寄存器
ysyx_26020055_ExceptionCtrl u_ysyx_26020055_ExceptionCtrl(
    .clk         (clk    ),
    .rst         (rst    ),
    .pc          ( pc    ),
    .imm         (imm[11:0]),
    .csr_wen     (csr_wen),
    .csr_op      (csr_op ),
    .ex_csr_wdata (csr_wdata ),
    .ex_csr_rdata (ex_csr_rdata )
);


    //csr_op
    localparam  CSR_OP_CSRRW = 3'b000,
                CSR_OP_CSRRS = 3'b001,
                CSR_OP_ECALL = 3'b110,
                CSR_OP_MRET = 3'b111;
localparam      CSR_MSTATUS = 12'h300,
                CSR_MTVEC   = 12'h305,
                CSR_MEPC    = 12'h341,
                CSR_MCAUSE  = 12'h342;
    wire csr_ex_en ;
    assign csr_ex_en = (imm[11:0] == CSR_MSTATUS || imm[11:0] == CSR_MTVEC || imm[11:0] == CSR_MEPC || imm[11:0] == CSR_MCAUSE) ? 1 : 0;
    always@(*)begin
        case(csr_op)
            CSR_OP_CSRRW: begin
                csr_wdata = src1;
            end
            CSR_OP_CSRRS: begin
                csr_wdata = src1 | csr_out;
            end
            default: begin
                csr_wdata = csr_out;
            end
        endcase
    end

    assign csr_out = csr_ex_en?ex_csr_rdata : csr_rdata ;



//alu
//======================================================//
    wire [31:0] alu_out;
    reg [31:0] a,b;
//alu_asrc
    wire [31:0] a_reg;
    assign a_reg = alu_asrc ? pc : src1;

//alu_base
    localparam  ALU_BASE_REG_REG = 2'b00,
                ALU_BASE_REG_IMM = 2'b01,
                ALU_BASE_PC_4    = 2'b10,
                ALU_BASE_REG_MEM = 2'b11;
    always@(*)begin
        case(alu_base)
            ALU_BASE_REG_REG:begin
                a = a_reg;
                b = src2;
            end
            ALU_BASE_REG_IMM:begin
                a = a_reg;
                b = imm;
            end
            ALU_BASE_PC_4:begin
                a = a_reg;
                b = 32'd4;
            end
            ALU_BASE_REG_MEM:begin
                a = a_reg;
                b = imm;
            end
            default:begin
                a = 32'd0;
                b = 32'd0;
            end
        endcase
    end
    wire zero,less;
ysyx_26020055_ALU u_ysyx_26020055_ALU (
    .a          (a      ),
    .b          (b      ),
    .alu_op     (alu_op ),
    .alu_out    (alu_out),
    .zero       (zero   ),
    .less       (less   ) 
);
//======================================================//


//branch_op
//======================================================//
    localparam  BRANCH_OP_IDLE         = 3'b000,
                BRANCH_OP_JAL          = 3'b001,
                BRANCH_OP_JALR         = 3'b010,
                BRANCH_OP_BEQ          = 3'b100,
                BRANCH_OP_BNE          = 3'b101,
                BRANCH_OP_BLT_AND_BLTU = 3'b110,
                BRANCH_OP_BGE_AND_BGEU = 3'b111;

//branch_flag
    always@(*)begin
        case(branch_op)
            BRANCH_OP_IDLE         :    branch_flag = 0;
            BRANCH_OP_JAL          :    branch_flag = 1;
            BRANCH_OP_JALR         :    branch_flag = 1;
            BRANCH_OP_BEQ          :    branch_flag =  zero;//相等的时候跳转
            BRANCH_OP_BNE          :    branch_flag = ~zero;//不相等的时候跳转
            BRANCH_OP_BLT_AND_BLTU :    branch_flag =  less;//小于的时候跳转
            BRANCH_OP_BGE_AND_BGEU :    branch_flag =  (~less || zero);//大于等于的时候跳转
            default:    branch_flag = 0;
        endcase
    end

//branch_target
    always@(*)begin
        if(csr_op == CSR_OP_ECALL || csr_op == CSR_OP_MRET) begin
            branch_target = ex_csr_rdata;
        end else begin
            case(branch_op)
                BRANCH_OP_JAL: begin
                    branch_target = pc + imm;
                end
                BRANCH_OP_JALR: begin
                    branch_target = ( src1 + imm ) & 32'hFFFF_FFFE;
                end
                BRANCH_OP_BEQ,BRANCH_OP_BNE,BRANCH_OP_BLT_AND_BLTU,BRANCH_OP_BGE_AND_BGEU: begin
                    branch_target = pc + imm;
                end
                default: begin
                    branch_target = 32'd0;
                end
            endcase
        end
    end
        
//======================================================//

    assign exu_out = (csr_wen == 1 || csr_op != 0) ? csr_out : alu_out;

endmodule

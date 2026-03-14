// npc/vsrc/ysyx_26020055_IDU.v
// IDU 负责译码
import "DPI-C" function void ebreak ();

module ysyx_26020055_IDU (
    input [31:0] inst,
    //addr
    output reg [4:0] rs1      ,
    output reg [4:0] rs2      ,
    output reg [4:0] rd       ,
    //imm
    output reg [31:0]imm      ,
    //ALU
    output reg [3:0] alu_op   ,//ALU工作模式
    output reg [1:0] alu_base ,//ALU输入类型
    output           alu_asrc ,//ALU输入a的来源
    //reg
    output reg       reg_wen  ,//reg写使能
    //mem
    output reg [2:0] mem_op   ,//mem工作模式(byte/half/word)
    output           mem_wen  ,//mem写使能
    output           mem_toreg,//mem读结果写入到reg
    //csr
    output           csr_wen  ,
    output reg [2:0] csr_op   ,
    //branch
    output reg [2:0] branch_op
);


// ALU 状态获取
//====================================================//
    localparam  ALU_ADD=4'b0000, 
                ALU_SUB=4'b1000, 
                ALU_LEFTSHIFT0=4'b0001 ,   
                ALU_SIGNED_LESS=4'b0010 ,
                ALU_UNSIGNED_LESS=4'b1010,
                ALU_OUTPUT_B0=4'b0011,     
                ALU_XOR0=4'b0100,            
                ALU_LOGIC_RIGHTSHIFT=4'b0101, 
                ALU_ARTH_RIGHTSHIFT=4'b1101,
                ALU_OR0=4'b0110,
                ALU_AND0=4'b0111;

//==================== baisc inst I ==============================//

    localparam  OP_LOAD   = 7'b0000011, 
                OP_STORE  = 7'b0100011, 
                OP_BRANCH = 7'b1100011,
                OP_IMM    = 7'b0010011,
                OP_NOIMM  = 7'b0110011,
                OP_JAL    = 7'b1101111,
                OP_JALR   = 7'b1100111,
                OP_LUI    = 7'b0110111,
                OP_AUIPC  = 7'b0010111;


// OP_JALR:
    localparam  IMM_FUNCT3_JALR  = 3'b000;

// OP_IMM:
    localparam  IMM_FUNCT3_ADDI  = 3'b000,
                IMM_FUNCT3_SLTI  = 3'b010,
                IMM_FUNCT3_SLTIU = 3'b011,
                IMM_FUNCT3_XORI  = 3'b100,
                IMM_FUNCT3_ORI   = 3'b110,
                IMM_FUNCT3_ANDI  = 3'b111,
                IMM_FUNCT3_SLLI  = 3'b001,
                IMM_FUNCT3_SRLI_OR_SRAI  = 3'b101;

                localparam  IMM_FUNCT7_SLLI = 7'b0000000,
                            IMM_FUNCT7_SRLI = 7'b0000000,
                            IMM_FUNCT7_SRAI = 7'b0100000;
//OP_NOIMM:
    localparam  NOIMM_FUNCT3_ADD_OR_SUB = 3'b000,
                NOIMM_FUNCT3_SLL = 3'b001,
                NOIMM_FUNCT3_SLT = 3'b010,
                NOIMM_FUNCT3_SLTU= 3'b011,
                NOIMM_FUNCT3_XOR = 3'b100,
                NOIMM_FUNCT3_SRL_OR_SRA = 3'b101,
                NOIMM_FUNCT3_OR  = 3'b110,
                NOIMM_FUNCT3_AND = 3'b111;

                localparam  IMM_FUNCT7_ADD = 7'b0000000,
                            IMM_FUNCT7_SUB = 7'b0100000,
                            IMM_FUNCT7_SLL = 7'b0000000,
                            IMM_FUNCT7_SLT = 7'b0000000,
                            IMM_FUNCT7_SLTU= 7'b0000000,
                            IMM_FUNCT7_XOR = 7'b0000000,
                            IMM_FUNCT7_SRL = 7'b0000000,
                            IMM_FUNCT7_SRA = 7'b0100000,
                            IMM_FUNCT7_OR  = 7'b0000000,
                            IMM_FUNCT7_AND = 7'b0000000;

//OP_BRANCH:
    localparam  BRANCH_FUNCT3_BEQ = 3'b000,
                BRANCH_FUNCT3_BNE = 3'b001,
                BRANCH_FUNCT3_BLT = 3'b100,
                BRANCH_FUNCT3_BGE = 3'b101,
                BRANCH_FUNCT3_BLTU= 3'b110,
                BRANCH_FUNCT3_BGEU= 3'b111;
//OP_LOAD:
    localparam  LOAD_FUNCT3_LB  = 3'b000,
                LOAD_FUNCT3_LH  = 3'b001,
                LOAD_FUNCT3_LW  = 3'b010,   
                LOAD_FUNCT3_LBU = 3'b100,
                LOAD_FUNCT3_LHU = 3'b101;
//OP_STORE:
    localparam  STORE_FUNCT3_SB = 3'b000,
                STORE_FUNCT3_SH = 3'b001,
                STORE_FUNCT3_SW = 3'b010;
//==================== inst for Zicsr ==============================//
    localparam  OP_CSR = 7'b1110011;
    localparam  CSR_FUNCT3_CSRRW = 3'b001;
    localparam  CSR_FUNCT3_CSRRS = 3'b010;




// 操作数和寄存器地址获取
    wire [6:0] opcode;
    wire [2:0] funct3;
    wire [6:0] funct7;

    assign  opcode = inst[6:0];
    assign  rs1    = inst[19:15];
    assign  rs2    = inst[24:20];
    assign  rd     = inst[11:7];
    assign  funct3 = inst[14:12];
    assign  funct7 = inst[31:25];


// 解析指令
//==================================================================================================//
// 立即数获取
//====================================================//
    wire [31:0] immI, immU, immS, immB, immJ;
    assign immI = {{20{inst[31]}}, inst[31:20]};
    assign immU = {inst[31:12], 12'b0};
    assign immS = {{20{inst[31]}}, inst[31:25], inst[11:7]};
    assign immB = {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0};
    assign immJ = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};

    always @(*) begin
        case (opcode)
            OP_LOAD  : imm = immI;   // LOAD
            OP_STORE : imm = immS;   // STORE
            OP_BRANCH: imm = immB;   // BRANCH
            OP_IMM   : imm = immI;   // OP-IMM
            OP_NOIMM : imm = 32'b0; // OP (no imm)
            OP_JAL   : imm = immJ;   // JAL
            OP_JALR  : imm = immI;   // JALR
            OP_LUI   : imm = immU;   // LUI
            OP_AUIPC : imm = immU;   // AUIPC
            OP_CSR   : imm = immI;
            default:   imm = 32'b0;
        endcase
    end




    always@(*)begin
        case(opcode)
            OP_LUI  : alu_op = ALU_OUTPUT_B0;
            OP_AUIPC: alu_op = ALU_ADD;

            OP_IMM  : begin
                case(funct3)
                    IMM_FUNCT3_ADDI  : alu_op = ALU_ADD;
                    IMM_FUNCT3_SLTI  : alu_op = ALU_SIGNED_LESS;
                    IMM_FUNCT3_SLTIU : alu_op = ALU_UNSIGNED_LESS;
                    IMM_FUNCT3_XORI  : alu_op = ALU_XOR0;
                    IMM_FUNCT3_ORI   : alu_op = ALU_OR0;
                    IMM_FUNCT3_ANDI  : alu_op = ALU_AND0;
                    IMM_FUNCT3_SLLI  :  begin
                                            if(funct7 == IMM_FUNCT7_SLLI) alu_op = ALU_LEFTSHIFT0;
                                            else alu_op = 4'b0000;
                                        end
                    IMM_FUNCT3_SRLI_OR_SRAI  : begin
                                            if     (funct7 == IMM_FUNCT7_SRAI) alu_op = ALU_ARTH_RIGHTSHIFT;
                                            else if(funct7 == IMM_FUNCT7_SRLI) alu_op = ALU_LOGIC_RIGHTSHIFT;
                                            else alu_op = 4'b0000;
                                        end
                    default    : alu_op = 4'b0000; 
                endcase
            end

            OP_NOIMM: begin
                case(funct3)
                    NOIMM_FUNCT3_ADD_OR_SUB : begin
                                                if     (funct7 == IMM_FUNCT7_ADD) alu_op = ALU_ADD;
                                                else if(funct7 == IMM_FUNCT7_SUB) alu_op = ALU_SUB;
                                                else alu_op = 4'b0000;
                                            end
                    NOIMM_FUNCT3_SLL : begin
                                        if(funct7 == IMM_FUNCT7_SLL) alu_op = ALU_LEFTSHIFT0;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_SLT : begin
                                        if(funct7 == IMM_FUNCT7_SLT) alu_op = ALU_SIGNED_LESS;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_SLTU: begin
                                        if(funct7 == IMM_FUNCT7_SLTU) alu_op = ALU_UNSIGNED_LESS;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_XOR : begin 
                                        if(funct7 == IMM_FUNCT7_XOR) alu_op = ALU_XOR0;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_SRL_OR_SRA : begin
                                        if(funct7 == IMM_FUNCT7_SRL) alu_op = ALU_LOGIC_RIGHTSHIFT;
                                        else if(funct7 == IMM_FUNCT7_SRA) alu_op = ALU_ARTH_RIGHTSHIFT;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_OR  : begin 
                                        if(funct7 == IMM_FUNCT7_OR) alu_op = ALU_OR0;
                                        else alu_op = 4'b0000;
                                    end
                    NOIMM_FUNCT3_AND : begin
                                        if(funct7 == IMM_FUNCT7_AND) alu_op = ALU_AND0;
                                        else alu_op = 4'b0000;
                                    end
                    default: alu_op = 4'b0000;
                endcase
            end

            OP_JAL  : alu_op = ALU_ADD;
            OP_JALR : begin 
                        if(funct3 == IMM_FUNCT3_JALR) alu_op = ALU_ADD;
                        else alu_op = 4'b0000;
                    end

            OP_BRANCH : begin
                case(funct3)
                    BRANCH_FUNCT3_BEQ : alu_op = ALU_SUB;
                    BRANCH_FUNCT3_BNE : alu_op = ALU_SUB;
                    BRANCH_FUNCT3_BLT : alu_op = ALU_SIGNED_LESS;
                    BRANCH_FUNCT3_BGE : alu_op = ALU_SIGNED_LESS;
                    BRANCH_FUNCT3_BLTU: alu_op = ALU_UNSIGNED_LESS;
                    BRANCH_FUNCT3_BGEU: alu_op = ALU_UNSIGNED_LESS;
                    default: alu_op = 4'b0000;
                endcase
            end

            OP_LOAD, OP_STORE: alu_op = ALU_ADD;
            OP_CSR:            alu_op = ALU_OUTPUT_B0;
            
        default: alu_op = 4'b0000;
        endcase
    end

//alu_base
    localparam  ALU_BASE_REG_REG = 2'b00,
                ALU_BASE_REG_IMM = 2'b01,
                ALU_BASE_PC_4    = 2'b10;
                //ALU_BASE_REG_MEM = 2'b11;

    always@(*)begin
        case(opcode)
            OP_LUI,OP_AUIPC : alu_base = ALU_BASE_REG_IMM;
            OP_IMM          : alu_base = ALU_BASE_REG_IMM;
            OP_NOIMM        : alu_base = ALU_BASE_REG_REG;   
            OP_JAL          : alu_base = ALU_BASE_PC_4;
            OP_JALR         : begin 
                                if(funct3 == IMM_FUNCT3_JALR) alu_base = ALU_BASE_PC_4;
                                else alu_base = ALU_BASE_REG_IMM; 
                            end
            OP_BRANCH       : alu_base = ALU_BASE_REG_REG;
            OP_LOAD,OP_STORE: alu_base = ALU_BASE_REG_IMM;
            OP_CSR          : alu_base = ALU_BASE_REG_IMM;
            default: alu_base = 2'b00;
        endcase
    end

//alu_asrc
    assign alu_asrc = (opcode == OP_AUIPC || opcode == OP_JAL || opcode == OP_JALR) ? 1 : 0;

//====================================================//

// reg 写入控制
//====================================================//
//reg_wen
    always@(*)begin
        case(opcode)
            OP_LUI   : reg_wen = 1;
            OP_AUIPC : reg_wen = 1;
            OP_IMM   : reg_wen = 1;
            OP_NOIMM : reg_wen = 1;
            OP_JAL   : reg_wen = 1;
            OP_JALR  : begin 
                        if(funct3 == IMM_FUNCT3_JALR) reg_wen = 1;
                        else reg_wen = 0;
                    end
            OP_BRANCH: reg_wen = 0;
            OP_LOAD  : reg_wen = 1;
            OP_STORE : reg_wen = 0;
            OP_CSR   : reg_wen = 1;
            default   : reg_wen = 0;
        endcase
    end


//mem
//====================================================//
//mem_op
    localparam MEM_OP_SIGNED_BYTE   = 3'b000,
               MEM_OP_SIGNED_HALF   = 3'b001,
               MEM_OP_WORD          = 3'b010,
               MEM_OP_UNSIGNED_BYTE = 3'b100,
               MEM_OP_UNSIGNED_HALF = 3'b101;

    always@(*)begin
        case(opcode)
            OP_LUI   : mem_op = 3'b000;
            OP_AUIPC : mem_op = 3'b000;
            OP_IMM   : mem_op = 3'b000;
            OP_NOIMM : mem_op = 3'b000;
            OP_JAL   : mem_op = 3'b000;
            OP_JALR  : mem_op = 3'b000;
            OP_BRANCH: mem_op = 3'b000;
            OP_LOAD  : begin
                case(funct3)
                    LOAD_FUNCT3_LB : mem_op = MEM_OP_SIGNED_BYTE;
                    LOAD_FUNCT3_LH : mem_op = MEM_OP_SIGNED_HALF;
                    LOAD_FUNCT3_LW : mem_op = MEM_OP_WORD;
                    LOAD_FUNCT3_LBU: mem_op = MEM_OP_UNSIGNED_BYTE;
                    LOAD_FUNCT3_LHU: mem_op = MEM_OP_UNSIGNED_HALF;
                    default: mem_op = 3'b000;
                endcase
            end
            OP_STORE : begin
                case(funct3)
                    STORE_FUNCT3_SB : mem_op = MEM_OP_SIGNED_BYTE;
                    STORE_FUNCT3_SH : mem_op = MEM_OP_SIGNED_HALF;
                    STORE_FUNCT3_SW : mem_op = MEM_OP_WORD;
                    default: mem_op = 3'b000;
                endcase
            end
            OP_CSR   : mem_op = 3'b000;
            default   : mem_op = 3'b000;
        endcase
    end

// mem_wen
    assign mem_wen = (opcode == OP_STORE)?1 : 0;

//mem_toreg
    assign mem_toreg = (opcode == OP_LOAD)?1 : 0;
//====================================================//


//branch
//====================================================//
//branch_op
    localparam  BRANCH_OP_IDLE         = 3'b000,
                BRANCH_OP_JAL          = 3'b001,
                BRANCH_OP_JALR         = 3'b010,
                BRANCH_OP_BEQ          = 3'b100,
                BRANCH_OP_BNE          = 3'b101,
                BRANCH_OP_BLT_AND_BLTU = 3'b110,
                BRANCH_OP_BGE_AND_BGEU = 3'b111;



     always@(*)begin
        case(opcode)
            OP_LUI   : branch_op = BRANCH_OP_IDLE;
            OP_AUIPC : branch_op = BRANCH_OP_IDLE;
            OP_IMM   : branch_op = BRANCH_OP_IDLE;
            OP_NOIMM : branch_op = BRANCH_OP_IDLE;
            OP_JAL   : branch_op = BRANCH_OP_JAL;
            OP_JALR  : branch_op = BRANCH_OP_JALR;
            OP_BRANCH: begin
                case(funct3)
                    BRANCH_FUNCT3_BEQ : branch_op = BRANCH_OP_BEQ;
                    BRANCH_FUNCT3_BNE : branch_op = BRANCH_OP_BNE;
                    BRANCH_FUNCT3_BLT : branch_op = BRANCH_OP_BLT_AND_BLTU;
                    BRANCH_FUNCT3_BGE : branch_op = BRANCH_OP_BGE_AND_BGEU;
                    BRANCH_FUNCT3_BLTU: branch_op = BRANCH_OP_BLT_AND_BLTU;
                    BRANCH_FUNCT3_BGEU: branch_op = BRANCH_OP_BGE_AND_BGEU;
                    default: branch_op = BRANCH_OP_IDLE;
                endcase
            end
            OP_LOAD   : branch_op = BRANCH_OP_IDLE;
            OP_STORE  : branch_op = BRANCH_OP_IDLE;
            OP_CSR    : begin
                if(inst == INST_MRET || inst == INST_ECALL)
                    branch_op = BRANCH_OP_JAL;
                else
                    branch_op = BRANCH_OP_IDLE;
            end
            default   : branch_op = BRANCH_OP_IDLE;
        endcase
    end




//====================================================//




//====================================================//
//系统指令的特别判断
    localparam INST_EBREAK = 32'b000000000001_00000_000_00000_1110011;
    localparam INST_ECALL  = 32'b000000000000_00000_000_00000_1110011;
    localparam INST_MRET   = 32'b001100000010_00000_000_00000_1110011;

//ebreak
    always@(*)begin
        if(inst == INST_EBREAK) begin
            ebreak();
        end 
    end

//csr_wen
    assign csr_wen = ((opcode == OP_CSR && (funct3 == CSR_FUNCT3_CSRRW)) || inst == INST_ECALL)?1 : 0;
//csr_op
    localparam  CSR_OP_CSRRW = 3'b000,
                CSR_OP_CSRRS = 3'b001,
                CSR_OP_ECALL = 3'b110,
                CSR_OP_MRET  = 3'b111;


    always@(*)begin
        if(opcode == OP_CSR)begin
            if(inst == INST_ECALL) begin
                csr_op = CSR_OP_ECALL;
            end else if(inst == INST_MRET) begin
                csr_op = CSR_OP_MRET;
            end else begin
                case(funct3)
                    CSR_FUNCT3_CSRRW : csr_op = CSR_OP_CSRRW;
                    CSR_FUNCT3_CSRRS : csr_op = CSR_OP_CSRRS;
                    default: csr_op = 3'b000;
                endcase
            end
        end else begin
            csr_op = 3'b000;
        end
    end
//====================================================//
endmodule



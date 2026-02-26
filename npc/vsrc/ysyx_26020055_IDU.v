// npc/vsrc/ysyx_26020055_IDU.v
// IDU 负责译码

//RV32I Base Instruction
//用于判断opcode是否属于这类指令
//==========================================================================================//
`define R(opcode) (opcode == 7'b0110011)
`define I(opcode) (opcode == 7'b1100111 || opcode == 7'b0000011 || opcode == 7'b0010011 )
`define S(opcode) (opcode == 7'b0100011)
`define B(opcode) (opcode == 7'b1100011)
`define U(opcode) (opcode == 7'b0110111 || opcode == 7'b0010111 )
`define J(opcode) (opcode == 7'b1101111)
//==========================================================================================//

//提取指令的标志{func7,func3,opcode},用于判断是否是这一条指令
//特别地，对于sys指令，为整个inst
//==============17'b============================================================================//
`define LUI     17'b???????_???_0110111					//f
`define AUIPC   17'b???????_???_0010111
`define JAL     17'b???????_???_1101111
`define JALR    17'b???????_000_1100111					//f
`define BEQ     17'b???????_???_1100011
`define BNE     17'b???????_???_1100111
`define BLT     17'b???????_???_1100111
`define BGE     17'b???????_???_1100111
`define BLTU    17'b???????_???_1100111
`define BGEU    17'b???????_???_1100111
`define LB      17'b???????_000_0000011
`define LH      17'b???????_001_0000011
`define LW      17'b???????_010_0000011                  //f
`define LBU     17'b???????_100_0000011					 //f
`define LHU     17'b???????_101_0000011
`define SB      17'b???????_000_0100011					 //f	
`define SH      17'b???????_001_0100011
`define SW      17'b???????_010_0100011					 //f
`define ADDI    17'b???????_000_0010011                  //f
`define SLTI    17'b???????_???_0010011
`define SLTIU   17'b???????_???_0010011
`define XORI    17'b???????_???_0010011
`define ORI     17'b???????_???_0010011
`define ANDI    17'b???????_???_0010011
`define SLLI    17'b???????_???_0010011
`define SRLI    17'b???????_???_0010011
`define SRAI    17'b???????_???_0010011
`define ADD     17'b0000000_000_0110011					//f
`define SUB     17'b???????_???_0110011
`define SLL     17'b???????_???_0110011
`define SLT     17'b???????_???_0110011
`define SLTU    17'b???????_???_0110011
`define XOR     17'b???????_???_0110011
`define SRL     17'b???????_???_0110011
`define SRA     17'b???????_???_0110011
`define OR      17'b???????_???_0110011
`define AND     17'b???????_???_0110011
`define EBREAK  32'b000000000001_00000_000_00000_1110011 //f
//==========================================================================================//




module ysyx_26020055_IDU (
//    input         clk,
//    input         reset,
    input [31:0]  inst,

    output [4:0]  rs1,
    output [4:0]  rs2,
    output [4:0]  rd,
    output [31:0] imm,

    output        reg_wr,
    output        mem_rd,
    output        mem_wr,
    output reg [5:0]  exu_op,//需要alu计算的inst
    output reg [3:0]  jmp_op,//涉及跳转的inst（包括需要计算的）
	output reg [3:0]  mem_op,//读写内存byte数
	output reg [3:0]  uncal_op,//不用计算的inst
    output reg [3:0]  sys_op//系统级指令
);
// 指令译码
    wire [6:0] opcode;
    wire [2:0] funct3;
    wire [6:0] funct7;

    assign opcode = inst[6:0];
    assign funct3 = inst[14:12];
    assign funct7 = inst[31:25];

//reg
    assign rs1 = inst[19:15];
    assign rs2 = inst[24:20];
    assign rd  = inst[11:7];

//imm
    // 默认为 0,R-type不涉及imm,所以不考虑
    assign imm = 
        /* I-type */
        `I(opcode) ? 
            {{20{inst[31]}}, inst[31:20]} :
        /* S-type */
        `S(opcode) ?
            {{20{inst[31]}}, inst[31:25], inst[11:7]} :
        /* B-type */
        `B(opcode) ?   
            {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0} : // BEQ/BNE/...
        /* U-type */
        `U(opcode) ? 
            {inst[31], inst[30:12], 12'b0} : 
        /* J-type */
        `J(opcode) ? 
            {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0} : 

            32'b0; // 默认

//signal
    assign reg_wr = 
        `R(opcode) || `I(opcode) || `U(opcode) || `J(opcode) ?
            1'b1 :

            1'b0; // 默认
  
    //注意不是所有I-type指令都需要mem_rd
    assign mem_rd = 
        (opcode == 7'b0000011) ?
            1'b1 :

            1'b0;

    assign mem_wr = 
        `S(opcode) ?
            1'b1 :

            1'b0;


/*
    exu_op操作码（工作模式），具体如下
      0:+,  1:-,
      2:<,  3:>,  4:==,
      5:<u, 6:>u,
      7:^,  8: |, 9:&,
      10:<<,11:>>,           逻辑左右移
      12:>>>                算术右移 

    jmp_op:
        0:IDLE
        1:jal   2:jalr

	mem_op:
		0:IDLE
		1:1byte
		2:2byte
		3:4byte

	uncal_op:
		0:IDLE
		1:lui

    sys_op:
        0:IDLE
        1:ecall
        2:ebreak
*/
//exu_op,自定义的一个用于exu的opcode
//最高位置为1表示src2为imm
    //jmp_op & exu_op
    always@(*)begin
        casez({funct7,funct3,opcode})
        //jalr
            `JALR:
                begin jmp_op = 4'd2;exu_op=6'd0;  end //jalr
        //op=0 add
            `ADD: 
                begin jmp_op = 4'd0; exu_op =   6'd0;   end //out = src1 + src2
            `ADDI,`LW,`SW,`LBU,`SB: 
                begin jmp_op = 4'd0; exu_op = 6'b100000;   end //out = src1 + imm
        //op=1 sub
            17'b0000000_000_0000100: 
                begin jmp_op = 4'd0; exu_op =   6'd1;  ; end //out = src1 - src2
            17'b0000000_000_0000101: 
                begin jmp_op = 4'd0; exu_op = 6'b100001;   end //out = src1 - imm
        //op=2 <
            17'b0000000_000_0000000: 
                begin jmp_op = 4'd0; exu_op =   6'd2;   end //out = src1 < src2
            17'b0000000_000_0000001: 
                begin jmp_op = 4'd0; exu_op = 6'b100010;   end //out = src1 < imm
        //op=3 >
            17'b0000000_000_0000100: 
                begin jmp_op = 4'd0; exu_op =   6'd3;   end //out = src1 > src2
            17'b0000000_000_0000101: 
                begin jmp_op = 4'd0; exu_op = 6'b100011;   end //out = src1 > imm

        //op=5 <u
            17'b0000000_000_0000110: 
                begin jmp_op = 4'd0; exu_op =   6'd5;   end //out = src1 <u src2
            17'b0000000_000_0000111: 
                begin jmp_op = 4'd0; exu_op = 6'b100101;   end //out = src1 <u imm
        //op=6 >u
            17'b0000000_000_0000000: 
                begin jmp_op = 4'd0; exu_op =   6'd6;   end //out = src1 >u src2
            17'b0000000_000_0000001: 
                begin jmp_op = 4'd0; exu_op = 6'b100110;   end //out = src1 >u imm
        //op=7 ^
            17'b0000000_000_0000100: 
                begin jmp_op = 4'd0; exu_op =   6'd7;   end //out = src1 ^ src2
            17'b0000000_000_0000101: 
                begin jmp_op = 4'd0; exu_op = 6'b100111;   end //out = src1 ^ imm
        //op=8 |
            17'b0000000_000_0000000: 
                begin jmp_op = 4'd0; exu_op =   6'd8;   end //out = src1 | src2
            17'b0000000_000_0000001: 
                begin jmp_op = 4'd0; exu_op = 6'b101000;   end //out = src1 | imm
        //op=9 &
            17'b0000000_000_0000100: 
                begin jmp_op = 4'd0; exu_op =   6'd9;   end //out = src1 & src2
            17'b0000000_000_0000101: 
                begin jmp_op = 4'd0; exu_op = 6'b101001;   end //out = src1 & imm
        //op=10 <<
            17'b0000000_000_0001000: 
                begin jmp_op = 4'd0; exu_op =   6'd10;  end //out = src1 << src2
            17'b0000000_000_0001001: 
                begin jmp_op = 4'd0; exu_op = 6'b101010;   end //out = src1 << imm
        //op=11 >>
            17'b0000000_000_0001100:
                begin jmp_op = 4'd0; exu_op =   6'd11;  end //out = src1 >> src2
            17'b0000000_000_0001101: 
                begin jmp_op = 4'd0; exu_op = 6'b101011;   end //out = src1 >> imm
        //op=12 >>>
            17'b0000000_000_0001110: 
                begin jmp_op = 4'd0; exu_op =   6'd12;  end //out = src1 >>> src2
            17'b0000000_000_0001111: 
                begin jmp_op = 4'd0; exu_op = 6'b101100;   end //out = src1 >>> imm

        default: begin jmp_op = 4'd0; exu_op =   6'd0;   end
        endcase
    end

	//uncal_op
	always@(*)begin 
		casez({funct7,funct3,opcode})
			`LUI: uncal_op = 4'b1;//lui rd = imm
			default: uncal_op = 4'b0;
		endcase
	end

	//mem_op
	always@(*)begin 
		casez({funct7,funct3,opcode})
			`LBU   : mem_op = 4'b0001;//1byte_u
			`LB,`SB: mem_op = 4'b1001;//1byte
			`LHU   : mem_op = 4'b0010;//2byte_u
			`LH,`SH: mem_op = 4'b1010;//2byte
			`LW,`SW: mem_op = 4'b0011;//4byte
			default: mem_op = 4'd0;
		endcase
	end

	//sys_op
    always@(*)begin 
        case(inst)
            
            `EBREAK: sys_op = 4'd2;

            default: sys_op = 4'd0;
        endcase
    end

endmodule

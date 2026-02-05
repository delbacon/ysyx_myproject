module sCPU(
    input clk,
    input rst,
    output [7:0] out
);
    wire [7:0] rom[11:0];//ram
    //rom_init
    assign rom[ 0] = 8'b10001010;
    assign rom[ 1] = 8'b10010000;
    assign rom[ 2] = 8'b10100000;
    assign rom[ 3] = 8'b10110001;
    assign rom[ 4] = 8'b00010111;
    assign rom[ 5] = 8'b00101001;
    assign rom[ 6] = 8'b11010001;
    assign rom[ 7] = 8'b01100000;
    assign rom[ 8] = 8'b11111000;
    assign rom[ 9] = 8'h00;//8'b
    assign rom[10] = 8'h00;
    assign rom[11] = 8'h00;
/*
                    10001010    # 0: li r0, 10
                    10010000    # 1: li r1, 0
                    10100000    # 2: li r2, 0
                    10110001    # 3: li r3, 1
                    00010111    # 4: add r1, r1, r3
                    00101001    # 5: add r2, r2, r1
                    11010001    # 6: bner0 r1, 4
                    11011111    # 7: bner0 r3, 7
*/
    localparam ADD = 2'b00,OUT = 2'b01,LI = 2'b10,BNER0 = 2'b11;

    wire [3:0] pc;
    wire [7:0] GPR[3:0];//寄存器
//    assign GPR[0] = 4'b0000;//zero=0

    wire [7:0]inst;
    assign inst = rom[pc];


    wire we;
    assign we = 1;
//一个时钟周期执行一条指令
//--------------------------------//
    wire [3:0] next_pc;
    assign next_pc = ((inst[7:6] == LI) && (GPR[0] != GPR[rs2])) ? 
                        addr : (pc + 1'b1);

    Reg #(4, 4'b0) pcreg (clk,rst,next_pc,pc,1'b1);
//--------------------------------//


//指令解析
//--------------------------------//

    wire [13:0]result;
    wire [7:0] wdata;
    MuxKeyWithDefault #(4, 2, 14) func0 (result, inst[7:6], 14'b0, {
        //  case (inst)
        ADD, /*y =*/{inst[5:0],8'b0},
        OUT, /*y =*/{2'b0,inst[5:4],10'b0},
        LI, /*y =*/{inst[5:4],4'b0,inst[3:0],4'b0},
        BNER0, /*y =*/{4'b0,inst[1:0],4'b0,inst[5:2]}
        //default: y = 1'b0;
    });

    //rd2bit,rs12bit,rs22bit,imm4bit,addr4bit;
    wire [1:0] rd, rs1, rs2;
    wire [3:0] imm, addr;

    assign rd = result[13:12];
    assign rs1 = result[11:10];
    assign rs2 = result[9:8];
    assign imm = result[7:4];
    assign addr = result[3:0];



//--------------------------------//


//write_GPR
//--------------------------------//

    MuxKeyWithDefault #(4, 2, 8) wdata0 (wdata, inst[7:6], 8'b0, {
        //  case (inst)
        ADD, /*y =*/{GPR[rs1]+GPR[rs2]},
        LI, /*y =*/ {4'b0,imm},
        OUT, /*y =*/8'b0,
        BNER0, /*y =*/8'b0
        //default: y = 1'b0;
    });

    genvar i;
    for (i = 0; i < 4; i = i + 1) begin:inst_write_GPR
        Reg #(8,8'b0) gpr0 (clk, rst, wdata,     GPR[i], we && (rd==i));
    end
//--------------------------------//

//out
//--------------------------------//

    Reg #(8,0) instout (clk, rst, GPR[rs1], out, we && (inst[7:6]==OUT));

//--------------------------------//

endmodule
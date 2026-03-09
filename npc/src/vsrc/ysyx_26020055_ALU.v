`define ALU_MAX_LEN 32
`define ALU_MAX_OP 4
/* verilator lint_off UNUSEDSIGNAL */
//============================================//
/* ALU 模块
>>>>FUNCTION:
      ALU模块，根据输入的op选择模式，并输出a,b的运算结果
      默认为 32bit

>>>>DEFINE:
        ALU_MAX_LEN 最长操作数长度
        ALU_MAX_OP  最长操作码长度

>>>>INPUT:
        a, b    操作数1 和 操作数2
        op      操作码（工作模式），具体如下
                      0:+,  1:-,
                      2:<,  3:>,  4:==,
                      5:<u, 6:>u,
                      7:^,  8: |, 9:&,
                      10:<<,11:>>,           逻辑左右移
                      12:>>>                算术右移 

>>>>OUTPUT:
        y       运算结果
        zero    结果是否为0
        cout    运算结果的进位
        overflow运算结果是否溢出

>>>>INCLUDE_EXAMPALE:
    ysyx_26020055_ALU u_ALU (
        .a(a),
        .b(b),
        .op(op),
        .y(y),
        .zero(zero),
        .cout(cout),
        .overflow(overflow)
    );

>>>>PS:
    移位运算时，可以直接输入 imm 到 a, 该 alu 会自动取 a 的低 5bit 作为移位数

 */
//============================================//
module ysyx_26020055_ALU (
    input  [`ALU_MAX_LEN-1:0] a, b,
    input  [`ALU_MAX_OP -1:0]  op,   // 0:+, 1:-, 2:<, 3:^, 4:\|, 5:&, 6:<<, 7:>>, 8:>>>
    output reg [`ALU_MAX_LEN-1:0] y,
    output        zero,
    output        cout,
    output        overflow
);
    reg [`ALU_MAX_LEN:0] res;

    //因为riscv中位移数shamt只有5位，这里只取a的最低5位
    wire [`ALU_MAX_LEN-1:0] shl = b << a[4:0];
    wire [`ALU_MAX_LEN-1:0] shr = b >> a[4:0];           // 逻辑右移
    wire [`ALU_MAX_LEN-1:0] sar = $signed(b) >>> a[4:0]; // 算术右移

/*
      0:+,  1:-,
      2:<,  3:>,  4:==,
      5:<u, 6:>u,
      7:^,  8: |, 9:&,
      10:<<,11:>>,           逻辑左右移
      12:>>>                算术右移 
*/
    always @(*) begin
        case (op)
            'd0: res = a + b;                     // ADD
            'd1: res = a - b;                     // SUB
            'd2: y   = ($signed(a) < $signed(b)) ? 'd1 : 'd0; // SLT
            'd3: y   = ($signed(a) > $signed(b)) ? 'd1 : 'd0;
            'd4: y   = (a == b) ? 'd1 : 'd0;            
            'd5: y   = ($unsigned(a) < $unsigned(b)) ? 'd1 : 'd0; // SLTU
            'd6: y   = ($unsigned(a) > $unsigned(b)) ? 'd1 : 'd0;
            'd7: y   = a ^ b;                     // XOR
            'd8: y   = a | b;                     // OR
            'd9: y   = a & b;                     // AND
            'd10:y   = shl;                       // SLL
            'd11:y   = shr;                       // SRL
            'd12:y   = sar;                       // SRA
            default: begin y = 32'd0; res = 'd0; end
        endcase
    end

    assign zero = (y == 'd0);
    assign cout = res[`ALU_MAX_LEN];
    assign overflow = (a[`ALU_MAX_LEN-1] == b[`ALU_MAX_LEN-1]) && (a[`ALU_MAX_LEN-1] != y[`ALU_MAX_LEN-1]);
    assign y = res[31:0];
endmodule

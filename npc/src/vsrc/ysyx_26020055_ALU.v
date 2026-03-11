`define ALU_MAX_LEN 32
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
module ysyx_26020055_ALU #(parameter ALU_MAX_BIT = 32)(
    input [ALU_MAX_BIT-1:0] a      ,
    input [ALU_MAX_BIT-1:0] b      ,
    input [3:0]             alu_op ,
    output[ALU_MAX_BIT-1:0]   alu_out,
    output                  zero   ,
    output                  less
);
    localparam  ALU_ADD=4'b0000, 
                ALU_SUB=4'b1000, 
                ALU_LEFTSHIFT0=4'b0001 ,     ALU_LEFTSHIFT1=4'b1001 ,
                ALU_SIGNED_LESS=4'b0010 ,
                ALU_UNSIGNED_LESS=4'b1010,
                ALU_OUTPUT_B0=4'b0011,       ALU_OUTPUT_B1=4'b1011,
                ALU_XOR0=4'b0100,            ALU_XOR1=4'b1100,
                ALU_LOGIC_RIGHTSHIFT=4'b0101, 
                ALU_ARTH_RIGHTSHIFT=4'b1101,
                ALU_OR0=4'b0110,       ALU_OR1=4'b1110,
                ALU_AND0=4'b0111,      ALU_AND1=4'b1111 ;

    wire sign_a,sign_b,sign_out,overflow;
    assign sign_a = a[ALU_MAX_BIT-1];
    assign sign_b = b[ALU_MAX_BIT-1];
    assign sign_out = alu_out[ALU_MAX_BIT-1];
    assign overflow = (sign_a == sign_b) && (sign_out == ~sign_a);//符号位不同且结果符号位与输入a符号位不同时为溢出

    reg [ALU_MAX_BIT-1:0] y;
    always@(*)begin
        case(alu_op)
            ALU_ADD:                           y = a + b;                                      
            ALU_SUB:                           y = a - b;                        
            ALU_LEFTSHIFT0,    ALU_LEFTSHIFT1: y = a << b;                       
            ALU_SIGNED_LESS:                   y = ($signed(a) - $signed(b));  
            ALU_UNSIGNED_LESS:                 y = (a - b);                         //默认无符号
            ALU_OUTPUT_B0,     ALU_OUTPUT_B1:  y = b;                                             
            ALU_XOR0,          ALU_XOR1:       y = a ^ b;                       
            ALU_LOGIC_RIGHTSHIFT:              y = a >> b;                     
            ALU_ARTH_RIGHTSHIFT:               y = $signed(a) >>> b;           
            ALU_OR0,     ALU_OR1:              y = a | b;                                            
            ALU_AND0,    ALU_AND1:             y = a & b;                     
            default: y = 0;
        endcase
        
    end

    assign zero = (alu_out == 0);
    assign less = sign_out ^ overflow;
    // 因为比大小要输出较小的值，并且需要减法计算结果，所以单独做了判断
    assign alu_out = (alu_op == ALU_SIGNED_LESS || alu_op == ALU_UNSIGNED_LESS) ?
                        ((less==1'b1)? 
                            a : b) : y;
endmodule

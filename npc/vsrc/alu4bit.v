module alu4bit(
    input [2:0] mode,
    input [3:0] a,
    input [3:0] b,

    output [3:0] out,
    output zero,
    output cout,
    output overflow
);
  // 通过MuxKey实现如下always代码
  // always @(*) begin
  //  case (s)
  //    1'b0: y = a;
  //    1'b1: y = b;
  //  endcase
  // end
    wire [4:0]result;
    wire [4:0]A,B;
    assign A = {1'b0,a};
    assign B = {1'b0,b};
    MuxKey #(8, 3, 5) i0 (result, mode, {
        //case(mode)
        3'b000, /*result = */(A+B),//A+B
        3'b001, /*result = */($signed(A)-$signed(B)),//A-B,输入已经是补码了
        3'b010, /*result = */{1'b0,~a},   //~A 
        3'b011, /*result = */{1'b0,(a&b)},//a&b
        3'b100, /*result = */{1'b0,(a|b)},
        3'b101, /*result = */{1'b0,(a^b)},
        3'b110, /*result = */({4'b0,$signed(a)<$signed(b)}),
        3'b111, /*result = */{4'b0,(&(~(a^b)))}//A==B(同或)
    });

    assign out = result[3:0];
    assign cout = result[4];
    assign overflow = (a[3] == b[3]) && (a[3] != result[3]);
    assign zero = ~(| out );

endmodule



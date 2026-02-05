module adder4bit(
    input cin,
    input [3:0]a,
    input [3:0]b,
    output [3:0]out,
    output cout,
    output overflow
);
    wire [3:0]t_no_cin;
    assign t_no_cin = {4{cin}}^b;//cin?~b:b
    assign {cout,out} = a + t_no_cin + {3'b0,cin};
    assign overflow = (a[3] == t_no_cin[3]) && (out[3] != a[3]);

endmodule
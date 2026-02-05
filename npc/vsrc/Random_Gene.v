module Random_Gene (
    input clk,
    input rst,
    output [7:0]out
);
    wire in;
    assign in = out[4] ^ out[3] ^ out[2] ^ out[0];
    

    Reg #(1, 1'b0) i7 (clk, rst, (in)    , out[7], 1'b1);//M-->L
    Reg #(1, 1'b0) i6 (clk, rst, (out[7]), out[6], 1'b1);//M-->L
    Reg #(1, 1'b0) i5 (clk, rst, (out[6]), out[5], 1'b1);//M-->L
    Reg #(1, 1'b0) i4 (clk, rst, (out[5]), out[4], 1'b1);//M-->L
    Reg #(1, 1'b0) i3 (clk, rst, (out[4]), out[3], 1'b1);//M-->L
    Reg #(1, 1'b0) i2 (clk, rst, (out[3]), out[2], 1'b1);//M-->L
    Reg #(1, 1'b0) i1 (clk, rst, (out[2]), out[1], 1'b1);//M-->L
    Reg #(1, 1'b1) i0 (clk, rst, (out[1]), out[0], 1'b1);//M-->L

/*
    D_Reg4bit D_Reg4bit0(
        .clk    (clk),
        .rst    (rst),
        .in     (in ),
        .out    (out[7:4])
    );
    D_Reg4bit D_Reg4bit1(
        .clk    (clk),
        .rst    (rst),
        .in     (out[4]),
        .out    (out[3:0])
    );
*/
endmodule



module D_Reg4bit(
    input clk,
    input rst,
    input in,
    output[3:0]out
);
    genvar i;
    generate
        for(i=3;i>0;i--)begin:inst
            Reg #(1, 1'b0) i0 (clk, rst, (i==3?in:out[i]), out[i-1], 1'b1);//M-->L
        end
    endgenerate
endmodule
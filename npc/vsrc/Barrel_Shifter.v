module Barrel_Shifter (
    input [7:0]din,
    input [2:0]shamt,
    input L_R,
    input A_L,
    output [7:0]dout
);
    wire [7:0]mid_num[1:0];
    wire sign;
    assign sign = A_L?din[7]:0;

    genvar j;
    generate
        for(j=0;j<8;j++)begin:inst2
            MuxKeyWithDefault #(4, 2, 1) i1 (mid_num[0][j], {L_R,shamt[0]}, 1'b0, {
                //  case (s)
                2'b00, /*y =*/din[j],
                2'b01, /*y =*/j==7?sign:din[j+1],//右移1
                2'b10, /*y =*/din[j],
                2'b11, /*y =*/j==0?1'b0:din[j-1]//左移1
                //default: y = 1'b0;
            });
            MuxKeyWithDefault #(4, 2, 1) i2 (mid_num[1][j], {L_R,shamt[1]}, 1'b0, {
                //  case (s)
                2'b00, /*y =*/mid_num[0][j],
                2'b01, /*y =*/(j==7||j==6)?sign:mid_num[0][j+1],//右移1
                2'b10, /*y =*/mid_num[0][j],
                2'b11, /*y =*/(j==0||j==1)?1'b0:mid_num[0][j-1]//左移1
                //default: y = 1'b0;
            });
            MuxKeyWithDefault #(4, 2, 1) i3 (dout[j], {L_R,shamt[2]}, 1'b0, {
                //  case (s)
                2'b00, /*y =*/mid_num[1][j],
                2'b01, /*y =*/(j==7||j==6||j==5||j==4)?sign:mid_num[1][j+1],//右移1
                2'b10, /*y =*/mid_num[1][j],
                2'b11, /*y =*/(j==0||j==1||j==2||j==3)?1'b0:mid_num[1][j-1]//左移1
                //default: y = 1'b0;
            });
        end


    endgenerate
endmodule
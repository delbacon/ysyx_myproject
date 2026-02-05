module Keyboard_Ascii (
    input rst,
    input ps2_clk,
    input ps2_data,
    output [7:0]data,
    output [15:0]num,
 //   output [7:0]data0,
 //   output [7:0]data1,
 //   output [7:0]data2,
    output [3:0]st

);
    localparam IDLE=4'd0,BIT0=4'd1,BIT1=4'd2,BIT2=4'd3,BIT3=4'd4,BIT4=4'd5,BIT5=4'd6,BIT6=4'd7,BIT7=4'd8,PARI=4'd9,STOP=4'd10,ERR=4'd11;
    wire [3:0]n_st;
    wire [1:0]odd;
    wire clk;
    assign clk = ~ps2_clk;
/* verilator lint_off WIDTHEXPAND */
    MuxKeyWithDefault #(16, 4, 4) i0 (n_st, st, 4'b0, {
        //  case (st)
        IDLE, /*n_st =*/(ps2_data==0)?BIT0:IDLE,
        BIT0, /*n_st =*/BIT1,
        BIT1, /*n_st =*/BIT2,
        BIT2, /*n_st =*/BIT3,
        BIT3, /*n_st =*/BIT4,
        BIT4, /*n_st =*/BIT5,
        BIT5, /*n_st =*/BIT6,
        BIT6, /*n_st =*/BIT7,
        BIT7, /*n_st =*/PARI,
        PARI, /*n_st =*/(ps2_data==~odd[0])?STOP:ERR,
        STOP, /*n_st =*/(ps2_data==1)?IDLE:ERR,
        ERR , /*n_st =*/(ps2_data==0)?BIT0:IDLE

        //default: y = 1'b0;
    });

    //st <= n_st
    Reg #(4, IDLE) st0 (clk, rst, n_st, st, 1'b1);


    wire odd_en;
    assign odd_en = (st!=IDLE);
    //if ps2_data==1   odd <= ~odd;
    // 位宽为1比特, 复位值为1'b1, 写使能一直有效
    Reg #(1, 1'b0) odd0 (ps2_data, rst, odd[1], odd[0], odd_en);
    Reg #(1, 1'b1) odd1 (ps2_data, rst, odd[0], odd[1], odd_en);



    // 位宽为1比特, 复位值为1'b1, 写使能一直有效
    wire data_en;
    assign data_en = (st == BIT0 || st == BIT1 || st == BIT2 || st == BIT3 || st == BIT4 || st == BIT5 || st == BIT6 );
    genvar i;
    generate
        for(i=7;i>0;i--)begin:inst
            Reg #(1, 1'b1) d0 (clk, rst, i==7?ps2_data:data[i], data[i-1], data_en);
        end
    endgenerate

/*
    assign save_en = (st == IDLE);
    Reg #(8, 8'b0) m0 (clk, rst, data0, data1, save_en);
    Reg #(8, 8'b0) m1 (clk, rst, data1, data2, save_en);

*/

    //检测是否松手
    wire left_flag;
    assign left_flag = (data==8'h70)?1'b1:1'b0;

    genvar j;
    generate
        for(j=0;j<16;j++)begin:inst2
            Reg #(1, 1'b0) num0 (left_flag, rst, j==0?1:num[j-1], num[j], 1'b1);
        end
    endgenerate

endmodule

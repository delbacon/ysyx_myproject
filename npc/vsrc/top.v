
module top(
  input clk,
  input rst,
  
  output [7:0] seg0,
  output [7:0] seg1,
  output [7:0] seg2,
  output [7:0] seg4,
  output [7:0] seg5,
  output [7:0] seg6,
  output [7:0] seg7

);
  wire [7:0] out;
  wire [3:0] pc;
  wire [7:0] test0, test1, test2, test3;
  sCPU u_sCPU(clk, rst, out, pc, test0, test1, test2, test3);


  bcd7seg inst_bcd7seg0(
    .b    (out[7:4] ),
    .h    (seg1)
  );
  bcd7seg inst_bcd7seg1(
    .b    (out[3:0] ),
    .h    (seg0)
  );
  bcd7seg inst_bcd7seg2(
    .b    (pc ),
    .h    (seg2)
  );


  bcd7seg inst_bcd7seg9(
    .b    (test0[3:0] ),
    .h    (seg4)
  );
  bcd7seg inst_bcd7seg8(
    .b    (test1[3:0] ),
    .h    (seg5)
  );
  bcd7seg inst_bcd7seg7(
    .b    (test2[3:0] ),
    .h    (seg6)
  );
  bcd7seg inst_bcd7seg6(
    .b    (test3[3:0] ),
    .h    (seg7)
  );


endmodule


/*VGA
module top(
    input clk,
    input rst,
    output VGA_CLK,
    output VGA_HSYNC,
    output VGA_VSYNC,
    output VGA_BLANK_N,
    output [7:0] VGA_R,
    output [7:0] VGA_G,
    output [7:0] VGA_B
);
    assign VGA_CLK = clk;

    wire [9:0] h_addr;
    wire [9:0] v_addr;
    wire [23:0] vga_data;

    vga_ctrl my_vga_ctrl(
        .pclk(clk),
        .reset(rst),
        .vga_data(vga_data),
        .h_addr(h_addr),
        .v_addr(v_addr),
        .hsync(VGA_HSYNC),
        .vsync(VGA_VSYNC),
        .valid(VGA_BLANK_N),
        .vga_r(VGA_R),
        .vga_g(VGA_G),
        .vga_b(VGA_B)
    );

    vmem my_vmem(
        .h_addr(h_addr),
        .v_addr(v_addr[8:0]),
        .vga_data(vga_data)
    );
endmodule

module vmem(
    input [9:0] h_addr,
    input [8:0] v_addr,
    output [23:0] vga_data
);

reg [23:0] vga_mem [524287:0];

initial begin
    $readmemh("picture.hex", vga_mem);
end

assign vga_data = vga_mem[{h_addr, v_addr}];
endmodule

*/
/*
//keyboard_ascii
module top(
  input ps2_clk,
  input ps2_data,
  input rst,
  output [7:0] seg0,
  output [7:0] seg1,
  output [3:0] st,
  output [15:0] num,
  output [7:0] data
);
  bcd7seg inst_bcd7seg0(
    .b    (data[7:4] ),
    .h    (seg1)
  );
  bcd7seg inst_bcd7seg1(
    .b    (data[3:0] ),
    .h    (seg0)
  );
Keyboard_Ascii u_Keyboard_Ascii (
    .rst     (rst     ),
    .ps2_clk (ps2_clk ),
    .ps2_data(ps2_data),
    .data    (data    ),
    .num     (num     ),
    .st      (st      )
);
endmodule
*/

/*Random_Gene
module top(
  input clk,
  input rst,
  output [7:0] seg0,
  output [7:0] seg1
);
  wire [7:0]dout;
  bcd7seg inst_bcd7seg0(
    .b    (dout[7:4] ),
    .h    (seg1)
  );
  bcd7seg inst_bcd7seg1(
    .b    (dout[3:0] ),
    .h    (seg0)
  );
  Random_Gene Random_Gene0 (
      .clk  (clk),
      .rst  (rst),
      .out  (dout)
  );

endmodule
*/

/*Barrel_Shifter
module top(
  input  L_R,
  input  A_L,
  input  [7:0] din,
  input  [2:0] shamt,
  output [7:0] seg0,
  output [7:0] seg1,
  output [7:0] seg2,
  output [7:0] seg3,
  output [7:0] dout
);

bcd7seg inst_bcd7seg0(
  .b    (din[7:4] ),
  .h    (seg3)
);
bcd7seg inst_bcd7seg1(
  .b    (din[3:0] ),
  .h    (seg2)
);
bcd7seg inst_bcd7seg2(
  .b    (dout[7:4]),
  .h    (seg1)
);
bcd7seg inst_bcd7seg3(
  .b    (dout[3:0]),
  .h    (seg0)
);

Barrel_Shifter u_Barrel_Shifter (
  .din     (din  ),
  .shamt   (shamt),
  .L_R     (L_R  ),
  .A_L     (A_L  ),
  .dout    (dout )
);

endmodule
*/


/*adder
module top(
  input [2:0] mode,
  input [3:0] a,
  input [3:0] b,  
  output zero,
  output cout,
  output overflow,
  output [7:0] seg0,
  output [7:0] seg1,
  output [7:0] seg2
);
wire [3:0] out;
bcd7seg inst_bcd7seg(
  .b    (a ),
  .h    (seg2)
);

bcd7seg inst_bcd7seg2(
  .b    (b ),
  .h    (seg1)
);

bcd7seg inst_bcd7seg3(
  .b    (out ),
  .h    (seg0)
);

adder4bit u_adder4bit(
    .cin      (mode[0] ),
    .a        (a       ), 
    .b        (b       ),
    .out      (out     ),
    .cout     (cout    ),
    .overflow (overflow)
);
assign zero = 0;
endmodule
*/
/*alu
module top(
  input [2:0] mode,
  input [3:0] a,
  input [3:0] b,  
  output zero,
  output cout,
  output overflow,
  output [7:0] seg0,
  output [7:0] seg1,
  output [7:0] seg2
);
wire [3:0] out;
bcd7seg inst_bcd7seg(
  .b    (a ),
  .h    (seg2)
);

bcd7seg inst_bcd7seg2(
  .b    (b ),
  .h    (seg1)
);

bcd7seg inst_bcd7seg3(
  .b    (out ),
  .h    (seg0)
);

alu4bit u_alu4bit(
    .mode      (mode     ),
    .a         (a        ),
    .b         (b        ),
    .out       (out      ),
    .zero      (zero     ),
    .cout      (cout     ),
    .overflow  (overflow )
);

endmodule
*/

/*encoder8_3 bcd7seg
module top(
  input [7:0]in,
  output flag,
  output [3:0]out,
  output [7:0]seg0
);


encoder8_3 inst_encoder8_3(
  .in   (in  ),
  .flag (flag),
  .out  (out )
);

bcd7seg inst_bcd7seg(
  .b    (out ),
  .h    (seg0)
);

endmodule
*/
/*led_flow
module top(
  input clk,
  input rst,
  input sw,
  output reg [15:0] led,
  output reg [31:0]cnt
);


led_flow inst_led_flow(
  .clk (clk),
  .rst (rst),
  .sw  (sw ),
  .led (led),
  .cnt (cnt)
);
endmodule
*/

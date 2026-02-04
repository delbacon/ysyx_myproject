//Generate the verilog at 2026-02-04T15:56:33 by iSTA.
module top (
clk,
rst,
sw,
led_0_,
led_1_,
led_2_,
led_3_,
led_4_,
led_5_,
led_6_,
led_7_,
led_8_,
led_9_,
led_10_,
led_11_,
led_12_,
led_13_,
led_14_,
led_15_,
cnt_0_,
cnt_1_,
cnt_2_,
cnt_3_,
cnt_4_,
cnt_5_,
cnt_6_,
cnt_7_,
cnt_8_,
cnt_9_,
cnt_10_,
cnt_11_,
cnt_12_,
cnt_13_,
cnt_14_,
cnt_15_,
cnt_16_,
cnt_17_,
cnt_18_,
cnt_19_,
cnt_20_,
cnt_21_,
cnt_22_,
cnt_23_,
cnt_24_,
cnt_25_,
cnt_26_,
cnt_27_,
cnt_28_,
cnt_29_,
cnt_30_,
cnt_31_
);

input clk ;
input rst ;
input sw ;
output led_0_ ;
output led_1_ ;
output led_2_ ;
output led_3_ ;
output led_4_ ;
output led_5_ ;
output led_6_ ;
output led_7_ ;
output led_8_ ;
output led_9_ ;
output led_10_ ;
output led_11_ ;
output led_12_ ;
output led_13_ ;
output led_14_ ;
output led_15_ ;
output cnt_0_ ;
output cnt_1_ ;
output cnt_2_ ;
output cnt_3_ ;
output cnt_4_ ;
output cnt_5_ ;
output cnt_6_ ;
output cnt_7_ ;
output cnt_8_ ;
output cnt_9_ ;
output cnt_10_ ;
output cnt_11_ ;
output cnt_12_ ;
output cnt_13_ ;
output cnt_14_ ;
output cnt_15_ ;
output cnt_16_ ;
output cnt_17_ ;
output cnt_18_ ;
output cnt_19_ ;
output cnt_20_ ;
output cnt_21_ ;
output cnt_22_ ;
output cnt_23_ ;
output cnt_24_ ;
output cnt_25_ ;
output cnt_26_ ;
output cnt_27_ ;
output cnt_28_ ;
output cnt_29_ ;
output cnt_30_ ;
output cnt_31_ ;

wire clk ;
wire rst ;
wire sw ;
wire led_0_ ;
wire led_1_ ;
wire led_2_ ;
wire led_3_ ;
wire led_4_ ;
wire led_5_ ;
wire led_6_ ;
wire led_7_ ;
wire led_8_ ;
wire led_9_ ;
wire led_10_ ;
wire led_11_ ;
wire led_12_ ;
wire led_13_ ;
wire led_14_ ;
wire led_15_ ;
wire cnt_0_ ;
wire cnt_1_ ;
wire cnt_2_ ;
wire cnt_3_ ;
wire cnt_4_ ;
wire cnt_5_ ;
wire cnt_6_ ;
wire cnt_7_ ;
wire cnt_8_ ;
wire cnt_9_ ;
wire cnt_10_ ;
wire cnt_11_ ;
wire cnt_12_ ;
wire cnt_13_ ;
wire cnt_14_ ;
wire cnt_15_ ;
wire cnt_16_ ;
wire cnt_17_ ;
wire cnt_18_ ;
wire cnt_19_ ;
wire cnt_20_ ;
wire cnt_21_ ;
wire cnt_22_ ;
wire cnt_23_ ;
wire cnt_24_ ;
wire cnt_25_ ;
wire cnt_26_ ;
wire cnt_27_ ;
wire cnt_28_ ;
wire cnt_29_ ;
wire cnt_30_ ;
wire cnt_31_ ;
wire \cnt[0]_reg_p_D ;
wire \cnt[0]_reg_p_RN ;
wire \cnt[10]_reg_p_D ;
wire \cnt[10]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[11]_reg_p_D ;
wire \cnt[11]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[12]_reg_p_D ;
wire \cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[13]_reg_p_D ;
wire \cnt[13]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[14]_reg_p_D ;
wire \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B ;
wire \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ;
wire \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ;
wire \cnt[15]_reg_p_D ;
wire \cnt[15]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[16]_reg_p_D ;
wire \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A0 ;
wire \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1 ;
wire \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ;
wire \cnt[17]_reg_p_D ;
wire \cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B ;
wire \cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ;
wire \cnt[18]_reg_p_D ;
wire \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B ;
wire \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ;
wire \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y_B ;
wire \cnt[19]_reg_p_D ;
wire \cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B ;
wire \cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ;
wire \cnt[1]_reg_p_D ;
wire \cnt[20]_reg_p_D ;
wire \cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ;
wire \cnt[21]_reg_p_D ;
wire \cnt[21]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[22]_reg_p_D ;
wire \cnt[22]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[23]_reg_p_D ;
wire \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ;
wire \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NOR4BBX4H7L_C_D ;
wire \cnt[24]_reg_p_D ;
wire \cnt[24]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[25]_reg_p_D ;
wire \cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[26]_reg_p_D ;
wire \cnt[26]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[27]_reg_p_D ;
wire \cnt[27]_reg_p_D_XNOR2X1H7L_Y_B ;
wire \cnt[28]_reg_p_D ;
wire \cnt[28]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[29]_reg_p_D ;
wire \cnt[29]_reg_p_D_XNOR2X1H7L_Y_B ;
wire \cnt[2]_reg_p_D ;
wire \cnt[2]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[30]_reg_p_D ;
wire \cnt[30]_reg_p_D_XNOR2X4H7L_Y_B ;
wire \cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ;
wire \cnt[31]_reg_p_D ;
wire \cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ;
wire \cnt[3]_reg_p_D ;
wire \cnt[3]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[4]_reg_p_D ;
wire \cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[5]_reg_p_D ;
wire \cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[6]_reg_p_D ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_A1 ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0 ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_A ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_B ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_C ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_D ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C_B ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_C ;
wire \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_D ;
wire \cnt[7]_reg_p_D ;
wire \cnt[7]_reg_p_D_XNOR2X0P5H7L_Y_B ;
wire \cnt[8]_reg_p_D ;
wire \cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ;
wire \cnt[9]_reg_p_D ;
wire \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ;
wire \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B ;
wire \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B_XOR2X0P5H7L_Y_B ;
wire \led[0]_reg_p_CK ;
wire \led[0]_reg_p_D ;
wire \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B ;
wire \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_A ;
wire \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_B ;
wire \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_C ;
wire \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_D ;
wire \led[10]_reg_p_D ;
wire \led[11]_reg_p_D ;
wire \led[12]_reg_p_D ;
wire \led[13]_reg_p_D ;
wire \led[14]_reg_p_D ;
wire \led[15]_reg_p_D ;
wire \led[1]_reg_p_D ;
wire \led[2]_reg_p_D ;
wire \led[3]_reg_p_D ;
wire \led[4]_reg_p_D ;
wire \led[5]_reg_p_D ;
wire \led[6]_reg_p_D ;
wire \led[7]_reg_p_D ;
wire \led[8]_reg_p_D ;
wire \led[9]_reg_p_D ;


DFFRQX2H7L \cnt[0]_reg_p ( .CK(clk ), .D(\cnt[0]_reg_p_D ), .Q(cnt_0_ ), .RN(\cnt[0]_reg_p_RN ) );
INVX0P5H7L \cnt[0]_reg_p_D_INVX0P5H7L_Y ( .A(cnt_0_ ), .Y(\cnt[0]_reg_p_D ) );
DFFRQX2H7L \cnt[10]_reg_p ( .CK(clk ), .D(\cnt[10]_reg_p_D ), .Q(cnt_10_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[10]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_10_ ), .B(\cnt[10]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[10]_reg_p_D ) );
NAND3X0P5H7L \cnt[10]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND3X0P5H7L_Y ( .A(cnt_9_ ), .B(cnt_8_ ), .C(\cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[10]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[11]_reg_p ( .CK(clk ), .D(\cnt[11]_reg_p_D ), .Q(cnt_11_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[11]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_11_ ), .B(\cnt[11]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[11]_reg_p_D ) );
NAND4X0P5H7L \cnt[11]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND4X0P5H7L_Y ( .A(cnt_10_ ), .B(cnt_9_ ), .C(cnt_8_ ), .D(\cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[11]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[12]_reg_p ( .CK(clk ), .D(\cnt[12]_reg_p_D ), .Q(cnt_12_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[12]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_12_ ), .B(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[12]_reg_p_D ) );
DFFRQX2H7L \cnt[13]_reg_p ( .CK(clk ), .D(\cnt[13]_reg_p_D ), .Q(cnt_13_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[13]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_13_ ), .B(\cnt[13]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[13]_reg_p_D ) );
NOR2BX1H7L \cnt[13]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2BX1H7L_Z ( .AN(cnt_12_ ), .B(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Z(\cnt[13]_reg_p_D_XOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[14]_reg_p ( .CK(clk ), .D(\cnt[14]_reg_p_D ), .Q(cnt_14_ ), .RN(\cnt[0]_reg_p_RN ) );
NOR2X0P5H7L \cnt[14]_reg_p_D_NOR2X0P5H7L_Y ( .A(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .B(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B ), .Y(\cnt[14]_reg_p_D ) );
XNOR2X0P5H7L \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y ( .A(cnt_14_ ), .B(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ), .Y(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B ) );
NOR2X0P5H7L \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y ( .A(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .B(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ), .Y(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ) );
NAND2X0P5H7L \cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_13_ ), .B(cnt_12_ ), .Y(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[15]_reg_p ( .CK(clk ), .D(\cnt[15]_reg_p_D ), .Q(cnt_15_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[15]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_15_ ), .B(\cnt[15]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[15]_reg_p_D ) );
NAND2X0P5H7L \cnt[15]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_14_ ), .B(\cnt[14]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ), .Y(\cnt[15]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[16]_reg_p ( .CK(clk ), .D(\cnt[16]_reg_p_D ), .Q(cnt_16_ ), .RN(\cnt[0]_reg_p_RN ) );
AOI21X0P5H7L \cnt[16]_reg_p_D_AOI21X0P5H7L_Y ( .A0(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A0 ), .A1(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1 ), .B0(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .Y(\cnt[16]_reg_p_D ) );
OAI21X0P5H7L \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A0_OAI21X0P5H7L_Y ( .A0(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .A1(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .B0(cnt_16_ ), .Y(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A0 ) );
OR3X1H7L \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y ( .A(cnt_16_ ), .B(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .C(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .Y(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1 ) );
NAND4X2H7L \cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C_NAND4X2H7L_Y ( .A(cnt_15_ ), .B(cnt_14_ ), .C(cnt_13_ ), .D(cnt_12_ ), .Y(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ) );
DFFRQX2H7L \cnt[17]_reg_p ( .CK(clk ), .D(\cnt[17]_reg_p_D ), .Q(cnt_17_ ), .RN(\cnt[0]_reg_p_RN ) );
NOR2X0P5H7L \cnt[17]_reg_p_D_NOR2X0P5H7L_Y ( .A(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .B(\cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B ), .Y(\cnt[17]_reg_p_D ) );
XNOR2X0P5H7L \cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y ( .A(cnt_17_ ), .B(\cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ), .Y(\cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B ) );
NOR3BX0P5H7L \cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3BX0P5H7L_Y ( .AN(cnt_16_ ), .B(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .C(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .Y(\cnt[17]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[18]_reg_p ( .CK(clk ), .D(\cnt[18]_reg_p_D ), .Q(cnt_18_ ), .RN(\cnt[0]_reg_p_RN ) );
NOR2X0P5H7L \cnt[18]_reg_p_D_NOR2X0P5H7L_Y ( .A(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .B(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B ), .Y(\cnt[18]_reg_p_D ) );
XNOR2X0P5H7L \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y ( .A(cnt_18_ ), .B(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ), .Y(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B ) );
NOR3X0P5H7L \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y ( .A(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .B(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y_B ), .C(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .Y(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ) );
NAND2X0P5H7L \cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_17_ ), .B(cnt_16_ ), .Y(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[19]_reg_p ( .CK(clk ), .D(\cnt[19]_reg_p_D ), .Q(cnt_19_ ), .RN(\cnt[0]_reg_p_RN ) );
NOR2X0P5H7L \cnt[19]_reg_p_D_NOR2X0P5H7L_Y ( .A(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .B(\cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B ), .Y(\cnt[19]_reg_p_D ) );
XNOR2X0P5H7L \cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y ( .A(cnt_19_ ), .B(\cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ), .Y(\cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B ) );
NOR4BX0P5H7L \cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR4BX0P5H7L_Y ( .AN(cnt_18_ ), .B(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ), .C(\cnt[18]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B_NOR3X0P5H7L_Y_B ), .D(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .Y(\cnt[19]_reg_p_D_NOR2X0P5H7L_Y_B_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[1]_reg_p ( .CK(clk ), .D(\cnt[1]_reg_p_D ), .Q(cnt_1_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[1]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_0_ ), .B(cnt_1_ ), .Y(\cnt[1]_reg_p_D ) );
DFFRQX2H7L \cnt[20]_reg_p ( .CK(clk ), .D(\cnt[20]_reg_p_D ), .Q(cnt_20_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[20]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_20_ ), .B(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[20]_reg_p_D ) );
NAND2X0P5H7L \cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .B(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ), .Y(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[21]_reg_p ( .CK(clk ), .D(\cnt[21]_reg_p_D ), .Q(cnt_21_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[21]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_21_ ), .B(\cnt[21]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[21]_reg_p_D ) );
NAND3X0P5H7L \cnt[21]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND3X0P5H7L_Y ( .A(cnt_20_ ), .B(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .C(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ), .Y(\cnt[21]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[22]_reg_p ( .CK(clk ), .D(\cnt[22]_reg_p_D ), .Q(cnt_22_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[22]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_22_ ), .B(\cnt[22]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[22]_reg_p_D ) );
NAND4X0P5H7L \cnt[22]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND4X0P5H7L_Y ( .A(cnt_21_ ), .B(cnt_20_ ), .C(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .D(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ), .Y(\cnt[22]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[23]_reg_p ( .CK(clk ), .D(\cnt[23]_reg_p_D ), .Q(cnt_23_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[23]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_23_ ), .B(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[23]_reg_p_D ) );
NOR2X0P5H7L \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y ( .A(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B ), .B(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ), .Y(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B ) );
NAND3X0P5H7L \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NAND3X0P5H7L_Y ( .A(cnt_22_ ), .B(cnt_21_ ), .C(cnt_20_ ), .Y(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ) );
NOR4BBX4H7L \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NOR4BBX4H7L_C ( .AN(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .BN(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ), .C(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ), .D(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NOR4BBX4H7L_C_D ), .Y(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ) );
NAND2X0P5H7L \cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NOR4BBX4H7L_C_D_NAND2X0P5H7L_Y ( .A(cnt_24_ ), .B(cnt_23_ ), .Y(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B_NOR4BBX4H7L_C_D ) );
DFFRQX2H7L \cnt[24]_reg_p ( .CK(clk ), .D(\cnt[24]_reg_p_D ), .Q(cnt_24_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[24]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_24_ ), .B(\cnt[24]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[24]_reg_p_D ) );
NOR3BX0P5H7L \cnt[24]_reg_p_D_XOR2X0P5H7L_Y_B_NOR3BX0P5H7L_Y ( .AN(cnt_23_ ), .B(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B ), .C(\cnt[23]_reg_p_D_XOR2X0P5H7L_Y_B_NOR2X0P5H7L_Y_B ), .Y(\cnt[24]_reg_p_D_XOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[25]_reg_p ( .CK(clk ), .D(\cnt[25]_reg_p_D ), .Q(cnt_25_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[25]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_25_ ), .B(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[25]_reg_p_D ) );
DFFRQX2H7L \cnt[26]_reg_p ( .CK(clk ), .D(\cnt[26]_reg_p_D ), .Q(cnt_26_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[26]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_26_ ), .B(\cnt[26]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[26]_reg_p_D ) );
NAND2X0P5H7L \cnt[26]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_25_ ), .B(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[26]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[27]_reg_p ( .CK(clk ), .D(\cnt[27]_reg_p_D ), .Q(cnt_27_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X1H7L \cnt[27]_reg_p_D_XNOR2X1H7L_Y ( .A(cnt_27_ ), .B(\cnt[27]_reg_p_D_XNOR2X1H7L_Y_B ), .Y(\cnt[27]_reg_p_D ) );
NAND3X1P4H7L \cnt[27]_reg_p_D_XNOR2X1H7L_Y_B_NAND3X1P4H7L_Y ( .A(cnt_25_ ), .B(cnt_26_ ), .C(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[27]_reg_p_D_XNOR2X1H7L_Y_B ) );
DFFRQX2H7L \cnt[28]_reg_p ( .CK(clk ), .D(\cnt[28]_reg_p_D ), .Q(cnt_28_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[28]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_28_ ), .B(\cnt[28]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[28]_reg_p_D ) );
NAND2X0P5H7L \cnt[28]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .B(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ), .Y(\cnt[28]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[29]_reg_p ( .CK(clk ), .D(\cnt[29]_reg_p_D ), .Q(cnt_29_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X1H7L \cnt[29]_reg_p_D_XNOR2X1H7L_Y ( .A(cnt_29_ ), .B(\cnt[29]_reg_p_D_XNOR2X1H7L_Y_B ), .Y(\cnt[29]_reg_p_D ) );
NAND3X1P4H7L \cnt[29]_reg_p_D_XNOR2X1H7L_Y_B_NAND3X1P4H7L_Y ( .A(cnt_28_ ), .B(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .C(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ), .Y(\cnt[29]_reg_p_D_XNOR2X1H7L_Y_B ) );
DFFRQX2H7L \cnt[2]_reg_p ( .CK(clk ), .D(\cnt[2]_reg_p_D ), .Q(cnt_2_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[2]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_2_ ), .B(\cnt[2]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[2]_reg_p_D ) );
NAND2X0P5H7L \cnt[2]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_0_ ), .B(cnt_1_ ), .Y(\cnt[2]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[30]_reg_p ( .CK(clk ), .D(\cnt[30]_reg_p_D ), .Q(cnt_30_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X4H7L \cnt[30]_reg_p_D_XNOR2X4H7L_Y ( .A(cnt_30_ ), .B(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B ), .Y(\cnt[30]_reg_p_D ) );
NAND4X2H7L \cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y ( .A(cnt_29_ ), .B(cnt_28_ ), .C(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .D(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ), .Y(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B ) );
AND3X1P4H7L \cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D_AND3X1P4H7L_Y ( .A(cnt_25_ ), .B(cnt_27_ ), .C(cnt_26_ ), .Y(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ) );
DFFRQX2H7L \cnt[31]_reg_p ( .CK(clk ), .D(\cnt[31]_reg_p_D ), .Q(cnt_31_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[31]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_31_ ), .B(\cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[31]_reg_p_D ) );
NAND2X0P5H7L \cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(\cnt[25]_reg_p_D_XOR2X0P5H7L_Y_B ), .B(\cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ), .Y(\cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
AND4X0P5H7L \cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B_AND4X0P5H7L_Y ( .A(cnt_29_ ), .B(cnt_28_ ), .C(cnt_30_ ), .D(\cnt[30]_reg_p_D_XNOR2X4H7L_Y_B_NAND4X2H7L_Y_D ), .Y(\cnt[31]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[3]_reg_p ( .CK(clk ), .D(\cnt[3]_reg_p_D ), .Q(cnt_3_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[3]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_3_ ), .B(\cnt[3]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[3]_reg_p_D ) );
NAND3X0P5H7L \cnt[3]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND3X0P5H7L_Y ( .A(cnt_0_ ), .B(cnt_2_ ), .C(cnt_1_ ), .Y(\cnt[3]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[4]_reg_p ( .CK(clk ), .D(\cnt[4]_reg_p_D ), .Q(cnt_4_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[4]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_4_ ), .B(\cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[4]_reg_p_D ) );
NAND4X1H7L \cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND4X1H7L_Y ( .A(cnt_0_ ), .B(cnt_3_ ), .C(cnt_2_ ), .D(cnt_1_ ), .Y(\cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
NOR2BX1H7L \cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B_NOR2BX1H7L_B ( .AN(cnt_4_ ), .B(\cnt[4]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Z(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[5]_reg_p ( .CK(clk ), .D(\cnt[5]_reg_p_D ), .Q(cnt_5_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[5]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_5_ ), .B(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[5]_reg_p_D ) );
DFFRQX2H7L \cnt[6]_reg_p ( .CK(clk ), .D(\cnt[6]_reg_p_D ), .Q(cnt_6_ ), .RN(\cnt[0]_reg_p_RN ) );
AO21X1H7L \cnt[6]_reg_p_D_AO21X1H7L_Y ( .A0(cnt_6_ ), .A1(\cnt[6]_reg_p_D_AO21X1H7L_Y_A1 ), .B0(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0 ), .Y(\cnt[6]_reg_p_D ) );
NAND2X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_A1_NAND2X0P5H7L_Y ( .A(cnt_5_ ), .B(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_A1 ) );
NOR3X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y ( .A(cnt_6_ ), .B(\cnt[6]_reg_p_D_AO21X1H7L_Y_A1 ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0 ) );
AND3X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_AND3X1P4H7L_C ( .A(cnt_5_ ), .B(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C ), .Y(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ) );
NOR4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y ( .A(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A ), .B(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_C ), .D(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_D ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C ) );
NAND4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y ( .A(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_A ), .B(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_B ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_C ), .D(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_D ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A ) );
NOR4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_A_NOR4X0P5H7L_Y ( .A(cnt_7_ ), .B(cnt_6_ ), .C(cnt_29_ ), .D(cnt_28_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_A ) );
NOR4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_B_NOR4X0P5H7L_Y ( .A(cnt_27_ ), .B(cnt_26_ ), .C(cnt_30_ ), .D(cnt_31_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_B ) );
NOR4BX0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_C_NOR4BX0P5H7L_Y ( .AN(cnt_9_ ), .B(cnt_8_ ), .C(cnt_25_ ), .D(cnt_24_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_C ) );
NOR4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_D_NOR4X0P5H7L_Y ( .A(cnt_11_ ), .B(cnt_10_ ), .C(cnt_13_ ), .D(cnt_12_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_A_NAND4X0P5H7L_Y_D ) );
NAND4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NAND4X0P5H7L_Y ( .A(cnt_19_ ), .B(cnt_18_ ), .C(cnt_17_ ), .D(cnt_16_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B ) );
NOR4BBX4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C ( .AN(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN ), .BN(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B ), .D(\cnt[16]_reg_p_D_AOI21X0P5H7L_Y_A1_OR3X1H7L_Y_C ), .Y(\cnt[20]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y_B ) );
AND3X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C ( .A(cnt_4_ ), .B(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C_B ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN ), .Y(\cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ) );
AND4X0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C_B_AND4X0P5H7L_Y ( .A(cnt_0_ ), .B(cnt_3_ ), .C(cnt_2_ ), .D(cnt_1_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C_B ) );
AND3X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_Y ( .A(cnt_7_ ), .B(cnt_6_ ), .C(cnt_5_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN ) );
AND4X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN_AND4X1P4H7L_Y ( .A(cnt_11_ ), .B(cnt_10_ ), .C(cnt_9_ ), .D(cnt_8_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN ) );
NAND4X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN_NAND4X1P4H7L_D ( .A(cnt_4_ ), .B(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN_AND3X1P4H7L_C_B ), .C(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_AN ), .D(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_B_NOR4BBX4H7L_C_BN ), .Y(\cnt[12]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
NAND2BX0P5H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_C_NAND2BX0P5H7L_Y ( .AN(cnt_15_ ), .B(cnt_14_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_C ) );
OR4X1P4H7L \cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_D_OR4X1P4H7L_Y ( .A(cnt_23_ ), .B(cnt_22_ ), .C(cnt_21_ ), .D(cnt_20_ ), .Y(\cnt[6]_reg_p_D_AO21X1H7L_Y_B0_NOR3X0P5H7L_Y_C_NOR4X0P5H7L_Y_D ) );
DFFRQX2H7L \cnt[7]_reg_p ( .CK(clk ), .D(\cnt[7]_reg_p_D ), .Q(cnt_7_ ), .RN(\cnt[0]_reg_p_RN ) );
XNOR2X0P5H7L \cnt[7]_reg_p_D_XNOR2X0P5H7L_Y ( .A(cnt_7_ ), .B(\cnt[7]_reg_p_D_XNOR2X0P5H7L_Y_B ), .Y(\cnt[7]_reg_p_D ) );
NAND3X0P5H7L \cnt[7]_reg_p_D_XNOR2X0P5H7L_Y_B_NAND3X0P5H7L_Y ( .A(cnt_6_ ), .B(cnt_5_ ), .C(\cnt[5]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[7]_reg_p_D_XNOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \cnt[8]_reg_p ( .CK(clk ), .D(\cnt[8]_reg_p_D ), .Q(cnt_8_ ), .RN(\cnt[0]_reg_p_RN ) );
XOR2X0P5H7L \cnt[8]_reg_p_D_XOR2X0P5H7L_Y ( .A(cnt_8_ ), .B(\cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[8]_reg_p_D ) );
DFFRQX2H7L \cnt[9]_reg_p ( .CK(clk ), .D(\cnt[9]_reg_p_D ), .Q(cnt_9_ ), .RN(\cnt[0]_reg_p_RN ) );
NOR2X0P5H7L \cnt[9]_reg_p_D_NOR2X0P5H7L_Y ( .A(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .B(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B ), .Y(\cnt[9]_reg_p_D ) );
ICGX0P5H7L \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A_ICGX0P5H7L_E ( .CK(clk ), .E(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_A ), .ECK(\led[0]_reg_p_CK ) );
XOR2X0P5H7L \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B_XOR2X0P5H7L_Y ( .A(cnt_9_ ), .B(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B_XOR2X0P5H7L_Y_B ), .Y(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B ) );
NAND2X0P5H7L \cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B_XOR2X0P5H7L_Y_B_NAND2X0P5H7L_Y ( .A(cnt_8_ ), .B(\cnt[8]_reg_p_D_XOR2X0P5H7L_Y_B ), .Y(\cnt[9]_reg_p_D_NOR2X0P5H7L_Y_B_XOR2X0P5H7L_Y_B ) );
DFFRQX2H7L \led[0]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[0]_reg_p_D ), .Q(led_0_ ), .RN(\cnt[0]_reg_p_RN ) );
NAND2BX0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y ( .AN(led_15_ ), .B(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B ), .Y(\led[0]_reg_p_D ) );
NAND4X0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y ( .A(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_A ), .B(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_B ), .C(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_C ), .D(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_D ), .Y(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B ) );
NOR4X0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_A_NOR4X0P5H7L_Y ( .A(led_14_ ), .B(led_13_ ), .C(led_4_ ), .D(led_0_ ), .Y(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_A ) );
NOR4X0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_B_NOR4X0P5H7L_Y ( .A(led_3_ ), .B(led_2_ ), .C(led_1_ ), .D(led_5_ ), .Y(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_B ) );
NOR4X0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_C_NOR4X0P5H7L_Y ( .A(led_12_ ), .B(led_11_ ), .C(led_10_ ), .D(led_9_ ), .Y(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_C ) );
NOR3X0P5H7L \led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_D_NOR3X0P5H7L_Y ( .A(led_8_ ), .B(led_7_ ), .C(led_6_ ), .Y(\led[0]_reg_p_D_NAND2BX0P5H7L_Y_B_NAND4X0P5H7L_Y_D ) );
DFFRQX2H7L \led[10]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[10]_reg_p_D ), .Q(led_10_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[10]_reg_p_D_BUFX1H7L_Y ( .A(led_9_ ), .Y(\led[10]_reg_p_D ) );
DFFRQX2H7L \led[11]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[11]_reg_p_D ), .Q(led_11_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[11]_reg_p_D_BUFX1H7L_Y ( .A(led_10_ ), .Y(\led[11]_reg_p_D ) );
DFFRQX2H7L \led[12]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[12]_reg_p_D ), .Q(led_12_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[12]_reg_p_D_BUFX1H7L_Y ( .A(led_11_ ), .Y(\led[12]_reg_p_D ) );
DFFRQX2H7L \led[13]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[13]_reg_p_D ), .Q(led_13_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[13]_reg_p_D_BUFX1H7L_Y ( .A(led_12_ ), .Y(\led[13]_reg_p_D ) );
DFFRQX2H7L \led[14]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[14]_reg_p_D ), .Q(led_14_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[14]_reg_p_D_BUFX1H7L_Y ( .A(led_13_ ), .Y(\led[14]_reg_p_D ) );
DFFRQX2H7L \led[15]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[15]_reg_p_D ), .Q(led_15_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[15]_reg_p_D_BUFX1H7L_Y ( .A(led_14_ ), .Y(\led[15]_reg_p_D ) );
DFFRQX2H7L \led[1]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[1]_reg_p_D ), .Q(led_1_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[1]_reg_p_D_BUFX1H7L_Y ( .A(led_0_ ), .Y(\led[1]_reg_p_D ) );
DFFRQX2H7L \led[2]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[2]_reg_p_D ), .Q(led_2_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[2]_reg_p_D_BUFX1H7L_Y ( .A(led_1_ ), .Y(\led[2]_reg_p_D ) );
DFFRQX2H7L \led[3]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[3]_reg_p_D ), .Q(led_3_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[3]_reg_p_D_BUFX1H7L_Y ( .A(led_2_ ), .Y(\led[3]_reg_p_D ) );
DFFRQX2H7L \led[4]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[4]_reg_p_D ), .Q(led_4_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[4]_reg_p_D_BUFX1H7L_Y ( .A(led_3_ ), .Y(\led[4]_reg_p_D ) );
DFFRQX2H7L \led[5]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[5]_reg_p_D ), .Q(led_5_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[5]_reg_p_D_BUFX1H7L_Y ( .A(led_4_ ), .Y(\led[5]_reg_p_D ) );
DFFRQX2H7L \led[6]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[6]_reg_p_D ), .Q(led_6_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[6]_reg_p_D_BUFX1H7L_Y ( .A(led_5_ ), .Y(\led[6]_reg_p_D ) );
DFFRQX2H7L \led[7]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[7]_reg_p_D ), .Q(led_7_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[7]_reg_p_D_BUFX1H7L_Y ( .A(led_6_ ), .Y(\led[7]_reg_p_D ) );
DFFRQX2H7L \led[8]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[8]_reg_p_D ), .Q(led_8_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[8]_reg_p_D_BUFX1H7L_Y ( .A(led_7_ ), .Y(\led[8]_reg_p_D ) );
DFFRQX2H7L \led[9]_reg_p ( .CK(\led[0]_reg_p_CK ), .D(\led[9]_reg_p_D ), .Q(led_9_ ), .RN(\cnt[0]_reg_p_RN ) );
BUFX1H7L \led[9]_reg_p_D_BUFX1H7L_Y ( .A(led_8_ ), .Y(\led[9]_reg_p_D ) );
INVX0P5H7L rst_INVX0P5H7L_A ( .A(rst ), .Y(\cnt[0]_reg_p_RN ) );

endmodule

/* verilator lint_off UNDRIVEN */

import "DPI-C" function int pROM_read_HDL(int addr) ;
// ROM 必定按 word 读，直接设置为 32 bit
module ysyx_26020055_pROM #(ADDR_WIDTH = 25, DATA_WIDTH = 32) (
    input                      clk                ,
    /* verilator lint_off UNUSEDSIGNAL */
    input                      rst                ,
    input [31:0]               vaddr              ,
    input                      reqValid           ,
    output reg                 respValid          ,
    input                      respReady          ,
    output                     reqReady           ,
    output reg[DATA_WIDTH-1:0] rdata                    
);
//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    initial begin
        for(int i=0;i<28'h800_0000;i=i+4)begin
            rf[i>>2] = pROM_read_HDL(i+32'h8000_0000);
        end
    end

    wire [ADDR_WIDTH-1:0] addr;
    assign addr = vaddr[ADDR_WIDTH-1:0];

//读
always @(posedge clk) begin
    if(reqValid)begin
        if(vaddr >= 32'h1000_0000 && vaddr < 32'h1000_1000) rdata <= pROM_read_HDL(vaddr);
        else rdata <= rf[addr>>2];
    end
end

// ============== 状态机 =================//
localparam IDLE = 2'b00,
           BUSY = 2'b01,
           WAITREADY = 2'b10;
reg [1:0] st,n_st;
always@(posedge clk)begin
    if(rst)
        st <= IDLE;
    else
        st <= n_st;
end
always@(*)begin
    case(st)
    // 如果收到 master 的读请求，则开始工作
        IDLE:  begin n_st = (reqValid)?BUSY:IDLE; end
        BUSY:  begin n_st = (respValid_base)?WAITREADY:BUSY; end
    // 自身工作完成后，开始等待 master 自身工作完成
        WAITREADY:begin   n_st = (respReady)?IDLE:WAITREADY;   end
        default : n_st = IDLE;
    endcase
end
wire respValid_base;
assign respValid = (st == WAITREADY || respValid_base);



// 随机延迟生成0-15
ysyx_26020055_lfsr uROM_ysyx_26020055_lfsr (
    .clk            (clk            ),
    .rst            (rst            ),
    .start          (reqReady       ),
    .output_pulse   (respValid_base )
);

ysyx_26020055_lfsr uROM_reqReady_ysyx_26020055_lfsr (
    .clk            (clk            ),
    .rst            (rst            ),
    .start          (reqValid       ),
    .output_pulse   (reqReady       )
);

/*
// for test 测试用可控延迟生成
reg flag_on;
always@(posedge clk)begin
    if(rst) flag_on <= 1'b0;
    else if(reqValid) flag_on <= 1'b1;
    else if(respValid) flag_on <= 1'b0;
end

reg [2:0] cnt;
always@(posedge clk)begin
    if(flag_on)
        cnt <= cnt + 1;
    else if(~flag_on)
        cnt <= 3'd0;
end
always@(posedge clk)begin
    if(rst)
        respValid <= 1'b0;
    else if(cnt >= 3'd6)
        respValid <= 1'b1;
    else 
        respValid <= 1'b0;

end
*/

endmodule


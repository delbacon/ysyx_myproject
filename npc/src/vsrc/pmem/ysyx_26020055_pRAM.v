import "DPI-C" function int pRAM_read_HDL(int addr, int len);
import "DPI-C" function void pRAM_write_HDL(int addr, int len, int data) ;

module ysyx_26020055_pRAM #(ADDR_WIDTH = 28, DATA_WIDTH = 8) (
    input                      clk                ,
    /* verilator lint_off UNUSEDSIGNAL */
    input                      rst                ,
    input [31:0]               vaddr              ,
    input                      reqValid           ,
    output reg                 respValid          ,
    input                      respReady          ,
    output                     reqReady           ,
    output reg[31:0]           rdata              ,
    input     [31:0]           wdata              ,
    input                      wen                ,
    input                      rden               ,
    input      [31:0]          wmask                                  
);
//寄存器组
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

   initial begin
        for(int i=0;i<28'h800_0000;i=i+4)begin
            {rf[i+3],rf[i+2],rf[i+1],rf[i]} = pRAM_read_HDL(i+32'h8000_0000, 4);
        end
    end


    wire [ADDR_WIDTH-1:0] addr;
    assign addr = vaddr[ADDR_WIDTH-1:0];


reg [31:0] wmask_full;
always@(*)begin
    case(wmask)
        32'd1: begin
            wmask_full = 32'h0000_00FF;
        end
        32'd2:begin 
            wmask_full = 32'h0000_FFFF;
        end
        32'd4: wmask_full = 32'hFFFF_FFFF;
        default: wmask_full = 32'hFFFF_FFFF;
    endcase
end



wire [31:0]wdata_all,rdata_all;
// 获得不会被写入覆盖的内容
assign rdata_all = {rf[addr+3],rf[addr+2],rf[addr+1],rf[addr]} & (~(wmask_full));
assign wdata_all = wdata & (wmask_full);
//读
always @(posedge clk) begin
    if(reqValid)begin
        if(vaddr >= 32'h1000_0000 && vaddr < 32'h1000_1000)begin
            if(wen) pRAM_write_HDL(vaddr,wmask,wdata);
            else if(rden) rdata <= pRAM_read_HDL(vaddr, wmask);
        end else begin
            if(wen) begin 
                {rf[addr+3],rf[addr+2],rf[addr+1],rf[addr]} <= wdata_all | rdata_all;
            end else if(rden) begin
                rdata <= {rf[addr+3], rf[addr+2], rf[addr+1], rf[addr]} ;
            end
        end
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
ysyx_26020055_lfsr uRAM_ysyx_26020055_lfsr (
    .clk            (clk            ),
    .rst            (rst            ),
    .start          (reqReady       ),
    .output_pulse   (respValid_base )
);

ysyx_26020055_lfsr uRAM_reqReady_ysyx_26020055_lfsr (
    .clk            (clk            ),
    .rst            (rst            ),
    .start          (reqValid       ),
    .output_pulse   (reqReady       )
);

endmodule


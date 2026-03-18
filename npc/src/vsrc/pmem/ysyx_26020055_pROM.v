/* verilator lint_off UNDRIVEN */

import "DPI-C" function int pROM_read_HDL(int addr) ;
// ROM 必定按 word 读，直接设置为 32 bit
/*
module ysyx_26020055_pROM #(ADDR_WIDTH = 25, DATA_WIDTH = 32) (
    input                      clk                ,
    input                      rst                ,
    input [31:0]               vaddr              ,
    input                      reqValid           ,
    output reg                 respValid          ,
    input                      respReady          ,
    output                     reqReady           ,
    output reg[DATA_WIDTH-1:0] rdata               
*/
module ysyx_26020055_pROM (
    input               clk         ,
    input               rst         ,
    input        [31:0] wmask       ,  
            /* AXI4-lite */
    /* 读地址操作 */
    input        [31:0] arAddr      ,
    input               arValid     ,
    output reg          arReady     ,
    /* 读数据操作 */
    output reg   [31:0] rData       ,
    output reg          rResp       ,
    output reg          rValid      ,
    input               rReady      ,
    /* 写地址操作 */
    input        [31:0] awAddr      ,
    input               awValid     ,
    output              awReady     ,
    /* 写数据操作 */
    input        [31:0] wData       ,
    input               wValid      ,
    output              wReady      ,
    /* 写回操作 */
    output              bResp       ,
    output              bValid      ,
    input               bReady  
);

// ================== 设置不用的端口为0 ===================== //
// aw ,w ,b 不处理
    assign awReady = 1'b0;
    assign wReady  = 1'b0;
    assign bResp   = 1'b0;
    assign bValid  = 1'b0;
// ======================================================== //

// ==================== 寄存器组 =========================== //
// 32bit 地址， 8bit 单元
    //localparam ADDR_WIDTH = 27;//27: 0x800_0000 大小(128MB)
    localparam ADDR_WIDTH = 10;//27: 0x000_1000 大小(1KB)
    localparam DATA_WIDTH = 8;

    localparam VADDR_INIT = 32'h8000_0000;
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
// 初始化
    initial begin
        for(int i=0;i<2**ADDR_WIDTH-1;i=i+4)begin
            {rf[i+3],rf[i+2],rf[i+1],rf[i]} = pROM_read_HDL(i + VADDR_INIT);
        end
    end
// ======================================================== //


// ======================= 操作mem' ======================== //
// arAddr_reg
// 目前只有一个寄存空间，后续可以使用 fifo 扩展
    reg [31:0] arAddr_reg;
    always@(posedge clk)begin
        if(rst)
            arAddr_reg <= 32'h0;
        else if(arValid && arReady) // 只有握手成功时认为读地址有效
            arAddr_reg <= arAddr;
    end
// 获得物理地址
// 因为只差一个 28bit ，直接截取就可以
    wire [ADDR_WIDTH-1:0] arPaddr;
    assign arPaddr = arAddr_reg[ADDR_WIDTH-1:0];

    reg arAddr_reg_valid; // arAddr_reg 是否有效 
    always@(posedge clk)begin
        if(rst)
            arAddr_reg_valid <= 1'b0;
        else if(arValid && arReady)
            arAddr_reg_valid <= 1'b1;
        else
            arAddr_reg_valid <= 1'b0;
    end

//读
localparam DEVICE_ADDR = 32'h1000_0000;
localparam DEVICE_SIZE = 32'h0000_1000;

always @(posedge clk) begin
    if(arAddr_reg_valid)begin
        // device
        if(arAddr >= DEVICE_ADDR && arAddr < DEVICE_ADDR+DEVICE_SIZE)begin
            rData <= pROM_read_HDL(arAddr);
            rResp <= 2'b00;
        // mem
        end else if(arAddr <= 2**ADDR_WIDTH-4)begin 
            rData <= {rf[arPaddr+3],rf[arPaddr+2],rf[arPaddr+1],rf[arPaddr]};
            rResp <= 2'b00;//有效地址
        end else begin
            rData <= rData;
            rResp <= 2'b10;//无效地址
        end
    end
end

// 随机延迟生成0-31,模拟读出延迟
// rValid 从设备声明数据有效的延迟，从读地址寄存器有效时开始计算
// 这里模拟随机时刻后 mem 成功读出数据，并送到 rData 上，且置 rValid 为 1
    wire rValid_base;
    ysyx_26020055_lfsr uROM_ysyx_26020055_lfsr (
        .clk            (clk             ),
        .rst            (rst             ),
        .start          (arAddr_reg_valid),
        .output_pulse   (rValid_base     )
    );
// ========================== 状态机 ============================//
// 状态机1:for data
localparam IDLE = 2'b00,//待命
           BUSY = 2'b01,//工作中
           WAITREADY = 2'b10;//等待 master 准备完成
reg [1:0] st,n_st;
always@(posedge clk)begin
    if(rst)
        st <= IDLE;
    elsey
        st <= n_st;
end
always@(*)begin
    case(st)
    // 如果收到 master 的有效地址，则开始工作
        IDLE:     begin n_st = (arValid)?BUSY:IDLE;          end
    // 等待自身工作完成
        BUSY:     begin n_st = (rValid_base)?WAITREADY:BUSY; end
    // 自身工作完成后，开始等待 master 工作完成以传输数据
        WAITREADY:begin   n_st = (rReady)?IDLE:WAITREADY;    end
        default : n_st = IDLE;
    endcase
end
// WAITREADY 时自身工作已经完成，输出数据有效，设置 rValid 为 1，并且等待 master 的 READY 信号
    assign rValid  = (st == WAITREADY);

// ============================ //
//状态机2 for addr
localparam ADDR_IDLE = 2'b00,//待命
           ADDR_BUSY = 2'b01,//工作中
           ADDR_WAITREADY = 2'b10;//等待 master 准备完成
reg [1:0] ad_st,ad_n_st;
always@(posedge clk)begin
    if(rst)
        ad_st <= ADDR_IDLE;
    elsey
        ad_st <= ad_n_st;
end
always@(*)begin
    case(ad_st)
    // 如果收到 master 的有效地址，则开始工作
        ADDR_IDLE:     begin ad_n_st = (arValid)?ADDR_BUSY:ADDR_IDLE;          end
    // 模拟消费地址的延迟
        ADDR_BUSY:     begin ad_n_st = (arReady_base)?ADDR_IDLE:ADDR_BUSY;     end
        default : ad_n_st = ADDR_IDLE;
    endcase
end

// IDLE 时自身工作已经完成，等待 master 的有效地址
    assign arReady = (ad_st == ADDR_IDLE);
    wire arReady_base;
// 这里模拟消费地址的延迟
    ysyx_26020055_lfsr uROM_reqReady_ysyx_26020055_lfsr (
        .clk            (clk             ),
        .rst            (rst             ),
        .start          (arAddr_reg_valid),
        .output_pulse   (arReady_base    )
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


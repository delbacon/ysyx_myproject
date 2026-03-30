import "DPI-C" function int pRAM_read_HDL(int addr, int len);
import "DPI-C" function void pRAM_write_HDL(int addr, int len, int data) ;


module ysyx_26020055_pRAM (
    input               clk         ,
    input               rst         ,
            /* AXI4-lite */
    /* 读地址操作 */
    input        [31:0] arAddr      ,
    input               arValid     ,
    output reg          arReady     ,
    /* 读数据操作 */
    output reg   [31:0] rData       ,
    output reg   [ 1:0] rResp       ,
    output reg          rValid      ,
    input               rReady      ,
    /* 写地址操作 */
    input        [31:0] awAddr      ,
    input               awValid     ,
    output              awReady     ,
    /* 写数据操作 */
    input        [31:0] wStrb       ,
    input        [31:0] wData       ,
    input               wValid      ,
    output              wReady      ,
    /* 写回操作 */
    output       [1:0]  bResp       ,
    output              bValid      ,
    input               bReady  
);

// ==================== 寄存器组 =========================== //
// 32bit 地址， 8bit 单元
    //localparam ADDR_WIDTH = 27;//27: 0x800_0000 大小(128MB)
    localparam ADDR_WIDTH = 27;//27: 0x000_1000 大小(1KB)
    localparam DATA_WIDTH = 8;

    localparam VADDR_INIT = 32'h8000_0000;
    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
// 初始化
    initial begin
        for(int i=0;i<2**ADDR_WIDTH-1;i=i+4)begin
            {rf[i+3],rf[i+2],rf[i+1],rf[i]} = pRAM_read_HDL(i + VADDR_INIT,4);
        end
    end
// ========================== 操作mem ============================== //
localparam DEVICE_ADDR = 32'h1000_0000;
localparam DEVICE_SIZE = 32'h0000_1000;
// ========= READ ============ //
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

always @(posedge clk) begin
    if(rdata_success)begin
        // device
        if(arAddr_reg >= DEVICE_ADDR && arAddr_reg < DEVICE_ADDR+DEVICE_SIZE)begin
            rData <= pRAM_read_HDL(arAddr_reg,32'd4);
            rResp <= 2'b00;
        // mem
        end else if(arAddr_reg >= VADDR_INIT && arAddr_reg <= 2**ADDR_WIDTH-4 + VADDR_INIT)begin 
            rData <= {rf[arPaddr+3],rf[arPaddr+2],rf[arPaddr+1],rf[arPaddr]};
            rResp <= 2'b00;//有效地址
        end else begin
            rData <= 'h80000000;
            rResp <= 2'b10;//无效地址
        end
    end
end

// 随机延迟生成0-31,模拟读出延迟
// rValid 从设备声明数据有效的延迟，从读地址寄存器有效时开始计算
// 这里模拟随机时刻后 mem 成功读出数据，并送到 rData 上，且置 rValid 为 1
    wire rdata_success;
    ysyx_26020055_lfsr urRAM_ysyx_26020055_lfsr (
        .clk            (clk               ),
        .rst            (rst               ),
        .start          (arValid && arReady),
        .output_pulse   (rdata_success     )
    );
// ========================= //


// ========= WRITE ============ //
//要求地址和数据同时握手
//wData_reg
    reg [31:0] wData_reg;
// awAddr_reg
// 目前只有一个寄存空间，后续可以使用 fifo 扩展
    reg [31:0] awAddr_reg;

    wire write_handshake = awValid && awReady && wValid && wReady;
    always@(posedge clk)begin
        if(rst)begin
            awAddr_reg <= 32'h0;
        end else if(write_handshake)begin // 只有握手成功时认为写地址有效
            awAddr_reg <= awAddr;
            wData_reg <= wData;
        end
    end
// 获得物理地址
// 因为只差一个 28bit ，直接截取就可以
    wire [ADDR_WIDTH-1:0] awPaddr;
    assign awPaddr = awAddr_reg[ADDR_WIDTH-1:0];

    reg [31:0] wmask;
    always@(*)begin
        case(wStrb)
            32'h0000_00FF: wmask = 32'd1;
            32'h0000_FFFF: wmask = 32'd2;
            32'hFFFF_FFFF: wmask = 32'd4;
            default:       wmask = 32'd4;
        endcase
    end


    wire [31:0]wdata_all,rdata_all;
    // 获得不会被写入覆盖的内容
    assign rdata_all = {rf[awPaddr+3],rf[awPaddr+2],rf[awPaddr+1],rf[awPaddr]} & (~(wStrb));
    assign wdata_all = wData_reg & (wStrb);
    //读
    always @(posedge clk) begin
        if(wdata_success)begin
            if(awAddr_reg >= DEVICE_ADDR && awAddr_reg < DEVICE_ADDR+DEVICE_SIZE)begin
                pRAM_write_HDL(awAddr_reg,wmask,wData_reg);
            end else if(awAddr_reg >= VADDR_INIT && awAddr_reg <= 2**ADDR_WIDTH-4 + VADDR_INIT)begin 
                {rf[awPaddr+3],rf[awPaddr+2],rf[awPaddr+1],rf[awPaddr]} <= wdata_all | rdata_all;
            end else begin
                // do nothing
            end
        end
    end


// 随机延迟生成0-31,模拟读出延迟
// rValid 从设备声明数据有效的延迟，从读地址寄存器有效时开始计算
// 这里模拟随机时刻后 mem 成功读出数据，并送到 rData 上，且置 rValid 为 1
    wire wdata_success;
    ysyx_26020055_lfsr uwRAM_ysyx_26020055_lfsr (
        .clk            (clk               ),
        .rst            (rst               ),
        .start          (write_handshake   ),
        .output_pulse   (wdata_success     )
    );
// ========================= //

// ========================== 状态机 ============================//
// 状态机1:for read
localparam IDLE = 2'b00,//待命
           BUSY = 2'b01,//工作中
           WAITREADY = 2'b11;//等待 master 准备完成
reg [1:0] st,n_st;
always@(posedge clk)begin
    if(rst)
        st <= IDLE;
    else
        st <= n_st;
end
always@(*)begin
    case(st)
    // 如果收到 master 的有效地址，则开始工作
        IDLE:     begin n_st = (arValid && arReady)?BUSY:IDLE;     end
    // 等待读取数据
        BUSY:     begin n_st = (rdata_success)?WAITREADY:BUSY; end
    // 等待 master 工作完成以传输数据
        WAITREADY:begin   n_st = (rReady)?IDLE:WAITREADY;    end
        default : n_st = IDLE;
    endcase
end
// WAITREADY 时自身工作已经完成，输出数据有效，设置 rValid 为 1，并且等待 master 的 READY 信号
    assign rValid  = (st == WAITREADY);
// IDLE 时自身工作已经完成，等待 master 的有效地址
    assign arReady = (st == IDLE);


// 状态机2:for write
localparam AWIDLE = 2'b00,//待命
           AWBUSY = 2'b01,//工作中
           AWVALID = 2'b11;//等待 master 准备完成
reg [1:0] awst,awn_st;
always@(posedge clk)begin
    if(rst)
        awst <= AWIDLE;
    else
        awst <= awn_st;
end
always@(*)begin
    case(awst)
    // 如果收到 master 的有效地址，则开始工作
        AWIDLE:     begin awn_st = (write_handshake)?AWBUSY:AWIDLE;     end
    // 等待写数据
        AWBUSY:     begin awn_st = (wdata_success)?AWVALID:AWBUSY; end
    // 等待 master 工作完成以传输地址
        AWVALID:begin   awn_st = (bReady)?AWIDLE:AWVALID;    end
        default : awn_st = AWIDLE;
    endcase
end
// WAITREADY 时自身工作已经完成，输出数据有效，设置 rValid 为 1，并且等待 master 的 READY 信号
    assign awReady = (awst == AWIDLE);
    assign wReady  = (awst == AWIDLE);
    assign bValid  = (awst == AWVALID);

//暂时没有实现相关接受功能，所以默认为00
assign bResp = 2'b00;
endmodule


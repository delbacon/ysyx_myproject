

module ysyx_26020055_LSU(
    input              clk       ,
    input              rst       ,
    input       [31:0] exu_out   ,//addr 来源
    input       [31:0] src2      ,//wdata 来源
    input       [ 2:0] mem_op    ,
    input              mem_wen   ,
    input              mem_toreg ,
 
    output reg [31:0] mem_rdata  ,
    input             exu_valid  ,
    output            lsu_valid  ,
    input             wbu_ready  ,

/* AXI4-lite ports */
    /* 读地址操作 */
    output [31:0]     lsu_arAddr ,
    output            lsu_arValid,
    input             lsu_arReady,
    /* 读数据操作 */                        
    input  [31:0]     lsu_rData  ,
    /* verilator lint_off UNUSEDSIGNAL */ 
    input  [1:0]      lsu_rResp  ,
    input             lsu_rValid ,
    output            lsu_rReady ,
    /* 写地址操作 */                      
    output [31:0]     lsu_awAddr ,
    output            lsu_awValid,
    input             lsu_awReady,
    /* 写数据操作 */ 
    output reg [31:0] lsu_wStrb  ,                     
    output [31:0]     lsu_wData  ,
    output            lsu_wValid ,
    input             lsu_wReady ,
    /* 写回操作 */              
    /* verilator lint_off UNUSEDSIGNAL */      
    input  [1:0]      lsu_bResp  ,
    input             lsu_bValid ,
    output            lsu_bReady 
);

// ============================ 主状态机 ===============================//
localparam  READ_IDLE = 'd0,
            READ_WAITADDR = 'd1,
            READ_WAITDATA = 'd2;

    localparam IDLE = 2'b00, WAIT_WRITE = 2'b01,WAIT_READ = 2'b10, BUSY = 2'b11;
    reg [1:0]st,n_st;
    always@(posedge clk)begin
        if(rst)
            st <= IDLE;
        else
            st <= n_st;
    end
    //wait 等待 wbu 完成
    always@(*)begin
        case(st)
            // 如果有请求与 mem 交互的信号，就等待 mem 执行完毕
            IDLE:begin 
                if(exu_valid)begin
                    if(mem_wen) n_st = WAIT_WRITE;
                    else if(mem_toreg) n_st = WAIT_READ;
                    else n_st = IDLE;
                end else n_st = IDLE;
            end
            // 向 ROM 发出请求，并等待 RAM 执行完成(进入 MEM_IDLE 状态)
            WAIT_WRITE:  begin n_st = (wrmem_st == WRITE_SUCCESS && lsu_bValid)?BUSY:WAIT_WRITE; end
            // 读取数据
            WAIT_READ:  begin n_st = (rom_st == READ_WAITDATA && lsu_rValid)?BUSY:WAIT_READ; end
            // 等待下一个模块执行完成
            BUSY:     begin n_st = (wbu_ready)?IDLE:BUSY;   end
            default : n_st = IDLE;
        endcase
    end

assign lsu_valid = (st == BUSY) || (st == IDLE && (exu_valid && ~(mem_wen || mem_toreg) ));
// =================================================================//

// ============== RAM 状态机 ====================//
// 用于和 RAM 交互
// read
reg [1:0]rom_st,rom_n_st;
always@(posedge clk)begin
    if(rst)
        rom_st <= READ_IDLE;
    else
        rom_st <= rom_n_st;
end
always@(*)begin
    case(rom_st)
        // 如果主状态机开始等待 mem 执行
        READ_IDLE: begin rom_n_st = (st == WAIT_READ)?READ_WAITADDR:READ_IDLE; end
        // 等待 ROM 不忙，可以响应 IFU 的请求（reqReady），期间一直向 mem 发出读请求(ifu_reqValid)
        READ_WAITADDR: begin rom_n_st = (lsu_arReady)?READ_WAITDATA:READ_WAITADDR; end
        // 等待 ROM 取完毕
        READ_WAITDATA: begin rom_n_st = (lsu_rValid)?READ_IDLE:READ_WAITDATA; end
    endcase
end

assign lsu_arValid = (rom_st == READ_WAITADDR);
assign lsu_rReady = (rom_st == READ_WAITDATA);
assign lsu_arAddr = mem_addr;
assign mem_rdata_raw = lsu_rData;
//write
localparam  WRITE_IDLE = 'd0,
            WRITE_WAIT = 'd1,
            WRITE_SUCCESS = 'd2;
reg [1:0]wrmem_st,wrmem_n_st;
always@(posedge clk)begin
    if(rst)
        wrmem_st <= WRITE_IDLE;
    else
        wrmem_st <= wrmem_n_st;
end
always@(*)begin
    case(wrmem_st)
        // 如果主状态机开始等待 mem 执行
        WRITE_IDLE: begin wrmem_n_st = (st == WAIT_WRITE)?WRITE_WAIT:WRITE_IDLE; end
        // 等待 RAM 不忙，可以响应 IFU 的请求（reqReady），期间一直向 mem 发出读请求(ifu_reqValid)
        WRITE_WAIT: begin wrmem_n_st = (lsu_awReady && lsu_wReady)?WRITE_SUCCESS:WRITE_WAIT; end
        // 等待写回信号
        WRITE_SUCCESS: begin wrmem_n_st = (lsu_bValid)?WRITE_IDLE:WRITE_SUCCESS; end
    endcase
end

assign lsu_awValid = (wrmem_st == WRITE_WAIT);
assign lsu_wValid = (wrmem_st == WRITE_WAIT);
assign lsu_wData = mem_wdata;
assign lsu_awAddr = mem_addr;
assign lsu_bReady = (wrmem_st == WRITE_SUCCESS);
// ==========================================//


 //mem_op
    localparam MEM_OP_SIGNED_BYTE   = 3'b000,
               MEM_OP_SIGNED_HALF   = 3'b001,
               MEM_OP_WORD          = 3'b010,
               MEM_OP_UNSIGNED_BYTE = 3'b100,
               MEM_OP_UNSIGNED_HALF = 3'b101;

//mem_rdata
    reg [31:0] mem_rdata_raw;
    always@(*)begin
        case(mem_op)
            MEM_OP_SIGNED_BYTE:begin
                mem_rdata = {{24{mem_rdata_raw[7]}}, mem_rdata_raw[7:0]};
            end
            MEM_OP_SIGNED_HALF:begin
                mem_rdata = {{16{mem_rdata_raw[15]}}, mem_rdata_raw[15:0]};
            end
            MEM_OP_WORD:
                mem_rdata = mem_rdata_raw;
            MEM_OP_UNSIGNED_BYTE:begin
                mem_rdata = {24'b0, mem_rdata_raw[7:0]};

            end
            MEM_OP_UNSIGNED_HALF:begin
                mem_rdata = {16'b0, mem_rdata_raw[15:0]};
            end
            default:
                mem_rdata = mem_rdata_raw;
        endcase   
    end
//lsu_wStrb
    always@(*)begin
        case(mem_op)
            MEM_OP_SIGNED_BYTE,MEM_OP_UNSIGNED_BYTE:
                lsu_wStrb =  32'h0000_00FF;
            MEM_OP_SIGNED_HALF,MEM_OP_UNSIGNED_HALF:
                lsu_wStrb =  32'h0000_FFFF;
            MEM_OP_WORD:
                lsu_wStrb = 32'hFFFF_FFFF;
            default:
                lsu_wStrb = 32'hFFFF_FFFF;
        endcase   
    end

    wire [31:0] mem_wdata;
    assign mem_wdata = src2;
    wire [31:0] mem_addr;
    assign mem_addr = exu_out;

endmodule

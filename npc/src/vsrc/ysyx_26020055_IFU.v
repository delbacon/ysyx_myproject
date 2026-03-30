import "DPI-C" function void pc_get_HDL(int val) ;

import "DPI-C" function void dnpc_get_HDL(int val) ;
module ysyx_26020055_IFU (
    input            clk          ,
    input            rst          ,
    output reg[31:0] pc           ,
    input            branch_flag  ,
    input     [31:0] branch_target,
    output    [31:0] inst         ,
    output reg       ifu_valid    ,
    input            wbu_ready    ,   // wbu 执行完毕代表IFU 处理完毕自身事务，当前指令成功执行，可以接收下一条指令了 

/* AXI4-lite ports */
    /* 读地址操作 */
    output [31:0]     ifu_arAddr ,
    output            ifu_arValid,
    input             ifu_arReady,
    /* 读数据操作 */                        
    input  [31:0]     ifu_rData  ,
    /* verilator lint_off UNUSEDSIGNAL */ 
    input  [1:0]      ifu_rResp  ,
    input             ifu_rValid ,
    output            ifu_rReady ,
    /* 写地址操作 */                      
    output [31:0]     ifu_awAddr ,
    output            ifu_awValid,
    input             ifu_awReady,
    /* 写数据操作 */ 
    output reg [31:0] ifu_wStrb  ,                     
    output [31:0]     ifu_wData  ,
    output            ifu_wValid ,
    input             ifu_wReady ,
    /* 写回操作 */              
    /* verilator lint_off UNUSEDSIGNAL */      
    input  [1:0]      ifu_bResp  ,
    input             ifu_bValid ,
    output            ifu_bReady 

);


assign ifu_awAddr  = 'd0;
assign ifu_awValid = 'd0;
assign ifu_wStrb   = 'd0;
assign ifu_wData   = 'd0;
assign ifu_wValid  = 'd0;
assign ifu_bReady  = 'd0;
// ========================== 主 状态机 ============================//
// 用于控制 IFU 状态，分为等待 MEM 完成和等待 WBU 完成(即最近发送的指令被执行完)
    localparam WAITMEM = 2'b01,BUSY = 2'b10;
    reg [1:0]st,n_st;
    always@(posedge clk)begin
        if(rst)
            st <= WAITMEM;
        else
            st <= n_st;
    end
    //wait 等待 wbu 完成
    always@(*)begin
        case(st)
            // 向 ROM 发出请求，并等待 ROM 取指完成(进入 MEM_IDLE 状态)
            WAITMEM:  begin n_st = (mem_ready)?BUSY:WAITMEM; end
            // 等待当前 inst 执行完成
            BUSY:     begin n_st = (wbu_ready)?WAITMEM:BUSY;   end
            default : n_st = WAITMEM;
        endcase
    end

// 从仿真环境中读取 ROM ，获得执行的指令
localparam PC_INIT = 32'h8000_0000;
// 判断从mem取指是否完
wire mem_ready;
//assign mem_ready = rom_done;
assign mem_ready = (rom_st == MEM_WAITDATA && ifu_rValid);
// 如果取指完成，取出的指令
assign inst = mem_ready?ifu_rData:32'b0;
// 此时 ifu 工作完成，inst和pc有效
assign ifu_valid = mem_ready && (st == WAITMEM);
assign ifu_arAddr = pc;
// =============================================================//

// ============== ROM 状态机 ====================//
// 用于和 ROM 交互
localparam  MEM_IDLE = 'd1,
            MEM_WAITADDR = 'd2,
            MEM_WAITDATA = 'd3;
reg [1:0]rom_st,rom_n_st;
always@(posedge clk)begin
    if(rst)
        rom_st <= MEM_IDLE;
    else
        rom_st <= rom_n_st;
end
always@(*)begin
    case(rom_st)
        // 如果主状态机开始等待 mem 执行
        MEM_IDLE: begin rom_n_st = (st == WAITMEM)?MEM_WAITADDR:MEM_IDLE; end
        // 等待 ROM 识别地址,此时地址有效
        MEM_WAITADDR:begin rom_n_st = (ifu_arReady)?MEM_WAITDATA:MEM_WAITADDR;end
        // 等待 ROM 读取数据。此时数据有效
        MEM_WAITDATA:begin rom_n_st = (ifu_rValid)?MEM_IDLE:MEM_WAITDATA; end
        default: begin rom_n_st = MEM_IDLE; end
    endcase
end

assign ifu_arValid = (rom_st == MEM_WAITADDR);

// wait data 时一直置 1 ，表示准备好接收数据
assign ifu_rReady = (rom_st == MEM_WAITDATA);


// ======================== PC 寄存器更新 ============================//
//如果跳转的话，更新pc为branch_target
    wire [31:0] next_pc ;
    assign next_pc = branch_flag ? branch_target : pc + 4; 

always @(posedge clk) begin
    if (rst) begin
        pc <= PC_INIT;
    end else if(mem_ready)begin
        pc <= next_pc; // 正常更新
    end
end

// DPI-C 向仿真环境传输数据
    always@(posedge clk)begin
        if(ifu_valid)begin
            dnpc_get_HDL(next_pc);
            pc_get_HDL(next_pc);
        end
    end

endmodule

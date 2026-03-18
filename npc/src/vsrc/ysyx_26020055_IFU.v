
import "DPI-C" function void inst_get_HDL(int vraddr) ;
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
    input            wbu_ready       // wbu 执行完毕代表IFU 处理完毕自身事务，当前指令成功执行，可以接收下一条指令了 
);
// ========================== 主 状态机 ============================//
// 用于控制 IFU 状态，分为等待 MEM 完成和等待 WBU 完成(即最近发送的指令被执行完)
    localparam IDLE = 2'b00, WAITMEM = 2'b01,BUSY = 2'b10;
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
            IDLE:     begin n_st = WAITMEM; end
            // 向 ROM 发出请求，并等待 ROM 取指完成(进入 MEM_IDLE 状态)
            WAITMEM:  begin n_st = (mem_ready)?BUSY:WAITMEM; end
            // 等待当前 inst 执行完成
            BUSY:     begin n_st = (wbu_ready)?WAITMEM:BUSY;   end
            default : n_st = WAITMEM;
        endcase
    end

// 从仿真环境中读取 ROM ，获得执行的指令
localparam PC_INIT = 32'h8000_0000;
reg [31:0] ifu_data,ifu_addr;
// 判断从mem取指是否完成
wire mem_ready;
assign mem_ready = (rom_st == MEM_BUSY && ifu_respValid);
// 如果取指完成，取出的指令
assign inst = mem_ready?ifu_rData:32'b0;
// 此时 ifu 工作完成，inst和pc有效
assign ifu_valid = mem_ready;
assign ifu_addr = pc;

// 收到 wbu_ready 代表指令执行完成
assign ifu_respReady = (st==BUSY) && wbu_ready;
// =============================================================//

reg rst_ready;
always@(posedge clk)begin
    rst_ready <= rst;
end


// ============== ROM 状态机 ====================//
// 用于和 ROM 交互
// addr 状态机
localparam  MEM_IDLE = 'd0,
            MEM_WAIT = 'd1,
            MEM_BUSY = 'd2;
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
        MEM_IDLE: begin rom_n_st = (st == WAITMEM)?MEM_WAIT:MEM_IDLE; end
        // 等待 ROM 取完毕
        MEM_BUSY:begin rom_n_st = (ifu_respValid)?MEM_IDLE:MEM_BUSY;end
    endcase
end

// data 状态机
localparam  MEM_IDLEDATA = 'd0,
            MEM_WAITDATA = 'd1;
reg [1:0]data_st,data_n_st;
always@(posedge clk)begin
    if(rst)
        data_st <= MEM_IDLEDATA;
    else
        data_st <= data_n_st;
end
always@(*)begin
    case(data_st)
        // 如果主状态机开始等待 mem 执行
        MEM_IDLEDATA: begin rom_n_st = (st == WAITMEM)?MEM_WAITDATA:MEM_IDLEDATA; end
        // 等待 ROM 不忙，可以响应 IFU 的请求（reqReady），期间一直向 mem 发出读请求(ifu_reqValid)
        MEM_WAITDATA: begin rom_n_st = (ifu_rValid)?MEM_IDLEDATA:MEM_WAITDATA; end
    endcase
end
// wait data 时一直置 1 ，表示准备好接收数据
assign ifu_rReady = (st==MEM_WAITDATA);
assign ifu_reqValid = (rst_ready)?1:(rom_st == MEM_WAIT);

reg [31:0] ifu_arAddr  ;
wire ifu_arValid       ;
wire ifu_arReady       ;
reg [31:0] ifu_rData   ;
wire ifu_rResp         ;
wire ifu_rValid        ;
wire ifu_rReady        ;

ysyx_26020055_pROM u_ysyx_26020055_pROM (
    .clk        (clk           ),
    .rst        (rst           ),
    .wmask      (32'd0         ),  
    .arAddr     (ifu_arAddr    ),
    .arValid    (ifu_arValid   ),
    .arReady    (ifu_arReady   ),
    .rData      (ifu_rData     ),
    .rResp      (ifu_rResp     ),
    .rValid     (ifu_rValid    ),
    .rReady     (ifu_rReady    ),

    .awAddr     (32'd0         ),
    .awValid    (1'd0          ),
    .awReady    (              ),
       
    .wData      (32'd0         ),
    .wValid     (1'd0          ),
    .wReady     (              ),
       
    .bResp      (              ),
    .bValid     (              ),
    .bReady     (1'd0          )
);
/* simple-bus
Master:
output        ifu_reqValid,
input         ifu_reqReady,
output [31:0] ifu_addr,
output        ifu_wen,
output [31:0] ifu_wdata,
output [ 3:0] ifu_wmask,
input         ifu_respValid,
output        ifu_respReady,
input  [31:0] ifu_rdata,

ysyx_26020055_pROM u_ysyx_26020055_pROM (
    .clk            (clk          ) ,
    .rst            (rst          ) ,
    .reqValid       (ifu_reqValid ) ,
    .reqReady       (ifu_reqReady ) ,
    .vaddr          (ifu_addr     ) ,
//  .ifu_wen        (ifu_wen      ) ,
//  .ifu_wdata      (ifu_wdata    ) ,
//  .ifu_wmask      (ifu_wmask    ) ,
    .respValid      (ifu_respValid) ,
    .respReady      (ifu_respReady) ,
    .rdata          (ifu_data     )       
);
*/


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
        dnpc_get_HDL(next_pc);
        pc_get_HDL(pc);
        inst_get_HDL(inst);
    end

endmodule



module ysyx_26020055_LSU(
    input clk,
    input rst,
    input       [31:0] exu_out  ,//addr 来源
    input       [31:0] src2     ,//wdata 来源
    input       [ 2:0] mem_op   ,
    input              mem_wen  ,
    input              mem_toreg,

    output reg [31:0] mem_rdata ,
    input             exu_valid ,
    output            lsu_valid ,
    input             wbu_ready
);
    
    wire lsu_respValid,lsu_reqValid;
    wire lsu_respReady,lsu_reqReady;

// ============================ 主状态机 ===============================//
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
            IDLE:     begin n_st = (exu_valid &&(mem_wen || mem_toreg))?WAITMEM:IDLE; end
            // 向 ROM 发出请求，并等待 ROM 取指完成(进入 MEM_IDLE 状态)
            WAITMEM:  begin n_st = (mem_ready)?BUSY:WAITMEM; end
            // 等待下一个模块执行完成
            BUSY:     begin n_st = (wbu_ready)?IDLE:BUSY;   end
            default : n_st = IDLE;
        endcase
    end

// 判断从mem取指是否完成
wire mem_ready;
assign mem_ready = (rom_st == MEM_BUSY && lsu_respValid);
assign lsu_respReady = (st==BUSY) && wbu_ready;
// 只有等待 mem 完成时，相关信号才使能有效
reg lsu_wen,lsu_rden;
wire mem_req = (rom_st == MEM_IDLE && (st == WAITMEM));
always@(posedge clk)begin
    if(mem_req && mem_wen)begin
        lsu_wen <= 1'd1;
    end else begin
        lsu_wen <= 1'b0;
    end
end
always@(posedge clk)begin
    if(mem_req && mem_toreg)begin
        lsu_rden <= 1'd1;
    end else begin
        lsu_rden <= 1'b0;
    end
end

assign lsu_valid = ( mem_ready ) || ((st == IDLE) && exu_valid && ~(mem_wen || mem_toreg));
// =================================================================//

// ============== ROM 状态机 ====================//
// 用于和 ROM 交互
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
        // 等待 ROM 不忙，可以响应 IFU 的请求（reqReady），期间一直向 mem 发出读请求(ifu_reqValid)
        MEM_WAIT: begin rom_n_st = (lsu_reqReady)?MEM_BUSY:MEM_WAIT; end
        // 等待 ROM 取完毕
        MEM_BUSY:begin rom_n_st = (lsu_respValid)?MEM_IDLE:MEM_BUSY;end
    endcase
end

assign lsu_reqValid = mem_req || (rom_st == MEM_WAIT);
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
//mem_len
    reg [31:0] mem_len;
    always@(*)begin
        case(mem_op)
            MEM_OP_SIGNED_BYTE,MEM_OP_UNSIGNED_BYTE:
                mem_len = 32'd1;
            MEM_OP_SIGNED_HALF,MEM_OP_UNSIGNED_HALF:
                mem_len = 32'd2;
            MEM_OP_WORD:
                mem_len = 32'd4;
            default:
                mem_len = 32'd0;
        endcase   
    end


    wire [31:0] mem_wdata;
    assign mem_wdata = src2;
    wire [31:0] mem_addr;
    assign mem_addr = exu_out;


ysyx_26020055_pRAM u_ysyx_26020055_pRAM  (
    .clk                 (clk               ),
    .rst                 (rst               ),
    .vaddr               (mem_addr          ),
    .reqValid            (lsu_reqValid      ),
    .respValid           (lsu_respValid     ),
    .respReady           (lsu_respReady     ),
    .reqReady            (lsu_reqReady      ),
    .rdata               (mem_rdata_raw     ),
    .wdata               (mem_wdata         ),
    .wen                 (lsu_wen           ),
    .rden                (lsu_rden          ),
    .wmask               (mem_len           )                    
);

endmodule

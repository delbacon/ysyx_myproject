// 三段式状态机引入一拍延迟
// 输出信号寄存引入一拍延迟

module ysyx_26020055_mem_arbiter (

    input               clk             ,
    input               rst             ,

            /* AXI4-lite for CH0*/
    /* 读地址操作 */
    input        [31:0] ch0_arAddr      ,
    input               ch0_arValid     ,
    output reg          ch0_arReady     ,
    /* 读数据操作 */
    output reg   [31:0] ch0_rData       ,
    output reg   [ 1:0] ch0_rResp       ,
    output reg          ch0_rValid      ,
    input               ch0_rReady      ,
    /* 写地址操作 */
    input        [31:0] ch0_awAddr      ,
    input               ch0_awValid     ,
    output              ch0_awReady     ,
    /* 写数据操作 */
    input        [31:0] ch0_wStrb       ,  
    input        [31:0] ch0_wData       ,
    input               ch0_wValid      ,
    output              ch0_wReady      ,
    /* 写回操作 */
    output       [ 1:0] ch0_bResp       ,
    output              ch0_bValid      ,
    input               ch0_bReady      ,

            /* AXI4-lite for CH1*/
    /* 读地址操作 */
    input        [31:0] ch1_arAddr      ,
    input               ch1_arValid     ,
    output reg          ch1_arReady     ,
    /* 读数据操作 */
    output reg   [31:0] ch1_rData       ,
    output reg   [ 1:0] ch1_rResp       ,
    output reg          ch1_rValid      ,
    input               ch1_rReady      ,
    /* 写地址操作 */
    input        [31:0] ch1_awAddr      ,
    input               ch1_awValid     ,
    output              ch1_awReady     ,
    /* 写数据操作 */
    input        [31:0] ch1_wStrb       ,  
    input        [31:0] ch1_wData       ,
    input               ch1_wValid      ,
    output              ch1_wReady      ,
    /* 写回操作 */
    output       [ 1:0] ch1_bResp       ,
    output              ch1_bValid      ,
    input               ch1_bReady  
);

// 这里使用轮询避免饿死，同时请求时总是优先 ch0 的请求
// 但是中途如果有ch1的请求，执行完毕后会直接跳转去执行ch1

wire ch0_Req,ch1_Req;
// 如果我请求读地址或者写地址
assign ch0_Req = ch0_arValid || ch0_awValid ;
assign ch1_Req = ch1_arValid || ch1_awValid ;

localparam ARB_CH0 = 'd0,ARB_CH0_SUCCESS = 'd1,ARB_CH1 ='d2,ARB_CH1_SUCCESS = 'd3;
reg [1:0]st,n_st;
always@(posedge clk)begin
    if(rst)
        st <= ARB_CH0_SUCCESS;
    else
        st <= n_st;
end

always@(*)begin
    case(st)
        //正常工作，结束后跳转回IDLE。如果有CH1的请求，直接跳去执行CH1
        ARB_CH0:begin
            n_st = (rd_success || wr_success)?ARB_CH0_SUCCESS:ARB_CH0; 
        end
        ARB_CH0_SUCCESS:begin
            if(ch1_Req)
                n_st = ARB_CH1;
            else if(ch0_Req)
                n_st = ARB_CH0;
            else
                n_st = ARB_CH0_SUCCESS;
        end
        ARB_CH1:begin
            n_st = (rd_success || wr_success)?ARB_CH1_SUCCESS:ARB_CH1; 
        end
        ARB_CH1_SUCCESS:begin
            if(ch0_Req)
                n_st = ARB_CH0;
            else if(ch1_Req)
                n_st = ARB_CH1;
            else
                n_st = ARB_CH1_SUCCESS;   
        end
        default:begin   n_st = ARB_CH0_SUCCESS;    end
    endcase
end


reg [31:0]  arAddr ;
reg         arValid;
wire        arReady;
wire[31:0]  rData  ;
wire[1:0]   rResp  ;
wire        rValid ;
reg         rReady ;
reg [31:0]  awAddr ;
reg         awValid;
wire        awReady;
reg [31:0]  wStrb  ;
reg [31:0]  wData  ;
reg         wValid ;
wire        wReady ;
wire[1:0]   bResp  ;
wire        bValid ;
reg         bReady ;

// 大型连线现场
always@(*)begin
    case(st)
        ARB_CH0,ARB_CH0_SUCCESS:begin
            arAddr  = ch0_arAddr ;arValid = ch0_arValid;ch0_arReady = arReady;
            ch0_rData   = rData  ;ch0_rResp   = rResp  ;ch0_rValid  = rValid ;rReady  = ch0_rReady ;
            awAddr  = ch0_awAddr ;awValid = ch0_awValid;ch0_awReady = awReady;
            wStrb   = ch0_wStrb  ;wData   = ch0_wData  ;wValid  = ch0_wValid ;ch0_wReady  = wReady ;
            ch0_bResp   = bResp  ;ch0_bValid  = bValid ;bReady  = ch0_bReady ;
            
            ch1_arReady = 'd0;ch1_awReady = 'd0;
            ch1_rData   = 'd0  ;ch1_rResp   = 'd0  ;ch1_rValid  = 'd0 ;
            ch1_wReady  = 'd0 ;
            ch1_bResp   = 'd0  ;ch1_bValid  = 'd0 ;

        end
        ARB_CH1,ARB_CH1_SUCCESS:begin
            arAddr  = ch1_arAddr ;arValid = ch1_arValid;ch1_arReady = arReady;
            ch1_rData   = rData  ;ch1_rResp   = rResp  ;ch1_rValid  = rValid ;rReady  = ch1_rReady ;
            awAddr  = ch1_awAddr ;awValid = ch1_awValid;ch1_awReady = awReady;
            wStrb   = ch1_wStrb  ;wData   = ch1_wData  ;wValid  = ch1_wValid ;ch1_wReady  = wReady ;
            ch1_bResp   = bResp  ;ch1_bValid  = bValid ;bReady  = ch1_bReady ;

            ch0_arReady = 'd0;ch0_awReady = 'd0;
            ch0_rData   = 'd0;ch0_rResp   = 'd0  ;ch0_rValid  = 'd0 ;
            ch0_wReady  = 'd0;
            ch0_bResp   = 'd0;ch0_bValid  = 'd0 ;
        end
        default:begin
            arAddr  = 'd0 ;arValid = 'd0;
            rReady  = 'd0 ;
            awAddr  = 'd0 ;awValid = 'd0;ch1_awReady = 'd0;
            wStrb   = 'd0  ;wData   = 'd0  ;wValid  = 'd0 ;
            bReady  = 'd0 ;

            ch0_arReady = 'd0;ch0_awReady = 'd0;
            ch0_rData   = 'd0;ch0_rResp   = 'd0  ;ch0_rValid  = 'd0 ;
            ch0_wReady  = 'd0;
            ch0_bResp   = 'd0;ch0_bValid  = 'd0 ;

            ch1_arReady = 'd0;ch1_awReady = 'd0;
            ch1_rData   = 'd0;ch1_rResp   = 'd0  ;ch1_rValid  = 'd0 ;
            ch1_wReady  = 'd0;
            ch1_bResp   = 'd0;ch1_bValid  = 'd0 ;
        end
    endcase
end


// 写完成和读完成的情况，用来控制主状态机转移回 IDLE 状态
wire rd_success,wr_success;
assign rd_success = rValid && rReady;
assign wr_success = bValid && bReady;

ysyx_26020055_pRAM u_ysyx_26020055_pRAM (
    .clk        (clk           ),
    .rst        (rst           ),

    .arAddr     (arAddr        ),
    .arValid    (arValid       ),
    .arReady    (arReady       ),
    .rData      (rData         ),
    .rResp      (rResp         ),
    .rValid     (rValid        ),
    .rReady     (rReady        ),
    .awAddr     (awAddr        ),
    .awValid    (awValid       ),
    .awReady    (awReady       ),
    .wStrb      (wStrb         ),  
    .wData      (wData         ),
    .wValid     (wValid        ),
    .wReady     (wReady        ),
    .bResp      (bResp         ),
    .bValid     (bValid        ),
    .bReady     (bReady        )
);

endmodule

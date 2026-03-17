//npc/vsrc/ysyx_26020055_WBU.v
module ysyx_26020055_WBU (
    input         clk          ,
    input         rst          ,
    input  [4:0]  rs1          ,
    input  [4:0]  rs2          ,
    input  [4:0]  rd           ,
    //alu & mem                     
    input  [31:0] exu_out      ,
    input  [31:0] mem_rdata    ,
    input         reg_wen      ,
    input         mem_toreg    ,
    //output                      
    output [31:0] src1         ,
    output [31:0] src2         ,
    /* verilator lint_off UNUSEDSIGNAL */
    input         exu_valid    ,
    output reg    wbu_ready    ,
    input         lsu_valid    
);
    localparam IDLE=2'b00,WAITREG=2'b10;
    reg [1:0] st,n_st;
    always@(posedge clk)begin
        if(rst)begin
            st <= IDLE;
        end
        else begin
            st <= n_st;
        end
    end

    always@(*)begin
        case(st)
            IDLE :begin n_st = (lsu_valid) ? WAITREG : IDLE; end
            WAITREG :begin n_st = IDLE; end
            default: begin n_st = IDLE; end
        endcase
    end

    wire wbu_wen;
    assign wbu_wen = (st == WAITREG) && reg_wen;

    wire wbu_toreg;
    assign wbu_toreg =  (st == WAITREG) && mem_toreg;

    assign wbu_ready = (rst) ? 1 : (st==WAITREG);


    reg [31:0]reg_wdata;
    //wen & mux2to1
    always@(*)begin
        if(wbu_wen)begin
            if(wbu_toreg)begin
                reg_wdata = mem_rdata;
            end else begin
                reg_wdata = exu_out;
            end
        end else begin
            reg_wdata = 32'b0;
        end
    end

ysyx_26020055_RegisterFile u_RegisterFile (
    .clk   (clk      ),
    .wdata (reg_wdata),
    .waddr (rd       ),
    .raddr1(rs1      ),
    .raddr2(rs2      ),
    .rdata1(src1     ),
    .rdata2(src2     ),
    .wen   (wbu_wen  ) 
);

    
endmodule




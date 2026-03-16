//npc/vsrc/ysyx_26020055_WBU.v
module ysyx_26020055_WBU (
    input         clk          ,
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
    output reg    wbu_ready     
);
    wire wbu_wen;
    assign wbu_wen = exu_valid && reg_wen;



    always@(posedge clk)begin
        wbu_ready <= exu_valid;
    end


    reg [31:0]reg_wdata;
    //wen & mux2to1
    always@(*)begin
        if(wbu_wen)begin
            if(mem_toreg)begin
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




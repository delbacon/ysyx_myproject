module ysyx_26020055_ExceptionCtrl(
    input              clk    ,
    input              rst    ,
    input       [31:0]  pc    ,
    input       [11:0] imm    ,
    input              csr_wen,
    input       [ 2:0] csr_op ,
    input       [31:0] ex_csr_wdata,
    output reg  [31:0] ex_csr_rdata
);

//csr_op
localparam      CSR_OP_CSRRW = 3'b000,
                CSR_OP_CSRRS = 3'b001,
                CSR_OP_ECALL = 3'b110,
                CSR_OP_MRET = 3'b111;


//csr_addr
localparam      CSR_MSTATUS = 12'h300,
                CSR_MTVEC   = 12'h305,
                CSR_MEPC    = 12'h341,
                CSR_MCAUSE  = 12'h342;

wire [11:0] ex_csr_addr = imm[11:0];

reg [31:0] mstatus;
reg [31:0] mtvec;
reg [31:0] mepc;
reg [31:0] mcause; 

//write
always@(posedge clk)begin
    if(rst)begin
        mstatus <= 32'h0;
        mtvec   <= 32'd0;
        mepc    <= 32'd0;
        mcause  <= 32'd0;
    end else if(csr_wen)begin
        if(csr_op == CSR_OP_CSRRW || csr_op == CSR_OP_CSRRS)begin
            case(ex_csr_addr)
                CSR_MSTATUS: mstatus <= mstatus | ex_csr_wdata;
                CSR_MTVEC  : mtvec   <= ex_csr_wdata;
                CSR_MEPC   : mepc    <= ex_csr_wdata;
                CSR_MCAUSE : mcause  <= ex_csr_wdata;
                default: begin
                    mstatus <= mstatus ;
                    mtvec   <= mtvec   ;
                    mepc    <= mepc    ;
                    mcause  <= mcause  ;
                end
            endcase
        end else if(csr_op == CSR_OP_ECALL)begin
            mcause <= 32'd11;
            mepc <= pc + 32'd4;
        end
    end
end

//read
always@(*)begin
    if(csr_op == CSR_OP_ECALL)begin
        ex_csr_rdata = mtvec;
    end else if(csr_op == CSR_OP_MRET)begin
        ex_csr_rdata = mepc;
    end else begin
        case(ex_csr_addr)
            CSR_MSTATUS: ex_csr_rdata = mstatus;
            CSR_MTVEC  : ex_csr_rdata = mtvec;
            CSR_MEPC   : ex_csr_rdata = mepc;
            CSR_MCAUSE : ex_csr_rdata = mcause;
            default: ex_csr_rdata = 32'd0;
        endcase
    end
end
endmodule

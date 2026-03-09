
module ysyx_26020055_top (
    input         clk,
    input         rst,
	output [31:0] pc,
	output [3:0] jmp_op,
	output [31:0]inst
);

//wire [31:0] inst;
//wire [31:0] pc;
ysyx_26020055_IFU IFU (
	.clk(clk),
	.pc(pc),    //input
    .inst(inst)     //output
);


wire [4:0] rs1,rs2,rd;
wire [31:0] imm;
wire reg_wr;
wire mem_rd,mem_wr;
wire [5:0] exu_op;
//wire [3:0] jmp_op;
wire [3:0] uncal_op;
wire [3:0] mem_op;
wire [3:0] sys_op;
wire [31:0] pc_jmp_target;
ysyx_26020055_IDU IDU (        
    .inst   (inst),    //input [31:0]  
    .rs1    (rs1),     //output [4:0]  
    .rs2    (rs2),     //output [4:0]  
    .rd     (rd),     //output [4:0]  
    .imm    (imm),     //output [31:0] 
    .reg_wr (reg_wr),     //output        
    .mem_rd (mem_rd),     //output        
    .mem_wr (mem_wr),     //output        
	.jmp_op (jmp_op),
    .exu_op (exu_op),	    //output [5:0]  
	.uncal_op(uncal_op),
	.mem_op (mem_op),
	.sys_op (sys_op)
);

wire [31:0] reg_wr_data;
wire [31:0] rs1_data,rs2_data;
wire jmp_taken;

wire [31:0] raddr,waddr;
wire [31:0] rdata;
ysyx_26020055_EXU EXU (
    .rs1_data(rs1_data),
    .rs2_data(rs2_data),
    .imm(imm),
    .exu_op(exu_op),
	.jmp_op(jmp_op),
	.uncal_op(uncal_op),
	.sys_op(sys_op),
	.pc(pc),
	.rdata(rdata),
	.mem_on(mem_rd | mem_wr),

	.jmp_taken(jmp_taken),
	.pc_jmp_target(pc_jmp_target),

	.reg_wr_data(reg_wr_data),

	.mem_rd_addr(raddr),
	.mem_wr_addr(waddr)
);


//ysyx_26020055_LSU

ysyx_26020055_LSU LSU(
    .raddr(raddr),			//input [31:0]      
    .waddr(waddr),			//input [31:0]      
    .wdata(rs2_data),		//input [31:0]    	//riscv所有的save都是写的rs2的数据  
    .wnum (mem_op),			//input [3:0]       //写入的字节个数 1 2 4
    .valid(mem_rd|mem_wr),			//input             
    .wen  (mem_wr),			//input             
    .rdata(rdata) 			//output reg [31:0] 
);



ysyx_26020055_WBU WBU (
	.clk			 (clk			  ),		//input 			
	.rst			 (rst			  ),		//input 			
	.rs1			 (rs1			  ),		//input  [4:0]  	
	.rs2			 (rs2			  ),		//input  [4:0]  	
	.rd				 (rd			  ),		//input  [4:0]  	
	.wr_data		 (reg_wr_data	  ),		//input  [31:0] 	
	.wen			 (reg_wr		  ),		//input 			
	.jmp_taken       (jmp_taken       ),		//input 			 //jmp跳转
	.pc_jmp_target   (pc_jmp_target   ),		//input 			 //jmp目标地址

	.rs1_data		 (rs1_data		 ),		//output [31:0] 	
	.rs2_data		 (rs2_data		 ),		//output [31:0] 	
	.pc				 (pc			 )		//output [31:0] 	
	);
    
endmodule

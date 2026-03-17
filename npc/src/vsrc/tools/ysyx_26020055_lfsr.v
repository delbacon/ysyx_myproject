module ysyx_26020055_lfsr (
    input        clk,
    input        rst,          // 异步复位，低有效
    input        start,        // 触发脉冲（高电平 ≥1 clk）
    output reg   output_pulse  // 随机延迟后的单周期脉冲
);

// 8-bit maximal-length LFSR: x^8 + x^6 + x^5 + x^4 + 1
// Feedback = lfsr[7] ^ lfsr[5] ^ lfsr[4] ^ lfsr[3]
wire feedback =  lfsr[4] ^ lfsr[2];

reg [4:0] lfsr;
reg [4:0] delay_count;
reg       counting;

always @(posedge clk) begin
    if (rst) begin 

        delay_count  <= 5'd0;
        counting     <= 1'b0;
        output_pulse <= 1'b0;
    end else begin
        output_pulse <= 1'b0;

        if (start && !counting) begin
            delay_count <= (lfsr == 'd0) ? 'd1 : lfsr;
            counting    <= 1'b1;
        end

        if (counting) begin
            if (delay_count == 'd1) begin
                output_pulse <= 1'b1;
                counting     <= 1'b0;
            end else begin
                delay_count <= delay_count - 1;
            end
        end
    end
end


always@(posedge clk)begin
    if(rst)
        lfsr <= 5'h3; // 非零种子，比如 0001_0010
    else 
        // LFSR 持续运行（提升熵）
        lfsr <= (start)?{lfsr[2:0], feedback, lfsr[3]}:{lfsr[3:0], feedback};
end



endmodule

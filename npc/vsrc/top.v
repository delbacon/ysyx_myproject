module top(
  input clk,
  input rst,
  input sw,
  output reg [15:0] led,
  output reg [31:0]cnt
);


always@(posedge clk or posedge rst)begin
  if(rst)begin
    cnt <= 'd0;
  end else if(cnt == 'd10_000_00 - 1)begin
    cnt <= 'd0;
  end else begin
    cnt <= cnt + 1;
  end
end

always@(posedge clk or posedge rst)begin
  if(rst)begin
    led <= 'd0;
  end else if(cnt == 'd10_000_00 - 1) begin
    if(led == 'd0)begin
      led <= 'd1;
    end else begin
      led <= {led[14:0],led[15]};
    end
  end
end
endmodule

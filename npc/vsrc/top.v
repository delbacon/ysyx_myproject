module top(
  input a,
  input b,
  output f,
  output test
);
  assign f = a ^ b;
  assign test = 1;
endmodule

module  encoder8_3(
    input [7:0]in,
    output reg flag,
    output reg[3:0]out
);
/*
    assign out[3] = 0;
    assign out[2] = in[7] | ~in[7]&in[6] | ~in[7]&~in[6]&in[5] | ~in[7]&~in[6]&~in[5]&in[4] ;
    assign out[1] = in[7] | ~in[7]&in[6] | ~in[7]&~in[6]&~in[5]&~in[4]&in[3] | ~in[7]&~in[6]&~in[5]&~in[4]&~in[3]&in[2] ;
    assign out[0] = in[7] | ~in[7]&~in[6]&in[5] | ~in[7]&~in[6]&~in[5]&~in[4]&in[3] | ~in[7]&~in[6]&~in[5]&~in[4]&~in[3]&~in[2]&in[1] ; 
    assign flag = (out == 0)?0:1;
*/
    always@(*)begin
        casez(in)
            8'b1???????: begin out = 4'b0111;flag = 1; end 
            8'b01??????: begin out = 4'b0110;flag = 1; end 
            8'b001?????: begin out = 4'b0101;flag = 1; end 
            8'b0001????: begin out = 4'b0100;flag = 1; end 
            8'b00001???: begin out = 4'b0011;flag = 1; end 
            8'b000001??: begin out = 4'b0010;flag = 1; end 
            8'b0000001?: begin out = 4'b0001;flag = 1; end 
            8'b00000001: begin out = 4'b0000;flag = 1; end 
            default:     begin out = 0;flag = 0;       end
        endcase
    end


endmodule
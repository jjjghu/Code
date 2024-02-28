module alu(A,B,op,Y);
input [5:0]A,B;
input[3:0]op;
output reg [5:0]Y;
always@(op) // when op changes do the following statement
begin
    case(op) // change the value of Y by op's value
 	 4'h0: assign Y = A;
 	 4'h1: assign Y = B;
 	 4'h2: assign Y = A + 1;
	 4'h3: assign Y = B + 1;
 	 4'h4: assign Y = A - 1;
 	 4'h5: assign Y = B - 1;
 	 4'h6: assign Y = A + B;
 	 4'h7: assign Y = A - B;
 	 4'h8: assign Y = A & B;
	 4'h9: assign Y = A | B; 
 	 4'hA: assign Y = A ^ B; 
  	 4'hB: assign Y = ~A;    
 	 4'hC: assign Y = A << 1;
 	 4'hD: assign Y = A >> 1;
 	 4'hE: assign Y = (A>B)? A:B;
 	 4'hF: assign Y = (A<B)? A:B;
    endcase
end
endmodule
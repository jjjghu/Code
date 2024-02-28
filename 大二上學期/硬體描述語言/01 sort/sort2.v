module sort2(A,B, min, max);
	input [7:0] A, B;
	output [7:0]min, max;
	wire s;
	assign s = (A < B)?1:0;
	assign min = (s == 1)? A:B;
	assign max = (s == 1)? B:A;
endmodule
module rom_a(count, seg, dpt);
	input [2:0] count;
	output reg [6:0] seg;
	output reg dpt;
	always@(count)
	begin
		case(count)
			3'b000:{seg,dpt} = {7'b1000000,1'b1}; // 0
			3'b001:{seg,dpt} = {7'b1000000,1'b1}; // 0
			3'b010:{seg,dpt} = {7'b1000000,1'b1}; // 0
			3'b011:{seg,dpt} = {7'b0110000,1'b1}; // 3
			3'b100:{seg,dpt} = {7'b0100100,1'b1}; // 2
			3'b101:{seg,dpt} = {7'b1111001,1'b1}; // 1
			default: {seg,dpt} = {7'b0000000,1'b0}; // error
		endcase
	end
endmodule
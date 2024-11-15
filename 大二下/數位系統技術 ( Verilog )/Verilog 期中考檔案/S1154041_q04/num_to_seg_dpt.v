module num_to_seg_dpt(num, seg7, dpt);
	input [3:0] num;
	output reg[6:0] seg7;
	output reg dpt;
	always@(num)
	begin
		case(num)
			0: {seg7, dpt} = {7'b1000000, 1'b1}; // 0
			1: {seg7, dpt} = {7'b1111001, 1'b1}; // 1
			2: {seg7, dpt} = {7'b0100100, 1'b1}; // 2
			3: {seg7, dpt} = {7'b0110000, 1'b1}; // 3
			4: {seg7, dpt} = {7'b0011001, 1'b1}; // 4
			5: {seg7, dpt} = {7'b0010010, 1'b1}; // 5
			6: {seg7, dpt} = {7'b0000010, 1'b1}; // 6
			7: {seg7, dpt} = {7'b1111000, 1'b1}; // 7
			8: {seg7, dpt} = {7'b0000000, 1'b1}; // 8
			9: {seg7, dpt} = {7'b0010000, 1'b1}; // 9
			default: {seg7, dpt} = {7'b1000000, 1'b0}; // error
		endcase
	end
endmodule

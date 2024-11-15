module switch_to_num(sw3, sw2, sw1, n3, n2, n1);
	input sw3, sw2, sw1;
	output reg [31:0] n3, n2, n1;
	always @(sw3 or sw2 or sw1)
	begin
		if((sw3 == 0 && sw2 == 0 && sw1 == 1)||(sw3 == 0 && sw2 == 1 && sw1 == 0) || (sw3 == 1 && sw2 == 0 && sw1 == 1))
		begin
			n3 = 4;
			n2 = 4;
			n1 = 4;
		end
		else
		begin
			n3 = (sw3 == 1) ? 3:0;
			n2 = (sw2 == 1) ? 2:0;
			n1 = (sw1 == 1) ? 1:0;
		end
	end
endmodule
//000
//100
//110
//111
//011
//001
//
//001
//010
//101
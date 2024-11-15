module S1154041_q06(clk, rst, seg0, seg1, seg0_dpt, seg1_dpt);
	input clk, rst;
	output [6:0] seg0, seg1;
	output seg0_dpt, seg1_dpt;
	wire clk_slow, clk_fast;
	wire [3:0] cnt_slow, cnt_fast;
	wire [5:0] loopTime;
	wire swap;
	
	freq_div #(23) freq0(clk, ~rst, clk_fast);
	freq_div #(24) freq1(clk, ~rst, clk_slow);
	
	counter_loop #(5) counter_slow(clk_slow, ~rst, cnt_slow);
	counter_loop #(5) counter_fast(clk_fast, ~rst, cnt_fast);
	swapUpdate #(29) swap_update(clk_slow, ~rst, swap);
	
	num_to_seg nts0((swap == 1) ? cnt_fast : cnt_slow, seg0, seg0_dpt);
	num_to_seg nts1((swap == 1) ? cnt_slow : cnt_fast, seg1, seg1_dpt);
	
endmodule
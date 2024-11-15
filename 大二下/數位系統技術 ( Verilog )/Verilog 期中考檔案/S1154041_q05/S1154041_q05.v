module S1154041_q05(clk, rst, seg1, seg2, seg3, seg1_dpt, seg2_dpt, seg3_dpt);
	// 時鐘, reset, 兩個開關, 七段顯示器, 小數點
	input clk, rst;
	output [6:0] seg1, seg2, seg3;
	output seg1_dpt, seg2_dpt, seg3_dpt;
	wire clk_select;
	wire [5:0] cnt;
	freq_div #(24) freq1(clk, ~rst, clk_select);

	counter_loop #(30) cnt0(clk_select, ~rst, cnt);
	num_to_seg nts0(cnt, seg1, seg2, seg3, seg1_dpt, seg2_dpt, seg3_dpt);
	
endmodule
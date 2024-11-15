module S1154041_q04(clk, rst, seg, sw2, sw1);
    input clk, rst, sw2, sw1;
    output [6:0] seg;
    wire clkSelect, clkFast, clkMedium, clkSlow;
    wire [3:0] cnt;
    freq_div #(22) fdFast(clk, ~rst, clkFast);
    freq_div #(23) fdMedium(clk, ~rst, clkMedium);
    freq_div #(24) fdSlow(clk, ~rst, clkSlow);
	clkUpdate cu(sw2, sw1, clkSelect, clkFast, clkMedium, clkSlow);
    counter c(clkSelect, ~rst, cnt);
    num_to_seg nts(cnt, seg);
endmodule
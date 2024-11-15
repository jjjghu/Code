module S1154041_q02(clk, rst, sw2, sw1, led4, led3, led2, led1);
    input clk, rst, sw2, sw1;
	output led4, led3, led2, led1;
    wire clkSelect, clkFast, clkMedium, clkSlow;
    wire [31:0] cnt;
    freq_div #(22) fdFast(clk, ~rst, clkFast);
    freq_div #(23) fdMedium(clk, ~rst, clkMedium);
    freq_div #(24) fdSlow(clk, ~rst, clkSlow);
	clkUpdate cu(sw2, sw1, clkSelect, clkFast, clkMedium, clkSlow);
    counter #(4) c(clkSelect, ~rst, cnt);
    num_to_seg nts(cnt, led4, led3, led2, led1);
endmodule
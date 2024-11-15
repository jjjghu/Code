module S1154041_q03(clk, rst, seg3, seg2, seg1);
    input clk, rst;
    output [6:0] seg3, seg2, seg1;
    wire clkout;
    freq_div #(24) freq_div(clk, ~rst, clkout);
    wire [31:0] cnt;
    counter #(6) (clkout, ~rst, cnt);
    num_to_seg nts(cnt, seg3, seg2, seg1);
endmodule 
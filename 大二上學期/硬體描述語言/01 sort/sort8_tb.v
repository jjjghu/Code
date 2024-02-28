module sort8_tb;
reg[7:0] x0, x1, x2, x3, x4, x5, x6, x7;
wire[7:0] y0, y1, y2, y3, y4, y5, y6, y7;
sort8 sorter(x0, x1, x2, x3, x4, x5, x6, x7, y0, y1, y2, y3, y4, y5, y6, y7);
initial
$monitor("Time: %3d ns, Input: x0 = %2d, x1 = %2d, x2 = %2d, x3 = %2d, x4 = %2d, x5 = %2d, x6 = %2d, x7 = %2d Output: y0 = %2d, y1 = %2d, y2 = %2d, y3 = %2d, y4 = %2d, y5 = %2d, y6 = %2d, y7 = %2d", $time,x0, x1, x2, x3, x4, x5, x6, x7, y0, y1, y2, y3, y4, y5, y6, y7);
initial begin
	#10 x0 = 8'd8; x1 = 8'd7; x2 = 8'd6; x3 = 8'd5; x4 = 8'd4; x5 = 8'd3; x6 = 8'd2; x7 = 8'd1;
	#10 x0 = 8'd5; x1 = 8'd6; x2 = 8'd7; x3 = 8'd8; x4 = 8'd1; x5 = 8'd2; x6 = 8'd3; x7 = 8'd4;
	#10 x0 = 8'd8; x1 = 8'd7; x2 = 8'd4; x3 = 8'd3; x4 = 8'd5; x5 = 8'd6; x6 = 8'd2; x7 = 8'd1;
	#10 x0 = 8'd18; x1 = 8'd72; x2 = 8'd36; x3 = 8'd58; x4 = 8'd44; x5 = 8'd73; x6 = 8'd27; x7 = 8'd31;
	#10 x0 = 8'd80; x1 = 8'd86; x2 = 8'd56; x3 = 8'd1; x4 = 8'd52; x5 = 8'd12; x6 = 8'd20; x7 = 8'd17;
	#10 x0 = 8'd8; x1 = 8'd17; x2 = 8'd69; x3 = 8'd42; x4 = 8'd90; x5 = 8'd0; x6 = 8'd89; x7 = 8'd42;
	#20 $finish;
end
endmodule
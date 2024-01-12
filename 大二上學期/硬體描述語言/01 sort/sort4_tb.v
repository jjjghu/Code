module sort4_tb;
reg [7:0] x0, x1, x2, x3;
wire [7:0] y0, y1, y2, y3;
sort4 sorter(x0, x1, x2, x3, y0, y1, y2, y3);
initial
 $monitor("TIme: %3t ns, Input: x0=%2d,x1=%2d,x2=%2d,x3=%2d,Output: y0=%2d,y1=%2d,y2=%2d,y3=%2d", $time,x0, x1, x2, x3, y0, y1, y2, y3);
initial begin
	#10 x0 = 8'd4; x1 = 8'd3; x2 = 8'd2; x3 = 8'd1;
	#10 x0 = 8'd1; x1 = 8'd4; x2 = 8'd3; x3 = 8'd2;
	#10 x0 = 8'd25; x1 = 8'd92; x2 = 8'd3; x3 = 8'd8;
	#10 x0 = 4'd32; x1 = 8'd0; x2 = 8'd79; x3 = 8'd64;
	#20 $finish;
end
endmodule

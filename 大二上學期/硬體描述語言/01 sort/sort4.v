module sort4(x0,x1,x2,x3,y0,y1,y2,y3);
	input [7:0] x0, x1, x2, x3;
	output [7:0] y0, y1, y2, y3;
	wire [7:0] win1, win2, lose1, lose2, lw, wl;
	sort2 s1(x0, x1, lose1, win1);
	sort2 s2(x2, x3, lose2, win2);
	sort2 s3(win1, win2, wl, y3);
	sort2 s4(lose1, lose2, y0, lw);
	sort2 s5(wl, lw, y1, y2);
endmodule

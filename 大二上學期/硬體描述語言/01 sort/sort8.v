module sort8(x0,x1,x2,x3,x4,x5,x6,x7,y0,y1,y2,y3,y4,y5,y6,y7);
	input [7:0] x0,x1,x2,x3,x4,x5,x6,x7;
	output [7:0] y0,y1,y2,y3,y4,y5,y6,y7;
	wire [7:0] l1, l2, l3, l4, w1, w2, w3, w4, s1, s2, s3, s4;/* s5, s6, m1, m2, m3, m4, n1, n2;*/

	sort4 s4_1(x0, x1, x2, x3, l1, l2, w1, w2);
	sort4 s4_2(x4, x5, x6, x7, l3, l4, w3, w4);

	sort4 s4_3(l1, l2, l3, l4, y0, y1, s3, s4);
	sort4 s4_4(w1, w2, w3, w4, s1, s2, y6, y7);

	sort4 s4_5(s1, s2, s3, s4, y2, y3, y4, y5);
/*
	sort4 s4_3(l1, l2, l3, l4, y0, s4, s5, s6);
	sort4 s4_4(w1, w2, w3, w4, s1, s2, s3, y7);
	
	sort4 s4_5(s1, s2, s3, s4, m1, m2, m3, m4);
	sort4 s4_6(m3, m4, s5, s6, n1, n2, y5, y6);
	sort4 s4_7(m1, m2, n1, n2, y1, y2, y3, y4);
*/
endmodule
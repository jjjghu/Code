module alu_tb;
reg[5:0]A,B;
reg[3:0]op;
wire[5:0]Y;
alu test(A,B,op,Y);
initial
$monitor("Time: %3t ns, A = %3d, B = %3d, op = %1h, Y = %3d", $time, A, B, op, Y);
//output when any value changed 
initial
begin
	for(op = 4'h0;; op = op+1)
	begin
	 #10;
	end
end

initial
begin
	A = 6'd12; B = 6'd5;
	#160
	op<=4'h0;
	A = 6'd7; B = 6'd11;
end

initial #320 $finish;
endmodule
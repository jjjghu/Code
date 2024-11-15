module freq_div(clk, rst, clk_out);
    input clk;
    input rst;
    output clk_out;
	 
    parameter EXP = 3;
    
    reg [EXP-1:0] divider;
    assign clk_out = divider[EXP-1];

    always @(posedge clk, posedge rst)
	 begin
        if(rst)
            divider <= 0;
        else
            divider <= divider + 1;
    end
endmodule

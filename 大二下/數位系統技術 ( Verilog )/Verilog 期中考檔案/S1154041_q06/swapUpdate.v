module swapUpdate(clk, rst, swap);
    input clk, rst;
    reg [5:0] count;
	 output reg swap;
    parameter [5:0] MX = 30;
    always@(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            count = 0;
        end
        else
        begin
            // 0 ~ 30
            if(count == MX)
            begin
                count = 0;
					 swap = ~swap;
            end
            else
                count = count + 1;
        end
    end
endmodule
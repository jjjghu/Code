module counter_loop(clk, rst, count);
    input clk, rst;
    output reg [3:0] count;
    reg [3:0] MX = 1;
    always@(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            count = 3'b000;
            MX = 1;
        end
        else
        begin
            // 0~1, 0~2, 0~3... 0~9, 0~1
            if(count == MX)
            begin
                count = 3'b000;
				if(MX == 9) MX = 0;
                MX = MX + 1;
            end
            else
                count = count + 1;
        end
    end
endmodule
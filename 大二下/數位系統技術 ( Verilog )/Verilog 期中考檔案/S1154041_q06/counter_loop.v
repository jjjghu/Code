module counter_loop(clk, rst, count);
    input clk, rst;
    output reg [2:0] count;
    parameter [3:0] MX = 5;
    always@(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            count = 0;
        end
        else
        begin
            // 0 ~ 5
            if(count == MX)
            begin
                count = 0;
            end
            else
                count = count + 1;
        end
    end
endmodule